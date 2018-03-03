#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=222;
const int M=1e5+10;
int n,m,s,t,tot=1;
int head[N],pre[N],from[N],dis[N];
queue<int>q;

struct Tway
{
	int v,nex,val,cost;
};
Tway e[M];

void add(int u,int v,int w,int c)
{
	e[++tot]={v,head[u],w,c};head[u]=tot;
	e[++tot]={u,head[v],0,-c};head[v]=tot;
}

bool spfa()
{
	memset(dis,0x3f,sizeof(dis));
	memset(from,-1,sizeof(from));
	dis[s]=0;q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].val && dis[v]>dis[u]+e[i].cost)
			{
				dis[v]=dis[u]+e[i].cost;
				from[v]=u;pre[v]=i;
				q.push(v);
			}
		}
	}
	return ~from[t];
}

int EK()
{
	int ret=0,k;
	while(spfa())
	{
		k=INF;
		for(int i=t;i!=s;i=from[i])
			k=min(k,e[pre[i]].val);
		ret+=k*dis[t];
		for(int i=t;i!=s;i=from[i])
			e[pre[i]].val-=k,e[pre[i]^1].val+=k;
	}
	return ret;
}

int main()
{
	freopen("BZOJ4108.in","r",stdin);
	freopen("BZOJ4108.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	s=2*n+2;t=2*n+3;add(0,1,m,0);
	for(int i=2;i<=n+1;++i)
	{
		int x;
		scanf("%d",&x);
		add(1,i,INF,x);add(s,i+n,1,0);
		add(i,t,1,0);add(i+n,0,INF,0);
	}
	for(int i=2;i<=n;++i)
		for(int j=i+1;j<=n+1;++j)
		{
			int x;
			scanf("%d",&x);
			add(i+n,j,INF,x);
	}
	
	printf("%d\n",EK());
	return 0;
}
