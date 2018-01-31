#include<bits/stdc++.h>
using namespace std;

const int MAXN=4e5+10; 
int n,m,q,tot1,tot2,tim,cnt,top;
int sta[MAXN],low[MAXN],dfn[MAXN],dfx[MAXN];
int dep[MAXN],ans[MAXN];
int head[MAXN],head2[MAXN],Log[MAXN];
int fa[20][MAXN];

struct Tway
{
	int v,nex;
};
Tway e[MAXN<<1],e2[MAXN<<1];

void add(int u,int v)
{
	++tot1;
	e[tot1].v=v;e[tot1].nex=head[u];head[u]=tot1;
}

void link(int u,int v)
{
	++tot2;
	e2[tot2].v=v;e2[tot2].nex=head2[u];head2[u]=tot2;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	sta[++top]=u;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			
			if(low[v]>=dfn[u])
			{
				++cnt;
				int t;
				do
				{
					t=sta[top--];
					link(cnt,t);link(t,cnt);
				}while(t!=v);
				link(cnt,u);link(u,cnt);
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}

void dfs(int u)
{
	dfx[++dfx[0]]=u;
	for(int i=head2[u];i;i=e2[i].nex)
	{
		int v=e2[i].v;
		if(v!=fa[0][u])
		{
			fa[0][v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
		}
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int i=Log[dep[x]-dep[y]];i>=0;--i)
		if(dep[fa[i][x]]>=dep[y])
			x=fa[i][x];
	if(x==y)
		return x;
//	printf("x:%d y:%d\n",x,y);
	for(int i=Log[dep[x]];i>=0;--i)
		if(fa[i][x]!=fa[i][y])
		{
			x=fa[i][x];
			y=fa[i][y];
			
		}
	return fa[0][x];
}

void get_log()
{
	for(int i=2;i<=cnt;++i)
		Log[i]=Log[i>>1]+1;
}

int main()
{
//	freopen("BZOJ3331.in","r",stdin);
//	freopen("BZOJ3331.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&q);
	cnt=n;
	
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	
	tarjan(1);
	dep[1]=1;
	dfs(1);
	get_log();
	
	for(int j=1;(1<<j)<=cnt;++j)
		for(int i=1;i<=cnt;++i)
			fa[j][i]=fa[j-1][fa[j-1][i]];
			
/*	for(int i=1;i<=cnt;++i)
	{
		for(int j=head2[i];j;j=e2[j].nex)
			printf("%d ",e2[j].v);
		printf("\n");
	}
	for(int j=0;(1<<j)<=cnt;++j)
	{
		for(int i=1;i<=cnt;++i)
			printf("%d ",fa[j][i]);
		printf("\n");
	}
	for(int i=1;i<=cnt;++i)
		printf("%d ",dep[i]);
	printf("\n");*/
	
	for(int i=1;i<=q;++i)
	{
		int u,v,md;
		scanf("%d%d",&u,&v);
		md=lca(u,v);
		++ans[u];++ans[v];--ans[md];--ans[fa[0][md]];
//		printf("%d %d %d\n",u,v,md);
	}
	
	for(int i=cnt;i;--i)
		ans[fa[0][dfx[i]]]+=ans[dfx[i]];
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
