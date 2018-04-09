#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1e10;
const int N=1e4+5;
int n,q,cnt;
int ans1[N],ans2[N];
LL a[N],c[N];
map<LL,int>mp;

int calc(int x)
{
	int l=1,r=cnt,ret=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(c[mid]<=x)
			l=mid+1,ret=mid;
		else
			r=mid-1;
	}
	return ret;
}

int main()
{
	freopen("BZOJ4725.in","r",stdin);
	freopen("BZOJ4725.out","w",stdout);
	
	a[1]=c[1]=cnt=1;a[2]=2;
	for(int i=3;a[i-1]<=INF || (!(i&1));++i)
	{
		if(i&1)
			a[i]=a[i-1]<<1ll;
		else
		{
			int j;
			for(j=1;j<cnt;++j)
				if(c[j+1]!=c[j]+1)
					break;
			a[i]=a[i-1]+c[j]+1;		
		}		
		for(int j=1;j<i;++j)
			c[++cnt]=a[i]-a[j];
		sort(c+1,c+cnt+1);
		n=i+1;	
	}	
	for(int i=1;i<=cnt;++i)
		if(c[i]>1e9)
			c[i]=INF+1;
	sort(c+1,c+cnt+1);
	while(c[cnt]>INF)
		--cnt;
	for(int i=1;i<=cnt;++i)
		mp[c[i]]=i;

	for(int i=1;i<n-1;++i)
		for(int j=i+1;j<n;++j)
			if(mp[a[j]-a[i]])
			{
				int t=mp[a[j]-a[i]];
				ans1[t]=j;ans2[t]=i;
			}
	scanf("%d",&q);
	while(q--)
	{
		int x,t;
		scanf("%d",&x);t=mp[x];
		if(t)
			printf("%d %d\n",ans1[t],ans2[t]);
		else
		{
			LL ret=x-calc(x);
			printf("%lld %lld\n",n+ret*2ll-1,n+ret*2ll-2);
		}
	}
	
	return 0;
}
