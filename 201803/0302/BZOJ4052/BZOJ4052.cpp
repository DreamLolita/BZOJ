#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int K=50;
int n,T;
int sum[N],gs[N][K];
LL ans;
LL a[N];

LL gcd(LL x,LL y)
{
	if(x%y==0)
		return y;
	return gcd(y,x%y);
}

int main()
{
	freopen("BZOJ4052.in","r",stdin);
	freopen("BZOJ4052.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			scanf("%lld",&a[i]);
			ans=max(ans,a[i]);
		}
		sum[n]=0;
		for(int i=n-1;i;--i)
		{
			sum[i]=1;gs[i][1]=i+1;
			LL t=gcd(a[i],a[i+1]);
			for(int j=1;j<=sum[i+1];++j)
				if(a[gs[i+1][j]]%t)
				{
					LL tmp=1ll*t*(gs[i+1][j]-i);
					ans=max(ans,tmp);
					t=gcd(t,a[gs[i+1][j]]);
					gs[i][++sum[i]]=gs[i+1][j];
				}
			ans=max(ans,1ll*t*(n-i+1));
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
