#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
const int N=105;
int n,c,k,mx,cnt[N];
double ans,f[N][N],dp[N][N];

void init()
{
	f[0][0]=1;
	for(int i=0;i<=100;++i)
		for(int j=0;j<=i;++j)
			f[i+1][j]+=f[i][j]/2.0,f[i+1][j+1]+=f[i][j]/2.0;
	scanf("%d%d%d",&n,&c,&k);
	for(int i=1;i<=k;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		for(int j=l;j<=r;++j)
			++cnt[j];		
	}		
	for(int i=0;i<=n;++i)
		mx=max(mx,cnt[i]);
}

void solve()
{
	dp[0][1]=1;
	for(int i=0;i<mx;++i)
		for(int j=0;j<c;++j)
			if(dp[i][j]>eps)
				for(int q=0;q<c;++q)
					dp[i+1][j*q%c]+=1.0*dp[i][j]/c;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=cnt[i];++j)
			for(int q=0;q<c;++q)
				ans+=1.0*f[cnt[i]][j]*dp[j][q]*q;
	printf("%.3lf\n",ans);
}

int main()
{
	freopen("2467.in","r",stdin);
	freopen("2467.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
