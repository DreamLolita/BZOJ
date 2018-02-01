#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull mod=7528443412579576937UL;
ull b,d,n,A,B,decl;

ull mul(ull x,ull y)
{
	ull ret=0;x%=mod;
	for(ull i=y;i;i>>=1,x=(x+x)%mod)
		if(i&1)
			ret=(ret+x)%mod;
	return ret;
}

struct Tmat
{
	ull a[2][2];
	Tmat(){
		memset(a,0,sizeof(a));
	}
	
	friend Tmat operator *(Tmat x,Tmat y)
	{
		Tmat ret;
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
				for(int k=0;k<2;++k)
					(ret.a[i][j]+=mul(x.a[i][k],y.a[k][j]))%=mod;
		return ret;
	}
	
	friend Tmat operator ^(Tmat x,ull y)
	{
		Tmat ret;
		ret.a[0][0]=ret.a[1][1]=1;
		for(ull i=y;i;i>>=1,x=x*x)
			if(i&1)
				ret=ret*x;
		return ret;
	}
};
Tmat num,ans;

int main()
{
//	freopen("BZOJ4002.in","r",stdin);
//	freopen("BZOJ4002.out","w",stdout);
	
	scanf("%llu%llu%llu",&b,&d,&n);
	A=b;B=(d-b*b)/4;
	num.a[0][1]=1;num.a[1][0]=B;num.a[1][1]=A;
	ans.a[0][0]=2;ans.a[1][0]=b;
	
	if(b*b!=d && n%2==0)
		decl=1;
	
	printf("%llu\n",(((num^n)*ans).a[0][0]-decl+mod)%mod);
	
	return 0;
} 
