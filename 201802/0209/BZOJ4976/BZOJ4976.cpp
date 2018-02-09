#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=1e5+10;
const int M=(1<<17)+10;
const int K=125;
int n,k,ans,fac,mx;
int a[N],f[K][M];

void init()
{
	memset(f,INF,sizeof(f));
	f[0][0]=0;fac=(1<<17);
		
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		mx=max(mx,a[i]);
	}
}

void solve()
{
	if(n>k+log(mx)/log(2))
	{
		for(int i=1;i<=n;++i)
			ans|=a[i];
		printf("%d\n",ans);
		return;
	}
	
	for(int i=0;i<n;++i)
		for(int j=0;j<fac;++j)
			if(f[i][j]<INF)
			{
				f[i+1][j]=min(f[i+1][j],f[i][j]);
				f[i+1][j|a[i+1]]=min(f[i+1][j|a[i+1]],f[i][j]+1);
			}
	for(int i=fac-1;i;--i)
		if(f[n][i]<=n-k)
		{
			ans=i;
			break;
		}
	printf("%d\n",ans);
}


int main()
{
	freopen("BZOJ4976.in","r",stdin);
	freopen("BZOJ4976.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
