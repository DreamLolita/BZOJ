#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=1e9+7;
const int N=3e6+10;
int n,m,x,y,ans;
int fac[N],inv[N];

void init()
{
	fac[0]=fac[1]=1;
	for(int i=2;i<N;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	inv[0]=inv[1]=1;
	for(int i=2;i<N;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;++i)
		inv[i]=1ll*inv[i]*inv[i-1]%mod;
}

int C(int p,int q)
{
	if(p<q)	return 0;
	return 1ll*fac[p]*inv[q]%mod*inv[p-q]%mod;
}

int calc(int p,int q)
{
	if(p<0 || q<0)	return 0;
	return C(p+q,p);
}

void flip1(int &p,int &q)//flip by y=x+1
{
	swap(p,q);
	--p;++q;
}

void flip2(int &p,int &q)//flip by y=x-(m+2)
{
	swap(p,q);
	p+=m+2;q-=m+2;
}

void solve()
{
	scanf("%d%d",&n,&m);
	ans=calc(n+m+1,n);
	
	x=n+m+1;y=n;
	while(x>=0 && y>=0)
	{
		flip1(x,y);
		ans-=calc(x,y);
		flip2(x,y);
		ans+=calc(x,y);
		ans%=mod;
	}
	
	x=n+m+1;y=n;
	while(x>=0 && y>=0)
	{
		flip2(x,y);
		ans-=calc(x,y);
		flip1(x,y);
		ans+=calc(x,y);
		ans%=mod;
	}
	
	ans=(ans+mod)%mod;
	printf("%d\n",ans);
}

int main()
{
//	freopen("BZOJ4005.in","r",stdin);
//	freopen("BZOJ4005.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
