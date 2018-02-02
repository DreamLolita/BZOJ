#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=19940417;
const int N=1e6+10;
LL n,m,mx;
LL f[N][2];

struct Tnode
{
	LL x,y,w;
};
Tnode a[N];

LL read()
{
    LL x=0,t=1;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')
		ch=getchar();
    if(ch=='-')
		t=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
		x=x*10+ch-48,ch=getchar();
    return x*t;
}

bool cmp(Tnode A,Tnode B)
{
	return A.x<B.x;
}

LL qpow(LL k)
{
	LL ret=1,x=2;
	for(;k;k>>=1,x=(x*x)%mod)
		if(k&1)
			ret=(ret*x)%mod;
	return ret;
}

int main()
{
//	freopen("BZOJ3215.in","r",stdin);
//	freopen("BZOJ3215.out","w",stdout);
		
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		a[i].x=read();a[i].y=read();
		a[i].w=i;
	}
	a[m+1].x=n;a[m+1].w=m+1;
	sort(a+1,a+m+1,cmp);
	
	f[0][0]=0;f[0][1]=1;
	for(int i=1;i<=m+1;++i)
	{
		int X=a[i].x-a[i-1].x;
		int Y=(X-a[i].y-a[i-1].y)>>1;
	
		mx=max(mx, a[i-1].y+((a[i].x-a[i-1].x+a[i].y-a[i-1].y)>>1) );
		if(a[i].x==a[i-1].x)
		{
			f[i][0]=f[i-1][0];f[i][1]=f[i-1][1];
			continue;
		}
		
		if(Y<=0)
		{
			if(a[i].y-a[i-1].y==a[i].x-a[i-1].x)
			{
				f[i][0]=f[i-1][0];
				if(a[i-1].y==0)
					f[i][0]=f[i-1][1];
			}
			else
			if(a[i-1].y-a[i].y==a[i].x-a[i-1].x)
				f[i][1]=f[i-1][1]+f[i-1][0];
			else
			{
				f[i][1]=f[i-1][0];
				if(Y==0)
					f[i][0]=f[i-1][0]+f[i-1][1];
				if(a[i-1].y==0)
					f[i][1]=f[i-1][1];
			}
			continue;
		}
		LL k=qpow(Y-1);
		if(a[i].y)
		{
			f[i][0]=f[i-1][1]*k%mod;
			if(a[i-1].y)
				f[i][0]=(f[i][0]+f[i-1][0]*k*2ll%mod)%mod;
		}
		else
			f[i][0]=0;
		f[i][1]=f[i-1][1]*k%mod;
		if(a[i-1].y)
			f[i][1]=(f[i][1]+f[i-1][0]*k*2ll%mod)%mod;
	}
	printf("%lld %lld\n",(f[m+1][0]+f[m+1][1])%mod,mx);
	
	return 0;
}
