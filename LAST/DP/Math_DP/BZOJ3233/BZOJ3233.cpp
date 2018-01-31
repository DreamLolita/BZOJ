#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN=55;
const int MAXM=100005;
const int INF=0xffffff;

int n,tot;
int f[MAXM],prime[MAXM],low[MAXM],val[MAXN];//here low is MAXM
bool flag[MAXM];

void get_prime(int t)
{
	memset(flag,true,sizeof(flag));
	flag[1]=false;
	for(int i=2;i<=t;++i)
	{
		if(flag[i])
		{
			prime[++tot]=i;
			low[i]=i;
		}
		for(int j=1;j<=tot && i*prime[j]<=t;++j)
		{
			flag[i*prime[j]]=false;
			low[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
}


int main()
{
//	freopen("BZOJ3233.in","r",stdin);
//	freopen("BZOJ3233.out","w",stdout);
	
	scanf("%d",&n);
	
	int mx=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&val[i]);
		mx=max(mx,val[i]);
	}
	get_prime(mx);

	for(int i=1;i<=mx;++i)
		f[i]=INF;
	for(int i=mx;i>=1;--i)
	{
		int s=0;
		for(int j=1;j<=n;++j)
			s+=val[j]/i;
		f[i]=min(f[i],s);
		int x=i;
		while(x>1)
		{
			int y=i/low[x],s=0;
			for(int j=1;j<=n;++j)
				s+=val[j]%i/y;
			f[y]=min(f[y],f[i]+s);
			y=low[x];
			while(x%y==0)
				x/=y;
		}
	}

	printf("%d\n",f[1]);
}
