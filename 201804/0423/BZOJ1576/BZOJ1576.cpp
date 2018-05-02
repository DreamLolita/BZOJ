#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef pair<int,int> pii;
const int INF=1e9;
const int N=1e5+10;
const int M=N*8;
int n,m,tot,ind;
int head[N],dis[N],from[N],beg[N],top[N];
int dep[N],siz[N],son[N];
int fa[18][N];
bool vis[M],mark[M];
priority_queue<pii,vector<pii>,greater<pii> >q;

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();};
	while(isdigit(c)){ret=(ret<<3)+(ret<<1)+(c^48);c=getchar();}
	return ret*f;
}

struct Tnode
{
	int u,v,w;
};
Tnode a[N<<1];

struct Tway
{
	int u,v,w,nex;
};
Tway e[N<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){u,v,w,head[u]};head[u]=tot;
	e[++tot]=(Tway){v,u,w,head[v]};head[v]=tot;
}

struct Seqment
{
	int tar[M],mi[M];
	
	void pushdown(int x)
	{
		if(tar[x]==INF)
			return;
		int t=tar[x];tar[x]=INF;
		mi[x<<1]=min(mi[x<<1],t);mi[x<<1|1]=min(mi[x<<1|1],t);
		tar[x<<1]=min(tar[x<<1],t);tar[x<<1|1]=min(tar[x<<1|1],t);
	}
	
	void build(int x,int l,int r)
	{
		mi[x]=tar[x]=INF;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
	
	void update(int x,int l,int r,int L,int R,int v)
	{
		pushdown(x);
		if(L<=l && r<=R)
		{
			tar[x]=min(tar[x],v);
			if(l==r)
				mi[x]=min(mi[x],v);
			return;
		}		
		int mid=(l+r)>>1;
		if(L<=mid)
			update(x<<1,l,mid,L,R,v);
		if(R>mid)
			update(x<<1|1,mid+1,r,L,R,v);
	}
	
	int query(int x,int l,int r,int p)
	{
		pushdown(x);
		if(l==r)
			return mi[x];
		int mid=(l+r)>>1;
		if(p<=mid)
			return query(x<<1,l,mid,p);
		else
			return query(x<<1|1,mid+1,r,p);
	}
}tr;

void dijkstra()
{
	for(int i=1;i<=n;++i)
		dis[i]=INF;
	dis[1]=0;q.push(mkp(0,1));
	while(!q.empty())
	{
		int u=q.top().second;q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[u]+e[i].w<dis[v])
			{
				dis[v]=dis[u]+e[i].w;
				mark[from[v]]=0;from[v]=i;mark[i]=1;
				q.push(mkp(dis[v],v));
			}
		}
	}
}

void dfs1(int x,int f)
{
	siz[x]=1;fa[0][x]=f;dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!mark[i])
			continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])
			son[x]=v;
	}
}

void dfs2(int x,int tp)
{
	top[x]=tp;beg[x]=++ind;
	if(!son[x])
		return;
	dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==son[x] || v==fa[0][x] || !mark[i])
			continue;
		dfs2(v,v);
	}
}

void init_fa()
{
	for(int i=1;i<18;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
}

void init()
{
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		a[i].u=read(),a[i].v=read(),a[i].w=read();
		add(a[i].u,a[i].v,a[i].w);
	}
	dijkstra();
	dfs1(1,0);dfs2(1,1);init_fa();
	tr.build(1,1,n);
}

int lca(int x,int y)
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

void calc(int x,int t,int val)
{
	while(top[x]!=top[t])
	{
		tr.update(1,1,n,beg[top[x]],beg[x],val);
		x=fa[0][top[x]];
	}
	if(x^t)
		tr.update(1,1,n,beg[t]+1,beg[x],val);
}

void solve()
{
	for(int i=1;i<=m;++i)
	{
		int t=lca(a[i].u,a[i].v);
		if(!mark[2*i-1])
			calc(a[i].v,t,dis[a[i].u]+dis[a[i].v]+a[i].w);
		if(!mark[2*i])
			calc(a[i].u,t,dis[a[i].v]+dis[a[i].u]+a[i].w);
	}
	for(int i=2;i<=n;++i)
	{
		int t=tr.query(1,1,n,beg[i]);
		if(t!=INF)
			printf("%d\n",t-dis[i]);
		else
			puts("-1");
	}
}

int main()
{
	freopen("BZOJ1576.in","r",stdin);
	freopen("BZOJ1576.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
