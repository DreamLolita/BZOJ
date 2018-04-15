#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=300;
const int K=255;
int n,m;
LL ans;
LL a[N],f[N][N],g[N][N],dp[N][N];

LL sqr(LL x)
{
	return (LL)x*x;
}

int main()
{
	freopen("2441.in","r",stdin);
	freopen("2441.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int x,num;
		scanf("%d%d",&x,&num);
		a[x]+=num;
	}
	for(int i=0;i<=K;++i)
		for(int j=i;j<=K;++j)
			for(int k=i;k<=j;++k)
				f[i][j]+=a[k]*sqr(k-i),g[i][j]+=a[k]*sqr(j-k);

	memset(dp,127/3,sizeof(dp));ans=dp[0][0];
	for(int i=0;i<=K;++i)
	{
		dp[i][1]=g[0][i];
		for(int j=i-1;j>=0;--j)
		{
			for(int k=2;k<=m;++k)
			{
				int mid=(i+j)>>1;
				LL tmp=f[j][mid]+g[mid+1][i];
//printf("%d %d %lld\n",i,j,tmp);
				dp[i][k]=min(dp[i][k],dp[j][k-1]+tmp);
			}
		}
	}
	
	for(int i=m;i<=K;++i)
		ans=min(ans,dp[i][m]+f[i][K]);
	printf("%lld\n",ans);
	return 0;
}
