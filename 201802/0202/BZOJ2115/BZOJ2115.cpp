#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,m,tot,cnt;
int head[N],g[N],dep[N];
LL ans,w[N],d[N];
bool vis[N];

struct Tway
{
	int v,nex;
	LL w;
};
Tway e[N<<1];

void add(int u,int v,LL w)
{
	++tot;
	e[tot].v=v;e[tot].w=w;
	e[tot].nex=head[u];head[u]=tot;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;LL w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
}

void dfs(int u)
{
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v])
		{
			if(dep[v]>dep[u])
				w[++cnt]=d[u]^d[v]^e[i].w;
		}
		else
		{
			d[v]=d[u]^e[i].w;g[v]=u;dep[v]=dep[u]+1;
			dfs(v);
		}
	}
}

void Linear_Basis()
{
	int k=1;
	for(int i=63;i>=0;--i)
	{
		int now=k;
		for(;now<=cnt;++now)
			if((w[now]>>i)&1)
				break;
		if(now==cnt+1)
			continue;
		swap(w[now],w[k]);
		for(int j=1;j<=cnt;++j)
			if(k!=j && ((w[j]>>i)&1))
				w[j]^=w[k];	
		++k;		
	}
}

void get_ans()
{
	ans=d[n];
	for(int i=1;i<=min(64,n);++i)
		ans=max(ans,ans^w[i]);
	printf("%lld\n",ans);
}

int main()
{
//	freopen("BZOJ2115.in","r",stdin);	
//	freopen("BZOJ2115.out","w",stdout);
	
	init();
	dfs(1);
	Linear_Basis();
	get_ans();
	
	return 0;
}
