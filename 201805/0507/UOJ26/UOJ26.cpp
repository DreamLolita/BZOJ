#include "game.h" 
#define N 2005

int n;
int fa[N],siz[N];
int num[N][N];

void initialize(int x)
{
	n=x;
	for(int i=0;i<=n;++i)
		fa[i]=i,siz[i]=1;		
}

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

int hasEdge(int u,int v)
{
	++u;++v; 
	int fu=findf(u),fv=findf(v);
	if(fu==fv)
		return 0;
	if(num[fu][fv]+1==siz[fu]*siz[fv])
	{
		for(int i=1;i<=n;++i)
		{
			num[fu][i]+=num[fv][i];
			num[i][fu]+=num[i][fv];
		}
		fa[fv]=fu;siz[fu]+=siz[fv];
		return 1;
	}
	else
	{
		num[fv][fu]++;num[fu][fv]++;
		return 0;
	}
}
