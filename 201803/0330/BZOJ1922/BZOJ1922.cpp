#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef pair<int,int> pii;
const int N=3005;
const int M=70005;
int n,m,tot;
int head[N],dis1[N],dis2[N],du[N];
bool vis[N];
vector<int>pro[N];
priority_queue<pii,vector<pii>,greater<pii> >q;

struct Tway
{
	int v,nex,w;
};
Tway e[M];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(u!=v)
			add(u,v,w);
	}
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&du[i]);
		for(int j=1;j<=du[i];++j)
			scanf("%d",&x),pro[x].push_back(i);
	}
}

void dij()
{
	memset(dis1,127/3,sizeof(dis1));
	dis1[1]=dis2[1]=0;q.push(mkp(0,1));
	while(!q.empty())
	{
		int mx=q.top().first,u=q.top().second;q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			dis1[v]=min(dis1[v],mx+e[i].w);
			if(!du[v])
				q.push(mkp(max(dis1[v],dis2[v]),v));
		}
		for(int i=0;i<pro[u].size();++i)
		{
			int v=pro[u][i];
			--du[v];dis2[v]=max(dis2[v],mx);
			if(!du[v])
				q.push(mkp(max(dis1[v],dis2[v]),v));
		}
	}
	printf("%d\n",max(dis1[n],dis2[n]));
}

int main()
{
	freopen("BZOJ1922.in","r",stdin);
	freopen("BZOJ1922.out","w",stdout);
	
	init();
	dij();
	
	return 0;
}
