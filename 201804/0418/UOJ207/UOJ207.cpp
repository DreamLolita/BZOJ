#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10;
int n,m,id,tot,S;
stack<int>q;

inline int read()
{
	int ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3)+(ret<<1)+(ch-'0');ch=getchar();}
	return ret*f;
}

struct Tway
{
	int u,v,w;
};
Tway e[N];

struct LCT
{
	int ch[N][2],fa[N],val[N],rev[N],sum[N];
	
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	
	void pushdown(int x)
	{
		if(rev[x])
		{
			rev[x]^=1;rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
			swap(ch[x][0],ch[x][1]);
		}
	}
	
	void pushup(int x)
	{
		sum[x]=sum[ch[x][0]]^sum[ch[x][1]]^val[x];
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
		for(int i=0;x;i=x,x=fa[x])
		{
			splay(x);val[x]^=sum[ch[x][1]];
			ch[x][1]=i;val[x]^=sum[i];
			pushup(x);
		}
	}
	
	void rever(int x)
	{
		access(x);
		splay(x);
		rev[x]^=1;
	}
	
	void makeroot(int x)
	{
		access(x);
		splay(x);
		rever(x);
	}
	
	void link(int x,int y)
	{
		makeroot(x);makeroot(y);
		fa[x]=y;val[y]^=sum[x];
		pushup(y);
	}
	
	void cut(int x,int y)
	{
		makeroot(x);access(y);splay(y);
		fa[x]=ch[y][0]=0;
		pushup(y);
	}
	
	void update(int x,int v)
	{
		access(x);splay(x);
		val[x]^=v;sum[x]^=v;
	}
	
	bool query(int x,int y)
	{
		makeroot(x);access(y);
		return val[y]==S?1:0;
	}
}tr;

int main()
{
	freopen("UOJ207.in","r",stdin);
	freopen("UOJ207.out","w",stdout);
	
	srand(233);
	id=read();n=read();m=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		tr.link(u,v);
	}
	for(int i=1;i<=m;++i)
	{
		int x,y,w,op;
		op=read();x=read();
		if(op==1)
		{
			y=read();tr.cut(x,y);
			x=read();y=read();tr.link(x,y);
		}
		else
		if(op==2)
		{
			y=read();
			e[++tot]=(Tway){x,y,w=rand()*rand()};
			S^=w;tr.update(x,w);tr.update(y,w);
		}
		else
		if(op==3)
		{
			S^=e[x].w;
			tr.update(e[x].u,e[x].w);tr.update(e[x].v,e[x].w);
		}
		else
		{
			y=read();
			puts(tr.query(x,y)?"YES":"NO");
		}
	}
	
	return 0;
}
