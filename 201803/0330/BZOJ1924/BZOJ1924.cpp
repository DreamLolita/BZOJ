#include<bits/stdc++.h>
using namespace std;

const int N=1e5+3;
int n,r,c,tot,ans,ind,scc;
int head[N],head2[N];
int col[N],low[N],dfn[N],num[N],siz[N];
int dx[]={0,1,1,1,0,-1,-1,-1},dy[]={-1,-1,0,1,1,1,0,-1};
bool vis[N];
stack<int>q;
vector<int>sx[N*10],sy[N*10];
map<int,int>mp[N*10];

struct Tnode
{
	int x,y,t;
};
Tnode a[N];

struct Tway
{
	int v,nex;
};
Tway e[N*10],e2[N*10];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

void build()
{
	for(int i=1;i<=r;++i)
	{
		int x=0;
		for(int j=0;j<sx[i].size();++j)
			if(a[sx[i][j]].t==1)
			{
				x=sx[i][j];
				break;
			}
		if(!x)
			continue;
		for(int j=0;j<sx[i].size();++j)
		{
			if(x==sx[i][j])
				continue;
			add(x,sx[i][j]);
			if(a[sx[i][j]].t==1)
				add(sx[i][j],x);
		}
	}
	for(int i=1;i<=c;++i)
	{
		int x=0;
		for(int j=0;j<sy[i].size();++j)
			if(a[sy[i][j]].t==2)
			{
				x=sy[i][j];
				break;
			}
		if(!x)
			continue;
		for(int j=0;j<sy[i].size();++j)
		{
			if(x==sy[i][j])
				continue;
			add(x,sy[i][j]);
			if(a[sy[i][j]].t==2)
				add(sy[i][j],x);
		}
	}
	for(int i=1;i<=n;++i)
		if(a[i].t==3)
			for(int j=0;j<8;++j)
			{
				int t=mp[a[i].x+dx[j]][a[i].y+dy[j]];
				if(t)
					add(i,t);
			}
	for(int i=0;i<N;++i)
		mp[i].clear();
}

void tarjan(int x)
{
	low[x]=dfn[x]=++ind;
	q.push(x);vis[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else
		if(vis[v])
			low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		int now=0;++scc;
		while(now!=x)
		{
			now=q.top();q.pop();vis[now]=0;
			col[now]=scc;num[scc]++;
		}
	}
}

void rebuild()
{	
	for(int i=1;i<=n;++i)
		head2[i]=head[i],head[i]=0;;
	for(int i=1;i<=tot;++i)
		e2[i]=e[i];//memcpy maybe MLE
	tot=0;
	for(int i=1;i<=n;++i)
		for(int j=head2[i];j;j=e2[j].nex)
		{
			int v=e2[j].v;
			if(col[i]!=col[v])
				add(col[i],col[v]);
		}
}

void dp(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
			dp(v);
		siz[x]=max(siz[x],siz[v]);
	}
	siz[x]+=num[x];
	ans=max(ans,siz[x]);
}

int main()
{
	freopen("BZOJ1924.in","r",stdin);
	freopen("BZOJ1924.out","w",stdout);
	
	scanf("%d%d%d",&n,&r,&c);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].t);
		mp[a[i].x][a[i].y]=i;
		sx[a[i].x].push_back(i);
		sy[a[i].y].push_back(i);
	}
	
	build();
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
			
	rebuild();
	for(int i=1;i<=scc;++i)
		if(!vis[i])
			dp(i);
	printf("%d\n",ans);
	
	return 0;
}
