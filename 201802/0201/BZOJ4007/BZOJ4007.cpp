#include<bits/stdc++.h>
using namespace std;

const int N=(1<<11);
const int M=12;
int n,m,ans;
int f[N][N],x[N][M],y[N][M];

void dfs(int u,int sta,int d)
{
	memset(f[u],0,sizeof(f[u]));
	if(d==n)
	{
		f[u][1]=f[u][0]=0;
		for(int i=1;i<n;++i,sta>>=1)
		{
			if(sta&1)	f[u][1]+=x[u][i];
				else	f[u][0]+=y[u][i];
		}
		return;
	}
	int p=n-d-1;
	
	dfs(u<<1,sta<<1,d+1);
	dfs(u<<1|1,sta<<1,d+1);
	for(int i=0,s=(1<<p);i<=s;++i)
		for(int j=0,ns=(1<<p);j<=ns;++j)
			f[u][i+j]=max(f[u][i+j],f[u<<1][i]+f[u<<1|1][j]);
	dfs(u<<1,sta<<1|1,d+1);
	dfs(u<<1|1,sta<<1|1,d+1);
	for(int i=0,s=(1<<p);i<=s;++i)
		for(int j=0,ns=(1<<p);j<=ns;++j)
			f[u][i+j]=max(f[u][i+j],f[u<<1][i]+f[u<<1|1][j]);
}

int main()
{
//	freopen("BZOJ4007.in","r",stdin);
//	freopen("BZOJ4007.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=(1<<(n-1)),s=(1<<n)-1;i<=s;++i)
		for(int j=1;j<n;++j)
			scanf("%d",&x[i][j]);
	for(int i=(1<<(n-1)),s=(1<<n)-1;i<=s;++i)
		for(int j=1;j<n;++j)
			scanf("%d",&y[i][j]);
	dfs(1,0,1);
	for(int i=0;i<=m;++i)
		ans=max(ans,f[1][i]);
	printf("%d\n",ans);
	
	return 0;
}
