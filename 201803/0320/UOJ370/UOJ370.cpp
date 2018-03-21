#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e5+10;
int n,mx,sum,a[N];
LL ans,f[N];
bool vis[N];

int main()
{
	freopen("UOJ370.in","r",stdin);
	freopen("UOJ370.out","w",stdout);
	
	scanf("%d",&n);sum=(1<<18)-1;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		sum&=a[i];mx|=a[i];
	}
	mx^=sum;
	for(int i=1;i<=n;++i)
	{
		a[i]^=sum;
		vis[mx^a[i]]=1;
	}
	vis[0]=1;
	for(int i=mx;i;--i)
		for(int j=0;j<=17;++j)
			if((i|(1<<j))<=mx)
				vis[i]|=vis[i|(1<<j)];
	
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=mx;++i)
		if(!(i&sum))
			for(int j=i;j;j=(j-1)&i)
			{
				if((i^j)>f[i])
					break;
				if(vis[j])
					f[i]=min(f[i],f[i^j]+(i^j));
			}
	ans=1ll*sum*n+f[mx];
	printf("%lld\n",ans);
	
	return 0;
}
