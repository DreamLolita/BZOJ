#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1005;
int cas,S,T,n,m,A,B;
int ind,top,scc,ans,cost,tot;
int dfn[N],low[N],bl[N],dis[N<<1];
int a[N],b[N],head[N<<1],head2[N<<1];
bool mark[N<<1],inq[N];
stack<int>stk;
queue<int>q;

struct Tway
{
	int v,nex,w,c;
};
Tway e[N*100],mp[N*100];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u],0,0};head[u]=tot;
}

void add2(int u,int v,int w,int c)
{
	mp[++tot]=(Tway){v,head2[u],w,c};head2[u]=tot;
	mp[++tot]=(Tway){u,head2[v],0,-c};head2[v]=tot;
}

void tarjan(int x)
{
	low[x]=dfn[x]=++ind;
	stk.push(x);inq[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else
		if(inq[v])
			low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		int now=0;++scc;
		while(now!=x)
		{
			now=stk.top();stk.pop();
			inq[now]=0;bl[now]=scc;
		}
	}
}

bool spfa()
{
	memset(mark,0,sizeof(mark));
	for(int i=0;i<=S;++i)
		dis[i]=-1;
	while(!q.empty())
		q.pop();
	
	q.push(T);dis[T]=0;mark[T]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();mark[u]=0;
		for(int i=head2[u];i;i=mp[i].nex)
		{
			int v=mp[i].v;
			if(mp[i^1].w && dis[u]+mp[i^1].c>dis[v])
			{
				dis[v]=dis[u]+mp[i^1].c;
				if(!mark[v])
				{
					mark[v]=1;
					q.push(v);
				}
			}
		}
	}
	return ~dis[S];
}

int dfs(int x,int f)
{
	mark[x]=1;
	if(x==T)
		return f;
	int w,used=0;
	for(int i=head2[x];i;i=mp[i].nex)
	{
		int v=mp[i].v;
		if(!mark[v] && mp[i].w && dis[v]+mp[i].c==dis[x])
		{
			w=dfs(v,min(mp[i].w,f-used));
			mp[i].w-=w;mp[i^1].w+=w;cost+=mp[i].c*w;
			used+=w;
			if(used==f)
				return f;
		}
	}
	return used;
}

void solve()
{
	tot=1;T=2*scc+1;S=T+1;

	for(int i=1;i<=A;++i)
		add2(0,bl[a[i]],INF,0);
	for(int i=1;i<=B;++i)
		add2(bl[b[i]]+scc,T,INF,0);		
	
	for(int i=1;i<=n;++i)
		for(int j=head[i];j;j=e[j].nex)
		{
			int v=e[j].v;
			if(bl[i]!=bl[v])
				add2(bl[i]+scc,bl[v],INF,0);
		}
	for(int i=1;i<=scc;++i)
		add2(i,i+scc,1,1),add2(i,i+scc,INF,0);
	add2(S,0,1,0);

	while(spfa())
	{
		int las=cost;
		mark[T]=1;
		while(mark[T])
		{
			memset(mark,0,sizeof(mark));
			dfs(S,INF);
		}

		add2(S,0,1,0);
		if(las==cost)
			break;
		else
			++ans;
	}
	
	if(cost!=scc)
		puts("no solution");
	else
		printf("%d\n",ans);
}

void init()
{
	memset(head,0,sizeof(head));
	memset(head2,0,sizeof(head2));
	memset(dfn,0,sizeof(dfn));
	ans=ind=tot=scc=cost=0;
	
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=A;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=B;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
}

int main()
{
	freopen("BZOJ2893.in","r",stdin);
	freopen("BZOJ2893.out","w",stdout);
	
	scanf("%d",&cas);
	while(cas--)
	{
		init();
		solve();
	}
	
	return 0;
}
