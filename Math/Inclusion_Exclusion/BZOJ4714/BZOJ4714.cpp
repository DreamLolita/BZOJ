#include<bits/stdc++.h>
using namespace std;

const int mod=1e9+7;
const int N=5e5+10;
int n,ans;
int d[N],f[N],g[N],inv[N];

void init()
{
	scanf("%d",&n);
	f[0]=f[1]=1;
	for(int i=2;i<=n;++i)
		f[i]=1ll*f[i-1]*i%mod;
	inv[0]=inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*(mod-inv[mod%i])*(mod/i)%mod;
	for(int i=1;i<=n;++i)
		inv[i]=1ll*inv[i-1]*inv[i]%mod;
	d[0]=d[2]=1;
	for(int i=3;i<=n;++i)
		d[i]=1ll*(i-1)*(d[i-2]+d[i-1])%mod;
	for(int i=0;i<=n;++i)
		d[i]=1ll*d[i]*inv[i]%mod;
}

void solve()
{
	g[0]=1;
	for(int i=2;i<=n;++i)
	{
		for(int j=1,k=i;k<=n;++j,k+=i)
		{
			g[j]=1ll*g[j-1]*f[k-1]%mod*inv[k-i]%mod;
			int tmp=1ll*d[n-k]*inv[k]%mod*g[j]%mod;
			ans=(ans+((j&1)?tmp:-tmp))%mod;
			if(ans<0)
				ans+=mod;
		}
	}
	ans=1ll*ans*f[n]%mod;
	printf("%d\n",ans);
}

int main()
{
//	freopen("BZOJ4714.in","r",stdin);
//	freopen("BZOJ4714.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
