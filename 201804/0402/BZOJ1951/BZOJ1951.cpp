#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=999911659;
int n,g,ans;
int t[]={2,3,4679,35617};
int r[4],fac[5][40000];

int qpow(LL x,int y,LL p)
{
	x%=p;
	LL ret=1;
	for(;y;y>>=1,x=x*x%p)
		if(y&1)
			ret=ret*x%p;
	return ret;
}

int C(int x,int y,int p)
{
	if(y<x)
		return 0;
	return 1ll*fac[p][y]*qpow(1ll*fac[p][x]*fac[p][y-x],t[p]-2,t[p])%t[p];
}

int Lucas(int x,int y,int p)
{
	if(y==0)
		return 1;
	return 1ll*C(x%t[p],y%t[p],p)*Lucas(x/t[p],y/t[p],p)%t[p];
}

void exgcd(int a,int b,LL &x,LL &y)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}

int CRT()
{
	LL x,y,q=t[0],p=r[0];
	for(int i=1;i<4;++i)
	{
		int tq=t[i],tp=r[i];
		exgcd(q,tq,x,y);
		x=((tp-p)*x%tq+tq)%tq;
		p+=q*x;q*=tq;
	}
	return p;
}

int main()
{
	freopen("BZOJ1951.in","r",stdin);
	freopen("BZOJ1951.out","w",stdout);
	
	scanf("%d%d",&n,&g);
	if(g==mod)
	{
		puts("0");
		return 0;
	}
	for(int i=0;i<4;++i)
	{
		fac[i][0]=1;
		for(int j=1;j<=t[i];++j)
			fac[i][j]=fac[i][j-1]*j%t[i];
	}
	for(int i=0;i<4;++i)
		for(int j=1;j*j<=n;++j)
			if(n%j==0)
			{
				r[i]=(r[i]+Lucas(j,n,i))%t[i];
				if(j*j!=n)
					r[i]=(r[i]+Lucas(n/j,n,i))%t[i];
			}
	ans=qpow(g,CRT(),mod);
	printf("%d\n",ans);
	
	return 0;
}
