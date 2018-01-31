#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
map<int,int>mp;

int gcd(int a,int b)
{
	if(a%b==0)
		return b;
	return gcd(b,a%b);
}

void exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int t=x;
	x=y;y=t-a/b*y;
}

LL solve1(int y,int z,int p)
{
	LL ret=1;
	while(z)
	{
		if(z&1)
			ret=1ll*ret*y%p;
		y=1ll*y*y%p;
		z>>=1;
	}
	return ret;
}

void solve2(int y,int z,int p)
{
	int a,b;
	p=-p;
	int t=gcd(y,p);
	if(z%t)
		return (void)puts("Orz, I cannot find x!");
	
	y/=t;z/=t;p/=t;
	exgcd(y,p,a,b);
	a=1ll*a*z%p;
	if(a<0)
		a+=p;
	printf("%d\n",a);
}

void solve3(int y,int z,int p)
{
	y%=p;
	if(!y && !z)
		return (void)puts("1");
	if(!y)
		return (void)puts("Orz, I cannot find x!");
	mp.clear();
	LL trc=ceil(sqrt(p)),t=1;
	mp[1]=trc+1;
	for(LL i=1;i<trc;++i)
	{
		t=1ll*t*y%p;
		if(!mp[t])
			mp[t]=i;
	}
	
	LL tmp=solve1(y,p-trc-1,p),ins=1;
	for(LL i=0;i<trc;++i)
	{
		int j=mp[1ll*z*ins%p];
		if(j)
		{
			if(j==trc+1)
				j=0;
			printf("%lld\n",1ll*i*trc+j);
			return;
		}
		ins=ins*tmp%p;
	}
	puts("Orz, I cannot find x!");
}

int main()
{
//	freopen("BZOJ2242.in","r",stdin);
//	freopen("BZOJ2242.out","w",stdout);
	
	int T,K,y,z,p;
	scanf("%d%d",&T,&K);
	while(T--)
	{
		scanf("%d%d%d",&y,&z,&p);
		if(K==1)
			printf("%d\n",solve1(y,z,p));
		else
		if(K==2)
			solve2(y,z,p);
		else
			solve3(y,z,p);
	}
	
	return 0;
}
