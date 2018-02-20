#include<bits/stdc++.h>
using namespace std;

const int mod=998244353;
const int N=15;
int n,m,ans;
int a[N],f[N],g[N],nex[N];

void dfs(int x,int y)
{
	if(x>n)
	{
		int j=0,k=1;
		for(int i=2;i<=n;nex[i++]=j)
		{
			while(j && a[j+1]!=a[i])
				j=nex[j];
			if(a[j+1]==a[i])
				++j;
			k*=i-j;
		}
		g[y]=(g[y]+k)%mod;
		return;
	}
	for(int i=1;i<=y;++i)
		a[x]=i,dfs(x+1,y);
	a[x]=y+1;dfs(x+1,y+1);
}

int main()
{
	freopen("BZOJ5130.in","r",stdin);
	freopen("BZOJ5130.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	f[0]=1;
	for(int i=1;i<=n;++i)
		f[i]=1ll*f[i-1]*(m-i+1)%mod;
	dfs(1,0);
	for(int i=1;i<=n;++i)
		ans=(1ll*f[i]*g[i]+ans)%mod;
	printf("%d\n",ans);
	
	return 0;
}
