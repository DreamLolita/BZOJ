#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e4+10;
int a,b,c,d,k,T,ans,cnt;
int mu[MAXN],sum[MAXN],pri[MAXN];
bool isnotpri[MAXN];

void init()
{
	mu[1]=1;
	for(int i=2;i<MAXN;++i)
	{
		if(!isnotpri[i])
		{
			mu[i]=-1;
			pri[++cnt]=i;
		}
		for(int j=1;j<=cnt && i*pri[j]<MAXN;++j)
		{
			isnotpri[i*pri[j]]=true;
			if(i%pri[j]==0)
			{
				mu[i*pri[j]]=0;
				break;
			}
			else
				mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<MAXN;++i)
		sum[i]=sum[i-1]+mu[i];
}

int calc(int n,int m)
{
	if(n>m)
		swap(n,m);
	int ret=0,las=0;
	for(int i=1;i<=n;i=las+1)
	{
		las=min(n/(n/i),m/(m/i));
		ret+=(n/i)*(m/i)*(sum[las]-sum[i-1]);
	}
	return ret;
}

int main()
{
//	freopen("BZOJ2301.in","r",stdin);
//	freopen("BZOJ2301.out","w",stdout);
	
	init();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		--a;--c;
		a/=k;b/=k;c/=k;d/=k;
		ans=calc(b,d)-calc(a,d)-calc(b,c)+calc(a,c);
		printf("%d\n",ans);
	}
	
	return 0;
}
