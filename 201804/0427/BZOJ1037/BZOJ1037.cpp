#include<bits/stdc++.h>
using namespace std;

const int N=155;
const int K=22;
const int mod=12345678;
int n,m,k,ans;
int f[N*2][N][K][K];

int main()
{
	freopen("BZOJ1037.in","r",stdin);
	freopen("BZOJ1037.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	f[0][0][0][0]=1;
	for(int i=0;i<n+m;++i)
		for(int j=0;j<=n;++j)
			for(int p=0;p<=k;++p)
				for(int q=0;q<=k;++q)
				{
					(f[i+1][j+1][p+1][max(q-1,0)]+=f[i][j][p][q])%=mod;
					(f[i+1][j][max(p-1,0)][q+1]+=f[i][j][p][q])%=mod;
				}
	for(int i=0;i<=k;++i)
		for(int j=0;j<=k;++j)
			(ans+=f[n+m][n][i][j])%=mod;
	printf("%d\n",ans);
	return 0;
}
