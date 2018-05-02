#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y) 
using namespace std;

typedef pair<int,int> pii;
const int INF=1e9;
const int N=1e4+10;
const int M=4e5+10;
int n,m,S,T,tot,cnt;
int head[N],head2[N],dis[N],mi[N];
bool vis[N];
priority_queue<pii,vector<pii>,greater<pii> > q;

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int v,nex,w;
	Tway(){}
	Tway(int vv,int nexx,int ww){
		v=vv;nex=nexx;w=ww;
	}
};
Tway e[M],mp[M];

void add(int u,int v,int w)
{	
	e[++tot]=Tway(v,head[u],w);
	head[u]=tot;
}

void adde(int u,int v,int w)
{
	mp[++cnt]=Tway(v,head2[u],w);
	head2[u]=cnt;
}

void rebuild()
{
	++T;
	for(int u=1;u<=n;++u)
	{
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(u==1)
			{
				if(mi[v]!=v)
					adde(1,v,e[i].w);
			}
			if(v==1)
			{
				if(mi[u]!=u)
					adde(1,T,dis[u]+e[i].w);
				else
					adde(u,T,e[i].w);
			}
			if(u^1 && v^1)
			{
				if(mi[u]^mi[v])
					adde(1,v,dis[u]+e[i].w);
				else
					adde(u,v,e[i].w);
			}
		}
	}
	tot=cnt;
	memcpy(head,head2,sizeof(head2));
	memcpy(e,mp,sizeof(mp));
}

void dij()
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=T;++i)
		dis[i]=INF;
	dis[S]=0;q.push(mkp(dis[S],S));
	while(!q.empty())
	{
		int u=q.top().second;q.pop();
//printf("%d %d\n",u,dis[u]);
		if(vis[u])
			continue;
		vis[u]=1;
//printf("%d\n",head[u]);
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
//printf("%d %d %d\n",dis[u],e[i].w,dis[v]);
			if(dis[u]+e[i].w<dis[v])
			{
				dis[v]=dis[u]+e[i].w;
				if(u==1)
					mi[v]=v;
				else
					mi[v]=mi[u];
				q.push(mkp(dis[v],v));
			}
		}
	}
}

int main()
{
	freopen("BZOJ2407.in","r",stdin);
	freopen("BZOJ2407.out","w",stdout);
	
	n=read();m=read();S=1;T=n;
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read(),w1=read(),w2=read();
		add(u,v,w1);add(v,u,w2);
	}
	dij();
	rebuild();
	dij();
	if(dis[T]==INF)
		dis[T]=-1;
	printf("%d\n",dis[T]);
	
	return 0;
}
