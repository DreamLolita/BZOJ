#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1e5+10;
const int M=2e7+10;

int T,n,m,q,ans,cnt,tot,len;
int vs[N],rt[N],siz[N],col[N],head[N],dep[N],R[N];
int fa[N][20];
bool vis[N];

struct Tway
{
	int u,v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){u,v,head[u]};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v]};head[v]=tot;
}

struct Segment_Tree
{
	int ls[M],rs[M],sum[M];
	
	void update(int x,int &y,int l,int r,int p)
	{
		y=++len;
		sum[y]=sum[x]+1;
		if(l==r)
			return;
		ls[y]=ls[x];rs[y]=rs[x];
		int mid=(l+r)>>1;
		if(p<=mid)	
			update(ls[x],ls[y],l,mid,p);
		else
			update(rs[x],rs[y],mid+1,r,p);
	}
	
	int query(int x1,int x2,int x3,int x4,int l,int r,int p)
	{
		if(l==r)
			return l;
		int now=sum[ls[x1]]+sum[ls[x2]]-sum[ls[x3]]-sum[ls[x4]];
		int mid=(l+r)>>1;
		if(p<=now)
			query(ls[x1],ls[x2],ls[x3],ls[x4],l,mid,p);
		else
			query(rs[x1],rs[x2],rs[x3],rs[x4],mid+1,r,p-now);
	}
}tr;

void dfs(int x,int f,int now)
{
	vis[x]=true;siz[x]=1;col[x]=now;
	for(int i=1;i<20;++i)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	tr.update(rt[f],rt[x],1,INF,vs[x]);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=f)
		{
			fa[v][0]=x;dep[v]=dep[x]+1;
			dfs(v,x,now);
			siz[x]+=siz[v];
		}
	}
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<20;++i)
		if(t&(1<<i))
			x=fa[x][i];
	for(int i=19;~i;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	if(x==y)
		return x;
	return fa[x][0];
}

int main()
{
	freopen("BZOJ3123.in","r",stdin);
	freopen("BZOJ3123.out","w",stdout);

	scanf("%d",&T);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i)
		scanf("%d",&vs[i]);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			dfs(i,0,++cnt),R[cnt]=i;
	while(q--)
	{
		char opt[2];int u,v,w;
		scanf("%s%d%d",opt,&u,&v);u^=ans;v^=ans;
		if(opt[0]=='Q')
		{
			scanf("%d",&w);w^=ans;
			int lca=LCA(u,v);
			ans=tr.query(rt[u],rt[v],rt[lca],rt[fa[lca][0]],1,INF,w);
			printf("%d\n",ans);
		}
		else
		{
			int now1=R[col[u]],now2=R[col[v]];
			if(siz[now1]>siz[now2])
				swap(now1,now2),swap(u,v);
			add(v,u);fa[u][0]=v;siz[now2]+=siz[now1];dep[u]=dep[v]+1;
			dfs(u,v,col[v]);
		}
	}

	return 0;
}
