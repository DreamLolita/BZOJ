#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;

int T,n,n1,n2,m,mod,prinum;
int a[N],pri[N],phi[N],fac[N];
LL ans;

inline LL qpow(LL x,int y,int p)
{
	LL ret=1;
	for(;y;y>>=1,x=x*x%p)
		if(y&1)
			ret=ret*x%p;
	return ret;
}

inline void exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b)
		x=1,y=0;
	else
		exgcd(b,a%b,y,x),y-=a/b*x;
}

inline LL inv(LL a,LL b)
{
	if(!a)
		return 0;
	LL x=0,y=0;
	exgcd(a,b,x,y);
	x=(x%b+b)%b;
	if(!x)
		x+=b;
	return x;
}

inline LL mul(int n,int pi,int pk)
{
	if(!n)
		return 1;
	LL ret=1;
	if(n>=pk)
	{
//		for(int i=2;i<pk;++i)
//			if(i%pi)
//				ret=1ll*ret*i%pk;
		ret=qpow(fac[pk],n/pk,pk);
	}
//	for(int i=2;i<=n%pk;++i)
//		if(i%pi)
//			ret=1ll*ret*i%pk;
	ret=1ll*ret*fac[n%pk]%pk;
	return ret*mul(n/pi,pi,pk)%pk;
}

inline LL C(int n,int m,int pi,int pk)
{
	if(m>n)
		return 0;
	fac[0]=1;
	for(int i=1;i<=pk;++i)
		if(i%pi)
			fac[i]=1ll*fac[i-1]*i%pk;
		else
			fac[i]=fac[i-1];
	LL a=mul(n,pi,pk),b=mul(m,pi,pk),c=mul(n-m,pi,pk);
	int k=0;
	for(int i=n;i;i/=pi)
		k+=i/pi;
	for(int i=m;i;i/=pi)
		k-=i/pi;
	for(int i=n-m;i;i/=pi)
		k-=i/pi;
	LL ret=a*inv(b,pk)%pk*inv(c,pk)%pk*qpow(pi,k,pk)%pk;
	return ret*(mod/pk)%mod*inv(mod/pk,pk)%mod;
}

inline LL exlucas(LL n,LL m)
{
	LL ret=0;
	for(int i=1;i<=prinum;++i)
		ret=(ret+C(n,m,phi[i],pri[i]))%mod;
	return ret;
}

inline LL solve(int s)
{
	int opt=0,now=m;
	for(int i=0;i<n1;++i)
		if((s>>i)&1)
			++opt,now-=a[i+1];
	if(now<0)
		return 0;
	if(opt&1)
		opt=-1;
	else
		opt=1;
	return exlucas(now+n-1,n-1)*opt;
}

inline void init()
{
	int x=mod;
	for(int i=2;i*i<=x;++i)
		if(!(x%i))
		{
			phi[++prinum]=i;pri[prinum]=1;
			while(x%i==0)
				pri[prinum]*=i,x/=i;
		}
	if(x>1)
		phi[++prinum]=x,pri[prinum]=x;
}

int main()
{
	freopen("BZOJ3129.in","r",stdin);
	freopen("BZOJ3129.out","w",stdout);
	
	scanf("%d%d",&T,&mod);
	init();
	while(T--)
	{
		scanf("%d%d%d%d",&n,&n1,&n2,&m);m-=n;
		for(int i=1;i<=n1+n2;++i)
			scanf("%d",&a[i]);
		for(int i=n1+1;i<=n1+n2;++i)
			m-=a[i]-1;
		if(m<0)
		{
			puts("0");
			continue;
		}
		ans=0;
		for(int i=0;i<(1<<n1);++i)
			ans=(ans+solve(i))%mod;
		ans=(ans%mod+mod)%mod;
		printf("%lld\n",ans);
	}
	
	return 0;
}
