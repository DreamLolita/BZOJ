#include<bits/stdc++.h>
using namespace std;

int n,mod;
int f[4205][2];

int main()
{
	freopen("BZOJ1925.in","r",stdin);
	freopen("BZOJ1925.out","w",stdout);
	
	scanf("%d%d",&n,&mod);
	f[1][1]=1;
	for(int i=2;i<=n+1;++i)
	{
		int x=(i&1);
		for(int j=1;j<=i;++j)
			f[j][x]=(f[j-1][x]+f[i-j+1][!x])%mod;
	}
	printf("%d\n",f[n+1][(n+1)&1]*2%mod);
	
	return 0;
}
