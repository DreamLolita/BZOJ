#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2e5+10;
int n,tot,len,l,r,rt;
int head[N],fa[N],chain[N];
LL mx,mx2;
LL dis[N],dis2[N];
bool vis[N];

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

void dfs(int x,int f)
{
	fa[x]=f;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=f)
		{
			dis[v]=dis[x]+e[i].w;
			if(dis[v]>mx)
				mx=dis[v],rt=v;
			dfs(v,x);
		}
	}
}

void get_chain(int x)
{
	while(x)
	{
		vis[x]=true;
		chain[++len]=x;
		x=fa[x];
	}
}

void dfs2(int x,int f)
{
	vis[x]=true;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=f && !vis[v])
		{
			dis2[v]=dis2[x]+e[i].w;
			mx2=max(mx2,dis2[v]);
			dfs2(v,x);
		}
	}
}

int main()
{
	freopen("BZOJ3124.in","r",stdin);
	freopen("BZOJ3124.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	dfs(1,0);
	memset(dis,0,sizeof(dis));mx=0;
	dfs(rt,0);
	get_chain(rt);
	l=len;r=1;
	for(int i=len;i;--i)
	{
		mx2=0;dfs2(chain[i],0);
		if(!mx2)
			continue;
		if(mx2==dis[chain[i]])
			l=i;
		if(mx2==mx-dis[chain[i]])
		{
			r=i;
			break;
		}		
	}
	printf("%lld\n%d\n",mx,l-r);
	
	return 0;
}
