#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=2e6+10;
int n,m,q,cnt;
int f[M];

struct Tway
{
	int u,v,w,id;
	bool op;
};
Tway e[M];

bool cmp1(Tway A,Tway B)
{
	return A.w<B.w;
}

bool cmp2(Tway A,Tway B)
{
	if(A.u^B.u)
		return A.u<B.u;
	return A.v<B.v;
}

bool cmp3(Tway A,Tway B)
{
	return A.id<B.id;
}

struct Tquery
{
	int op,x,y,ans,id;
};
Tquery qr[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

void write(int x)
{
	if(x<0)putchar('-'),x=-1;
	if(x>9)write(x/10);
	putchar((x%10)^48);
}

int findf(int x)
{
	return x==f[x]?x:f[x]=findf(f[x]);
}

int findp(int u,int v)
{
	int l=1,r=m;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(e[mid].u==u && e[mid].v==v)
			return mid;
		if(e[mid].u<u || (e[mid].u==u && e[mid].v<v))
			l=mid+1;
		else
			r=mid-1;
	}
}

struct LCT
{
	int fa[M],key[M],mx[M],rev[M];
	int ch[M][2];
	stack<int>stk;
	
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	
	void pushup(int x)
	{
		int ls=ch[x][0],rs=ch[x][1];mx[x]=x;
		if(key[mx[ls]]>key[mx[x]]) mx[x]=mx[ls];
		if(key[mx[rs]]>key[mx[x]]) mx[x]=mx[rs];
	}
	
	void pushdown(int x)
	{
		if(rev[x])
		{
			int ls=ch[x][0],rs=ch[x][1];
			rev[ls]^=1;rev[rs]^=1;
			swap(ch[x][0],ch[x][1]);rev[x]=0;
		}
	}
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(!isroot(y))
			ch[z][ch[z][1]==y]=x;
		fa[x]=z;fa[y]=x;fa[ch[x][!kind]]=y;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x)
	{
		stk.push(x);
		for(int i=x;!isroot(i);i=fa[i])
			stk.push(fa[i]);
		while(!stk.empty())
			pushdown(stk.top()),stk.pop();
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y))
			{
				if(ch[y][0]^x==ch[z][0]^y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
	}
	
	void access(int x)
	{
		for(int t=0;x;t=x,x=fa[x])
			splay(x),ch[x][1]=t,pushup(x);
	}
	
	void makeroot(int x)
	{
		access(x);splay(x);
		rev[x]^=1;
	}
	
	void link(int x,int y)
	{
		makeroot(x);fa[x]=y;
	}
	
	void cut(int x,int y)
	{
		makeroot(x);access(y);splay(y);
		ch[y][0]=fa[x]=0;
	}
	
	int query(int x,int y)
	{
		makeroot(x);access(y);splay(y);
		return mx[y];
	}
	
	int solve1(int x,int y)
	{
		return key[query(x,y)];
	}
}tr;

int main()
{
	freopen("BZOJ2594.in","r",stdin);
	freopen("BZOJ2594.out","w",stdout);
	
	n=read();m=read();q=read();
	for(int i=1;i<=n;++i)	
		f[i]=i;
	for(int i=1;i<=m;++i)
	{
		e[i].u=read();e[i].v=read();e[i].w=read();
		if(e[i].u>e[i].v)
			swap(e[i].u,e[i].v);
	}
	
	sort(e+1,e+m+1,cmp1);
	for(int i=1;i<=m;++i)
	{
		e[i].id=i;tr.key[n+i]=e[i].w;
		tr.mx[n+i]=n+i;
	}
	
	sort(e+1,e+m+1,cmp2);
	for(int i=1;i<=q;++i)
	{
		qr[i].op=read();qr[i].x=read();qr[i].y=read();
		if(qr[i].op==2)
		{
			if(qr[i].x>qr[i].y)
				swap(qr[i].x,qr[i].y);
			int t=findp(qr[i].x,qr[i].y);
			e[t].op=1;qr[i].id=e[t].id;
		}
	}
	
	sort(e+1,e+m+1,cmp3);cnt=0;
	for(int i=1;i<=m;++i)
	{
		if(e[i].op)
			continue;
		int u=e[i].u,v=e[i].v,fu=findf(u),fv=findf(v);
		if(fu^fv)
		{
			++cnt;f[fu]=fv;
			tr.link(u,i+n);tr.link(v,i+n);
			if(cnt==n-1)
				break;
		}
	}
	for(int i=q;i;--i)
	{
		if(qr[i].op&1)
			qr[i].ans=tr.solve1(qr[i].x,qr[i].y);
		else
		{
			int u=qr[i].x,v=qr[i].y,d=qr[i].id;
			int t=tr.query(u,v);
			if(e[d].w<tr.key[t])
			{
				tr.cut(e[t-n].u,t);tr.cut(e[t-n].v,t);
				tr.link(u,d+n);tr.link(v,d+n);
			}
		}	
	}
	for(int i=1;i<=q;++i)
		if(qr[i].op==1)
			printf("%d\n",qr[i].ans);
	
	return 0;
}
