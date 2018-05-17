#include<bits/stdc++.h>
using namespace std;

const int N=5e4+5;
int prinum,T;
int mu[N],sum[N],pri[N];
bool bo[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

void init()
{
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!bo[i]) 
			pri[++prinum]=i,mu[i]=-1;
		for(int j=1;j<=prinum && pri[j]*i<N;++j)
		{
			bo[pri[j]*i]=1;
			if(i%pri[j]==0)
			{
				mu[i*pri[j]]=0;
				break;
			}
			else
				mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<N;++i)
		sum[i]=sum[i-1]+mu[i];
}

int calc(int n,int m)
{
	if(n>m) swap(n,m);
	int ret=0,pos;
	for(int i=1;i<=n;i=pos+1)
	{
		pos=min(n/(n/i),m/(m/i));
		ret+=(sum[pos]-sum[i-1])*(n/i)*(m/i);
	}
	return ret;
}

int main()
{
	freopen("BZOJ1101.in","r",stdin);
	freopen("BZOJ1101.out","w",stdout);

	init();
	T=read();
	while(T--)
	{
		int x=read(),y=read(),d=read();
		printf("%d\n",calc(x/d,y/d));
	}

	return 0;
}

