#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;	

typedef long long LL;
const int INF=1e9;
const int N=1e5+10;
const int M=6e5+10;
int K=4,lim=1e4;
int n,m,Q,ed,h,t,ans,POS;
int p1,p2,tot,all;
int head[N],q[N],d[N],fa[N];
int v1[N],v2[N],d1[N],d2[N],vis[N];
vector<int>es[N];
set<pii>T;

struct Tway
{
	int v,nex;
};
Tway e[M];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

int bfs(int S,int T)
{
	for(int i=1;i<=n;++i)
		d[i]=-1;
	d[q[h=t=1]=S]=0;
	while(d[T]<0)
	{
		int u=q[h++];
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(d[v]<0)
				d[q[++t]=v]=d[u]+1;
		}
	}
	return d[T];
}

void bfs1(int S)
{
	v1[S]=++p1;
	d1[q[h=t=1]=S]=0;
	while(h<=t)
	{
		int u=q[h++];
		if(d1[u]==K)
			continue;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v1[v]<p1)
			{
				d1[q[++t]=v]=d1[u]+1;
				v1[v]=p1;
			}
		}
	}
	all+=t;
}

void bfs2(int S)
{
	v2[S]=++p2;
	d2[q[h=t=1]=S]=0;
	while(h<=t)
	{
		int u=q[h++];
		if(v1[u]==p1 && d1[u]+d2[u]<ans)
			ans=d1[u]+d2[u];
		if(d2[u]==K)
			continue;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v2[v]<p1)
			{
				d2[q[++t]=v]=d2[u]+1;
				v2[v]=p1;
			}
		}
	}
	all+=t;
}

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void dfs1(int x,int y,int z)
{
	if(vis[x]<POS)
		vis[x]=POS,d[x]=y;
	else
	if(d[x]>y)
		d[x]=y;
	else
		return;

	if(y==K || y>ans)
		return;
	++y;
	for(int i=0;i<es[x].size();++i)
		if(es[x][i]!=z)
			dfs1(es[x][i],y,x);
}

void dfs2(int x,int y,int z)
{
	if(vis[x]==POS && d[x]+y<ans)
		ans=d[x]+y;
	if(y==K || y>=ans)
		return;
	++y;
	for(int i=0;i<es[x].size();++i)
		if(es[x][i]!=z)
			dfs2(es[x][i],y,x);
}

int main()
{
	freopen("BZOJ5049.in","r",stdin);
	freopen("BZOJ5049.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(findf(x)!=findf(y))
			fa[fa[x]]=fa[y];
		add(x,y);add(y,x);
		es[x].push_back(y);
		es[y].push_back(x);
	}
	
	while(Q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(findf(x)!=findf(y))
		{
			puts("-1");
			continue;
		}
		
		POS++;ans=INF;
		dfs1(x,0,0);dfs2(y,0,0);
		if(ans==INF)
			ans=bfs(x,y);
		printf("%d\n",ans);
	}
	
	return 0;
}
