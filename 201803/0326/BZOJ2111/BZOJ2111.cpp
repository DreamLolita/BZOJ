#include<bits/stdc++.h>
using namespace std;

const int N=2e6+10;
int n,mod;
int f[N],siz[N],fac[N],inv[N];

void init()
{
	scanf("%d%d",&n,&mod);
	fac[0]=fac[1]=1;inv[0]=inv[1]=1;
	for(int i=2;i<=n;++i)	
		fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*inv[i]*inv[i-1]%mod;
}

int C(int a,int b)
{
	if(a<b)
		return 0;
	if(a<mod && b<mod)
		return 1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;
	return 1ll*C(a/mod,b/mod)*C(a%mod,b%mod)%mod;
}

void solve()
{
	for(int i=n+1;i<=2*n+1;++i)
		f[i]=1,siz[i]=0;
	for(int i=n;i;--i)
	{
		siz[i]=siz[i<<1]+siz[i<<1|1]+1;
		f[i]=1ll*C(siz[i]-1,siz[i<<1])*f[i<<1]%mod*f[i<<1|1]%mod;
	}
	printf("%d\n",f[1]);
}

int main()
{
	freopen("BZOJ2111.in","r",stdin);
	freopen("BZOJ2111.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
