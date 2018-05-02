#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=N*50;
const int INF=1e9;
int n,m,cnt,tot,ind,cs;
int root[N],head[N],beg[N],dep[N],tar[N],re[N];
int fa[19][N];

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

struct Tquery
{
	int x,y,c;
};
Tquery q[N];

bool cmp(Tquery A,Tquery B)
{
	return A.c<B.c;
}

void dfs(int x,int f)
{
	beg[x]=++ind;fa[0][x]=f;dep[x]=dep[f]+1;re[ind]=x;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		dfs(v,x);
	}
}

void get_fa()
{
	for(int i=1;i<18;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<18;++i)
		if(t&(1<<i))
			x=fa[i][x];
	for(int i=17;~i;--i)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return x==y?x:fa[0][x];
}

struct Seqment
{
	int sz;
	int ls[M],rs[M],v[M],s[M];
	
	void pushup(int x)
	{
		v[x]=max(v[ls[x]],v[rs[x]]);
		s[x]=(v[ls[x]]>=v[rs[x]]?s[ls[x]]:s[rs[x]]);
	}
	
	void insert(int &x,int l,int r,int p,int d)
	{
		if(!x)
			x=++sz;
		if(l==r)
		{
			v[x]+=d;s[x]=tar[l];
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			insert(ls[x],l,mid,p,d);
		else
			insert(rs[x],mid+1,r,p,d);
		pushup(x);
	}
	
	void merge(int &x,int y,int l,int r)
	{
		if(!x || !y)
		{
			x=x+y;
			return;
		}
		if(l==r)
		{
			v[x]+=v[y];
			return;
		}
		int mid=(l+r)>>1;
		merge(ls[x],ls[y],l,mid);
		merge(rs[x],rs[y],mid+1,r);
		pushup(x);
	}
}tr;

int main()
{
	freopen("BZOJ3307.in","r",stdin);
	freopen("BZOJ3307.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
		root[i]=++tr.sz;
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	dfs(1,0);get_fa();
	for(int i=1;i<=m;++i)
		q[i].x=read(),q[i].y=read(),q[i].c=read();
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		int u=q[i].x,v=q[i].y,lca=LCA(u,v);
		if(q[i].c>q[i-1].c)
			tar[++cs]=q[i].c;
		tr.insert(root[u],0,m,cs,1);tr.insert(root[v],0,m,cs,1);
		tr.insert(root[lca],0,m,cs,-1);tr.insert(root[fa[0][lca]],0,m,cs,-1);
	}
	for(int i=n;i>1;--i)
		tr.merge(root[fa[0][re[i]]],root[re[i]],0,m);
	for(int i=1;i<=n;++i)
		printf("%d\n",tr.s[root[i]]);
	
	return 0;
}
