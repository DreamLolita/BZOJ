#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=1e7+10;
int n,ans,tot;
int a[N],b[N],c[N],d[N],f[N];

int main()
{
	freopen("BZOJ3704.in","r",stdin);
	freopen("BZOJ3704.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
	{
		c[i]=b[i]-a[i];
		if(c[i]<c[i-1])
			c[i]+=(c[i-1]-c[i])/4*4;
		if(c[i]<c[i-1])
			c[i]+=4;
		f[i]=c[i]/4;
		d[i]=c[i]-c[i-1];
	}
	
	ans=c[n];f[n+1]=INF;tot=0;
	for(int i=1;i<=n;++i)
		if(d[i]==3 && f[i]>tot)
		{
			d[i]-=4;ans-=3;
			++tot;
		}
	for(int i=1;i<=n;++i)
		c[i]=c[i-1]+d[i];
	for(int i=n;i;--i)
		f[i]=min(c[i]/4,f[i+1]);
	tot=0;
	for(int i=1;i<=n;++i)
		if(d[i]==2 && f[i]>tot)
		{
			d[i]-=4;ans-=2;
			++tot;
		}
	for(int i=1;i<=n;++i)
		c[i]=c[i-1]+d[i];
	for(int i=n;i;--i)
		f[i]=min(c[i]/4,f[i+1]);
	tot=0;
	for(int i=n;i;--i)
		if(d[i]==1 && f[i]>tot)
		{
			d[i]-=4;--ans;
			++tot;
		}
	printf("%d\n",ans);
	
	return 0;
}
