#include<bits/stdc++.h>
using namespace std;

const int inv=5e8+4;
const int mod=1e9+7;
int T,a,b,n,m,ans;
int p,tim,ta,tb,tp;

int main()
{
	freopen("BZOJ3114.in","r",stdin);
	freopen("BZOJ3114.out","w",stdout);
	
	scanf("%d",&T);
	for(int cas=1;cas<=T;++cas)
	{
		scanf("%d",&n);
		a=b=m=1;
		for(int i=1;i<=n;++i)
		{
			ta=0;tb=0;tp=1;
			scanf("%d%d",&p,&tim);
			for(int j=0;j<tim;++j)
			{
				tb=(tb+tp)%mod;
				tp=(1ll*tp*p)%mod;
			}
			ta=(ta+1ll*tp*(tim+1)%mod)%mod;
			tb=(tb+tp)%mod;
			m=1ll*m*tp%mod;
			a=1ll*((ta+tb-tp)%mod+mod)%mod*a%mod;
			b=1ll*((ta+tb-tp)%mod+mod)%mod*b%mod;
		}
		ans=1ll*(a+b+m*2ll)%mod*inv%mod;
		printf("Case %d: %d\n",cas,ans);
	}
	
	return 0;
}
