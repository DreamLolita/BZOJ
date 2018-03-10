#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=855;
int cas,n,m,qur,S,T,tot,cnt;
int dep[N],head[N],mark[N],qs[N],a[N];
int ans[N][N];
queue<int>q;
map<int,bool>mp;

struct Tway
{
	int v,nex,w;
};
Tway e[N*100];

inline void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

inline bool bfs()
{
	memset(dep,-1,sizeof(dep));
	while(!q.empty())
		q.pop();
	q.push(S);dep[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dep[v]==-1 && e[i].w)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return ~dep[T];
}

inline int dfs(int x,int f)
{
	if(x==T)
		return f;	
	int used=0,w;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dep[v]==dep[x]+1)
		{
			w=dfs(v,min(e[i].w,f-used));
			e[i].w-=w;e[i^1].w+=w;
			used+=w;
			if(used==f)
				return f;
		}
	}
	if(used==0)
		dep[x]=-1;
	return used;
}

inline int dinic()
{
	int ret=0;
	while(bfs())
		ret+=dfs(S,INF);
	return ret;
}

inline void mpdfs(int u)
{
	mark[u]=1;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].w && !mark[v])
			mpdfs(v);
	}
}

inline void rebuild(int l,int r)
{
	for(int i=2;i<=tot;i+=2)
		e[i].w=e[i^1].w=(e[i].w+e[i^1].w)/2;
	S=a[l];T=a[r];
	memset(mark,0,sizeof(mark));
}

inline void solve(int l,int r)
{

	if(l==r)
		return;
	rebuild(l,r);
	int t=dinic();
	mpdfs(S);
	if(!mp[t])
		cnt++,mp[t]=true;
	
	int L=l,R=r;
	for(int i=l;i<=r;++i)
		if(mark[a[i]])
			qs[L++]=a[i];
		else
			qs[R--]=a[i];
	for(int i=l;i<=r;++i)
		a[i]=qs[i];
	solve(l,L-1);solve(R+1,r);
}

inline void _reset()
{
	tot=1;
	memset(ans,127,sizeof(ans));
	memset(head,0,sizeof(head));
}

inline void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		a[i]=i;
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
}

inline void get_sol()
{
	solve(1,n);
	printf("%d\n",cnt);
}

int main()
{
	freopen("BZOJ4519.in","r",stdin);
	freopen("BZOJ4519.out","w",stdout);
	
	_reset();
	init();
	get_sol();
	
	return 0;
}
