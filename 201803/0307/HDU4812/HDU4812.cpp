#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int mod=1e6+3;
const int INF=1e9;
int n,k,tot,rt,sum,top,ans1,ans2;
int id[N],f[N],siz[N],head[N];
LL tmp[N],val[N],dis[N];
LL inv[mod],mp[mod];
bool vis[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void init()
{
	inv[1]=1;
	for(int i=2;i<mod;++i)
	{
		int x=mod/i,y=mod%i;
		inv[i]=(inv[y]*(-x)%mod+mod)%mod;
	}
}

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void getroot(int x,int fa)
{
	f[x]=0;siz[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			getroot(v,x);
			siz[x]+=siz[v];
			f[x]=max(f[x],siz[v]);
		}
	}
	f[x]=max(f[x],sum-siz[x]);
	if(f[x]<f[rt])
		rt=x;
}

void dfs(int x,int fa)
{
	tmp[++top]=dis[x];id[top]=x;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			dis[v]=(dis[x]*val[v])%mod;
			dfs(v,x);
		}
	}
}

void query(int x,int id)
{
	x=inv[x]*k%mod;
	int y=mp[x];
	if(y==0)
		return;
	if(y>id)
		swap(y,id);
	if(y<ans1 || (y==ans1 && id<ans2))
		ans1=y,ans2=id;
}

void solve(int x)
{
	vis[x]=1;mp[val[x]]=x;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			top=0;dis[v]=val[v];
			dfs(v,x);
			for(int j=1;j<=top;++j)
				query(tmp[j],id[j]);
			top=0;dis[v]=(val[x]*val[v])%mod;
			dfs(v,x);
			for(int j=1;j<=top;++j)
			{
				int t=mp[tmp[j]];
				if(!t || id[j]<t)
					mp[tmp[j]]=id[j];
			}
		}
	}
	mp[val[x]]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			top=0;dis[v]=(val[x]*val[v])%mod;
			dfs(v,x);
			for(int j=1;j<=top;++j)
				mp[tmp[j]]=0;
		}
	}
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			rt=0;sum=siz[v];
			getroot(v,0);
			solve(rt);
		}
	}
}

void _reset()
{
	memset(vis,0,sizeof(vis));
	memset(head,0,sizeof(head));
	tot=0;ans1=ans2=INF;
}

int main()
{
	freopen("HDU4812.in","r",stdin);
	freopen("HDU4812.out","w",stdout);
	
	init();
	while(~scanf("%d%d",&n,&k))
	{
		_reset();
		for(int i=1;i<=n;++i)
			scanf("%d",&val[i]);
		for(int i=1;i<n;++i)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
		}
		rt=0;sum=n;f[0]=n+1;
		getroot(1,0);
		solve(rt);
		if(ans1==INF) puts("No solution");
		else printf("%d %d\n",ans1,ans2);
	}
	
	return 0;
}
