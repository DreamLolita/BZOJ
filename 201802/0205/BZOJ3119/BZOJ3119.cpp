#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
LL n,x,a,b,m;
LL ans[N];

int main()
{
	freopen("BZOJ3119.in","r",stdin);
	freopen("BZOJ3119.out","w",stdout);
	
	scanf("%lld%lld%lld%lld%lld",&n,&x,&a,&b,&m);
	LL d=(n*(n-1)/2*a-m+n*x)/(a+b);
	for(int i=n-1;i>=1;--i)
	{
		if(d>i)
		{
			ans[n-i+1]=-1;
			d-=i;
		}
		else
		{
			ans[n-d+1]=-1;
			break;
		}
	}
	ans[1]=x;
	for(int i=2;i<=n;++i)
		if(ans[i]==-1)
			ans[i]=ans[i-1]-b;
		else
			ans[i]=ans[i-1]+a;
	for(int i=1;i<=n;++i)
		printf("%lld\n",ans[i]);
	
	return 0;
}
