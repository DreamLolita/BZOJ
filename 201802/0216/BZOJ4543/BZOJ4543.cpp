#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;

int n,tot;
int head[N],son[N],dep[N],h[N],mx[N],siz[N];
LL id,ans;
LL mem[10*N],*f[N],*g[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;mx[u]=u;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		dfs(v,u);
		if(dep[mx[v]]>dep[mx[son[u]]])
			son[u]=v;
		if(dep[mx[v]]>dep[mx[u]])
			mx[u]=mx[v];
	}
	siz[mx[u]]=h[u]=dep[mx[u]]-dep[u]+1;
}

void init()
{
	for(int i=1;i<=n;++i)
	{
		if(mx[i]!=i)
			continue;
		id+=siz[i]-1;
		f[i]=&mem[id];++id;
		g[i]=&mem[id];id+=2*siz[i]+2;
	}
}

void solve(int u,int fa)
{
	if(mx[u]==u)
	{
		f[u][0]=1;
		return;
	}
	solve(son[u],u);
	f[u]=f[son[u]]-1;g[u]=g[son[u]]+1;
	ans+=g[u][0];f[u][0]=1;
	
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa || v==son[u])
			continue;
		solve(v,u);
		
		for(int i=0;i<=h[v];++i)
			ans+=f[v][i]*g[u][i+1];
		for(int i=1;i<=h[v];++i)
			ans+=g[v][i]*f[u][i-1];
		
		for(int i=0;i<=h[v];++i)
			g[u][i+1]+=f[v][i]*f[u][i+1];
		for(int i=1;i<=h[v];++i)
			g[u][i-1]+=g[v][i];
		
		for(int i=0;i<=h[v];++i)
			f[u][i+1]+=f[v][i];
	}
}

int main()
{
	freopen("BZOJ4543.in","r",stdin);
	freopen("BZOJ4543.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0);
	init();
	solve(1,0);
	printf("%lld\n",ans);
	
	return 0;
}
