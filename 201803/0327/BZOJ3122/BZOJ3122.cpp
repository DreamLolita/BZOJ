#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL T,p,a,b,x1,t,x,y;
map<LL,int>mp;

LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	LL ret=exgcd(b,a%b,x,y);
	LL tmp=x;x=y;y=tmp-a/b*y;
	return ret;
}

LL qpow(LL x,LL y,LL mod)
{
	x%=mod;LL ret=1;
	for(;y;y>>=1,x=x*x%mod)
		if(y&1)
			ret=ret*x%mod;
	return ret;
}

LL bsgs(LL A,LL B,LL C)
{
	A%=C;
	if(!A)
	{
		if(!B)
			return 1;
		return -1;
	}
	LL m=sqrt(C)+1,w=1,k=1,km=qpow(A,C-m-1,C);
	mp.clear();mp[1]=m+1;
	for(int i=1;i<m;++i)
	{
		w=w*A%C;
		if(!mp[w])
			mp[w]=i;
	}
	for(int i=0;i<m;++i)
	{
		int j=mp[B*k%C];
		if(j)
		{
			if(j==m+1)
				j=0;
			return i*m+j;
		}
		k=k*km%C;
	}
	return -1;
}

LL calc1()
{
	LL q=(t-x1+p)%p;
	LL w=exgcd(b,p,x,y);
	if(q%w)
		return -1;
	q/=w;
	x=(x*q%p+p)%p;
	return x+1;
}

LL calc2()
{
	LL q=qpow(a-1,p-2,p),A=(x1+b*q)%p,C=(t+b*q)%p;
	LL w=exgcd(A,p,x,y);
	if(C%w)
		return-1;
	C/=w;
	x=(x%p+p)%p;
	w=bsgs(a,x*C%p,p);
	if(~w)
		return w+1;
	return w;
}

LL solve()
{
	if(x1==t)
		return 1;
	if(a==0)
	{
		if(b==t)	
			return 2;
		return -1;
	}
	if(a==1)
		return calc1();
	return calc2();
}

int main()
{
	freopen("BZOJ3122.in","r",stdin);
	freopen("BZOJ3122.out","w",stdout);
	
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld%lld",&p,&a,&b,&x1,&t);
		printf("%lld\n",solve());
	}
	
	return 0;
}
