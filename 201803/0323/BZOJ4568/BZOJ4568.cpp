#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2e4+10;
const int M=16;
const int K=63;
int n,m,tot;
int head[N],dep[N],fa[N][M];
LL a[K],f[N][M][K];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void addedge(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void add(LL *x,LL y)
{
	for(int i=60;~i;--i)
		if(y&(1ll<<i))
		{
			if(!x[i])
			{
				x[i]=y;
				return;
			}
			else
				y^=x[i];
		}
}

void merge(LL *x,LL *y)
{
	for(int i=60;~i;--i)
		if(y[i])
			add(x,y[i]);
}

void dfs(int x)
{
	dep[x]=dep[fa[x][0]]+1;
	for(int i=1;i<M;++i)
		if(fa[x][i-1])
		{
			fa[x][i]=fa[fa[x][i-1]][i-1];
			memcpy(f[x][i],f[x][i-1],sizeof(f[x][i-1]));
			merge(f[x][i],f[fa[x][i-1]][i-1]);
		}
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[x][0])
			continue;
		fa[v][0]=x;
		dfs(v);
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int tmp=(dep[x]-dep[y]);
	for(int i=M-1;~i;--i)
		if(tmp&(1<<i))
		{
			merge(a,f[x][i]);
			x=fa[x][i];
		}
	if(x==y)
		return x;
	for(int i=M-1;~i;--i)
		if(fa[x][i]!=fa[y][i])
		{
			merge(a,f[x][i]);merge(a,f[y][i]);
			x=fa[x][i];y=fa[y][i];
		}
	merge(a,f[x][0]);merge(a,f[y][0]);
	return fa[x][0];
}

void get_ans()
{
	LL ans=0;
	for(int i=K-1;~i;--i)
		ans=max(ans,ans^a[i]);
	printf("%lld\n",ans);
}

int main()
{
	freopen("BZOJ4568.in","r",stdin);
	freopen("BZOJ4568.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		LL x;
		scanf("%lld",&x);
		add(f[i][0],x);
	}
	
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	dfs(1);
	
	for(int i=1;i<=m;++i)
	{
		memset(a,0,sizeof(a));
		int x,y,z;
		scanf("%d%d",&x,&y);z=lca(x,y);
		merge(a,f[z][0]);
		get_ans();
	}
	return 0;
}
