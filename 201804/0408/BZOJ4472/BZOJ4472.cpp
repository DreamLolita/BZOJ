#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,tot;
int a[N],f[N],g[N];
int val[N],lim[N],head[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

bool cmp(int x,int y)
{
	return f[x]>f[y];
}

void dfs(int x,int fa)
{
	int cnt=0,p=0;
	f[x]=val[x];
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=fa)
			dfs(v,x);
	}
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=fa)
			a[++cnt]=v;
	}
	sort(a+1,a+cnt+1,cmp);
	while(p<min(lim[x]-1,cnt) && f[a[p+1]]>=0)
	{
		++p;
		f[x]+=f[a[p]];g[x]|=g[a[p]];
	}
	if((p>0 && p<cnt && f[a[p]]==f[a[p+1]]) || (f[a[p]]==0 && p>0))
		g[x]=1;
}

int main()
{
	freopen("BZOJ4472.in","r",stdin);
	freopen("BZOJ4472.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
		scanf("%d",&val[i]);
	for(int i=2;i<=n;++i)
		scanf("%d",&lim[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	lim[1]=n+1;
	dfs(1,0);
//	for(int i=1;i<=n;++i)
//		printf("%d\n",f[i]);
	printf("%d\n",f[1]);
	if(g[1])
		puts("solution is not unique");
	else
		puts("solution is unique");
	
	return 0;
}
