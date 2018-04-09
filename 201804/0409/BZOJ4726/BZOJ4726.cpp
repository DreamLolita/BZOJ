#include<bits/stdc++.h>
using namespace std;

const int N=5e5+10;
int n,k,tot;
int siz[N],head[N];
double ans,f[N];

struct Tway
{
	int v,nex;
};
Tway e[N];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

void dfs(int x)
{
	siz[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		dfs(v);
		siz[x]+=siz[v];
	}
	if(!head[x])
		f[x]=1;
	else
	{
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			f[x]=max(f[x],min(1.0*siz[v]/(siz[x]-1),f[v]));
		}
	}
	if(siz[x]>k)
		ans=max(ans,f[x]);
}

int main()
{
	freopen("BZOJ4726.in","r",stdin);
	freopen("BZOJ4726.out","w",stdout);
	
	scanf("%d%d",&n,&k);
	for(int i=2;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		add(x,i);
	}
	dfs(1);
	printf("%0.10lf\n",ans);
	
	return 0;
}
