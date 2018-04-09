#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;
int n,m;
LL x,a[N];

int main()
{
	freopen("BZOJ4724.in","r",stdin);
	freopen("BZOJ4724.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		scanf("%lld",&a[i]);
		(x+=a[i]*i)%=(n-1);
	}	
	if(x)
		--a[x];
	for(int i=1;i<n;++i)
		a[i]+=a[i-1];
	while(m--)
	{
		scanf("%lld",&x);++x;
		int l=0,r=n-1,ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a[mid]>=x)
				ans=mid,r=mid-1;
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
