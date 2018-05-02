#include<bits/stdc++.h>
using namespace std;

const int INF=1e8;
const int N=3e5+10;
const int M=N*8;
int n,id,S,T,sum,tot;
int head[N],dep[N];
queue<int>q;

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int v,nex,w;
};
Tway e[M];

void add(int u,int v,int w)
{
	e[++tot]={v,head[u],w};head[u]=tot;
	e[++tot]={u,head[v],0};head[v]=tot;
}

bool bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[S]=0;q.push(S);
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
	return ~dep[T];
}

int dfs(int u,int f)
{
	if(u==T)
		return f;
	int w,used=0;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].w && dep[v]==dep[u]+1)
		{
			w=dfs(v,min(e[i].w,f-used));
			e[i].w-=w;e[i^1].w+=w;used+=w;
			if(used==f)
				return f;
		}
	}
	if(!used)
		dep[u]=-1;
	return used;
}

int dinic()
{
	int ret=0;
	while(bfs())
		ret+=dfs(S,INF);
	return ret;
}

int main()
{
	freopen("BZOJ3996.in","r",stdin);
	freopen("BZOJ3996.out","w",stdout);
	
	n=read();T=n*n+n+1;id=n;tot=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			int x=read();++id;
			add(i,id,INF);add(j,id,INF);add(id,T,x);
			sum+=x;
		}
	for(int i=1;i<=n;++i)
	{
		int x=read();
		add(S,i,x);
	}
	printf("%d\n",sum-dinic());
	
	return 0;
}
