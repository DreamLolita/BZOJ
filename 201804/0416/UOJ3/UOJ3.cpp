#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=2e5+10;
int n,m,ans=INF;
int f[N];
stack<int>q;

struct Tway
{
	int u,v,a,b;
};
Tway e[N];

struct LCT
{
	int rev[N],mx[N];
	int val[N],fa[N],ch[N][2];
	
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	
	void pushup(int x)
	{
		int l=ch[x][0],r=ch[x][1];mx[x]=x;
		if(val[mx[l]]>val[mx[x]])	
			mx[x]=mx[l];
		if(val[mx[r]]>val[mx[x]])	
			mx[x]=mx[r];
	}
	
	void pushdown(int x)
	{
		int l=ch[x][0],r=ch[x][1];
		if(rev[x])
		{
			rev[x]^=1;rev[l]^=1;rev[r]^=1;
			swap(ch[x][0],ch[x][1]);
		}
	}
	
	void rotate(int &x)
	{
		int y=fa[x],z=fa[y],kind=ch[y][0]!=x;
		if(!isroot(y))
			ch[z][ch[z][0]!=y]=x;
		fa[x]=z;fa[y]=x;fa[ch[x][!kind]]=y;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int &x)
	{
		q.push(x);
		for(int i=x;!isroot(i);i=fa[i])
			q.push(fa[i]);
		while(!q.empty())
			pushdown(q.top()),q.pop();
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y))
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x);
				else
					rotate(y);
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
		ch[y][0]=fa[x]=0;pushup(y);
	}
	
	int query(int x,int y)
	{
		makeroot(x);access(y);splay(y);
		return mx[y];
	}
}tr;

int read()
{
	int ret=0,f=1;char c='.';
	while(c<'0' || c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		ret=(ret<<3)+(ret<<1)+(c-'0');
		c=getchar();
	}
	return ret*f;
}

bool cmp(Tway A,Tway B)
{
	return A.a<B.a;
}

int findf(int x)
{
	return f[x]==x?x:f[x]=findf(f[x]);
}

void init()
{
	n=read();m=read();
	for(int i=1;i<=n;++i)
		f[i]=i;
	for(int i=1;i<=m;++i)
	{
		e[i].u=read();e[i].v=read();
		e[i].a=read();e[i].b=read();
	}
	sort(e+1,e+m+1,cmp);
}

void solve()
{
	for(int i=1;i<=m;++i)
	{
		int u=e[i].u,v=e[i].v,a=e[i].a,b=e[i].b;
		if(findf(u)==findf(v))
		{
			int t=tr.query(u,v);
			if(tr.val[t]>e[i].b)
			{
				tr.cut(t,e[t-n].u);
				tr.cut(t,e[t-n].v);
			}
			else
			{
				if(findf(1)==findf(n))
					ans=min(ans,e[i].a+tr.val[tr.query(1,n)]);
				continue;
			}
		}
		else
			f[findf(u)]=findf(v);
		tr.val[n+i]=e[i].b;tr.mx[n+i]=n+i;
		tr.link(u,n+i);tr.link(v,n+i);
		if(findf(1)==findf(n))
			ans=min(ans,e[i].a+tr.val[tr.query(1,n)]);
	}
	
	if(ans==INF)
		ans=-1;
	printf("%d\n",ans);
}

int main()
{
	freopen("UOJ3.in","r",stdin);
	freopen("UOJ3.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
