#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=5005;
int n,m,k,tot,ans;
int head[N],pre[N],dep[N],dis[N];
bool inq[N];
queue<int>q;

struct Tway
{
	int u,v,nex,w,c,t;
};
Tway e[N*20];

void add(int u,int v,int w,int c,int t)
{
	e[++tot]=(Tway){u,v,head[u],w,c,t};
	head[u]=tot;
}

void init()
{
	tot=1;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i)
	{
		int u,v,w,c;
		scanf("%d%d%d%d",&u,&v,&w,&c);
		add(u,v,w,0,c);add(v,u,0,0,-c);
	}
}

bool bfs_dinic()
{
	memset(dep,-1,sizeof(dep));
	q.push(1);dep[1]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dep[v]==-1)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return ~dep[n];
}

int dfs_dinic(int u,int f)
{
	if(u==n)
		return f;
	int w,used=0;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].w && dep[v]==dep[u]+1)
		{
			w=dfs_dinic(v,min(e[i].w,f-used));
			e[i].w-=w;e[i^1].w+=w;
			used+=w;
			if(used==f)
				return f;
		}
	}
	if(!used)
		dep[u]=-1;
	return used;
}

void dinic()
{
	ans=0;
	while(bfs_dinic())
		ans+=dfs_dinic(1,INF);
	printf("%d ",ans);
}

void rebuild()
{
	int t=tot;
	for(int i=2;i<=t;i+=2)
		add(e[i].u,e[i].v,INF,e[i].t,0),add(e[i].v,e[i].u,0,-e[i].t,0);
	add(0,1,k,0,0);
}

bool spfa()
{
	for(int i=0;i<=n;++i)
		dis[i]=INF;
	dis[0]=0;inq[0]=true;q.push(0);
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=false;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dis[u]+e[i].c<dis[v])
			{
				dis[v]=dis[u]+e[i].c;
				pre[v]=i;
				if(!inq[v])
				{
					inq[v]=true;
					q.push(v);
				}
			}
		}
	}
	return dis[n]!=INF;
}

void mcfx()
{
	ans=0;
	while(spfa())
	{
		int t=INF;
		for(int i=pre[n];i;i=pre[e[i].u])
			t=min(t,e[i].w);
		
		for(int i=pre[n];i;i=pre[e[i].u])
		{
			e[i].w-=t;e[i^1].w+=t;
			ans+=t*e[i].c;
		}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ1834.in","r",stdin);
	freopen("BZOJ1834.out","w",stdout);
	
	init();
	dinic();
	rebuild();
	mcfx();
	
	return 0;
}
