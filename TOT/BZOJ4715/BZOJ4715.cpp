#include<bits/stdc++.h>
using namespace std;

const int N=10005;
const int mod=1e9+7;
int n,m,res;
int cnt[N],f[N],a[N];
bool vis[N];

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(u<v) ++cnt[u];
		   else ++cnt[v];
	}
	
	int j;
	for(int i=1;i<=n;++i)
	{
		++cnt[i];
		for(j=1;j<=n;++j)
			if(!vis[j])
			{
				--cnt[i];
				if(!cnt[i])
					break;
			}
		a[i]=j;
		vis[j]=true;
	}
}

void solve()
{
	f[0]=1;
	for(int i=1;i<=n;++i)
	{
		int res=-1;
		for(int j=i-1;j>=0;--j)
		{
			if(a[j]<a[i] && res<a[j])
				f[i]=(f[i]+f[j])%mod;		
			if(a[j]<a[i])
				res=max(res,a[j]);
		}
	}
	
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		int flag=1;
		for(int j=i+1;j<=n;++j)
			if(a[j]>a[i])
			{
				flag=0;
				break;
			}
		ans=(ans+flag*f[i])%mod;
	}
	printf("%d\n",ans);
}

int main()
{
//	freopen("senritsu.in","r",stdin);
//	freopen("senritsu.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
