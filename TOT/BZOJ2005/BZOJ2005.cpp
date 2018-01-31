#include<bits/stdc++.h>
using namespace std;

typedef long long LL; 
const int MAXN=1e5+10;
int n,m,t,cnt;
LL ans;
LL phi[MAXN],pri[MAXN],sum[MAXN];
bool isnotpri[MAXN];

void init()
{
	scanf("%d%d",&n,&m);
	t=min(n,m);
	
	phi[1]=1;
	for(int i=2;i<MAXN;++i)
	{
		if(!isnotpri[i])
		{
			pri[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt && i*pri[j]<MAXN;++j)
		{
			isnotpri[i*pri[j]]=true;
			if(i%pri[j])
				phi[i*pri[j]]=phi[i]*(pri[j]-1);
			else
			{
				phi[i*pri[j]]=phi[i]*pri[j];
				break;				
			}
		}
	}
	for(int i=1;i<MAXN;++i)
		sum[i]=sum[i-1]+phi[i];
}


void solve()
{
	int las=0;
	for(int i=1;i<=t;i=las+1)
	{
		las=min(n/(n/i),m/(m/i));
		ans+=1ll*(n/i)*(m/i)*(sum[las]-sum[i-1]);
	}
	ans=2ll*ans-1ll*n*m;
	printf("%lld\n",ans);
}

int main()
{
//	freopen("BZOJ2005.in","r",stdin);
//	freopen("BZOJ2005.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
