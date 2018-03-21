#include<bits/stdc++.h>
using namespace std;

const int INF=1e8;
const int N=2005;
int n,m,T,ans,tot=1;
int a[N],head[N],dis[N],from[N];
bool inq[N];
queue<int>q;

struct Tway
{
	int u,v,nex,w,c; 
};
Tway e[N*20];

void add(int u,int v,int w,int c)
{
	e[++tot]=(Tway){u,v,head[u],w,c};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v],0,-c};head[v]=tot;
}

bool spfa()
{
	for(int i=0;i<=T;++i)
		dis[i]=INF,inq[i]=false;
	while(!q.empty())
		q.pop();
	dis[0]=0;q.push(0);inq[0]=1;
	while(!q.empty())
	{
		int now=q.front();q.pop();inq[now]=false;
		for(int i=head[now];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && e[i].c+dis[now]<dis[v])
			{
				dis[v]=e[i].c+dis[now];
				from[v]=i;
				if(!inq[v])
				{
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[T]!=INF;
}

void mcfx()
{
	int t=INF;
	for(int i=from[T];i;i=from[e[i].u])
		t=min(t,e[i].w);
	for(int i=from[T];i;i=from[e[i].u])
	{
		ans+=t*e[i].c;
		e[i].w-=t;e[i^1].w+=t;
	}
}


int main()
{
	freopen("BZOJ1927.in","r",stdin);
	freopen("BZOJ1927.out","w",stdout);
	
	scanf("%d%d",&n,&m);T=2*n+1;
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		add(0,i,1,0);
		add(i+n,T,1,0);
		add(0,i+n,1,a[i]);
	}
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(u>v)
			swap(u,v);
		add(u,v+n,1,w);
	}
	while(spfa())
		mcfx();
	printf("%d\n",ans);
	
	return 0;
}
