#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAXN=5e4+10;
LL n,L;
LL sum[MAXN],f[MAXN],g[MAXN],s[MAXN];
LL q[MAXN<<1],h,t;

inline LL sqr(LL x)
{
	return x*x;
}

inline LL cross(LL xa,LL ya,LL xb,LL yb)
{
	return xa*yb-xb*ya;
}

int main()
{
//	freopen("BZOJ1010.in","r",stdin);
//	freopen("BZOJ1010.out","w",stdout);
	
	scanf("%lld%lld",&n,&L);
	++L;
	for(LL i=1;i<=n;++i)
	{
		LL x;
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
		s[i]=sum[i]+i;
	}
	memset(f,127,sizeof(f));
	f[0]=0;h=1;t=0;
	q[++t]=0;
	for(LL i=1;i<=n;++i)
	{
		while(t-h+1>=2 && ( ((g[q[h+1]]-g[q[h]])*1.0/(s[q[h+1]]-s[q[h]])) < (s[i]*2-L*2)) ) 
			++h;
		f[i]=f[q[h]]+sqr(s[i]-s[q[h]]-L);
		g[i]=f[i]+sqr(s[i]);
		
		while(t-h+1>=2 && cross(s[q[t]]-s[q[t-1]] , g[q[t]]-g[q[t-1]] , s[i]-s[q[t]] ,g[i]-g[q[t]])<0 )
			--t;
		q[++t]=i;
	}
	printf("%lld\n",f[n]);
	
	return 0;
}
