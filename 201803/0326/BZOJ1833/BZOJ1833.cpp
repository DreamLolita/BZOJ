#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=15;
LL a,b;
LL ans1[N],ans2[N];
LL f[N],fc[N],num[N];

void init()
{
	fc[0]=1;
	for(int i=1;i<N;++i)
	{
		f[i]=10ll*f[i-1]+fc[i-1];
		fc[i]=10ll*fc[i-1];
	}
	scanf("%lld%lld",&a,&b);
}

void solve(LL x,LL *y)
{
	if(x==0)
		return;
	int m=0;LL res=x;
	while(x)
	{
		num[++m]=x%10;
		x/=10;
	}
	for(int i=1;i<m;++i)
	{
		y[0]+=f[i-1]*9ll;
		for(int j=1;j<=9;++j)
			y[j]+=f[i-1]*9ll+fc[i-1];
	}
	res-=num[m]*fc[m-1];
	for(int i=1;i<num[m];++i)
		y[i]+=fc[m-1];
	for(int i=0;i<=9;++i)
		y[i]+=f[m-1]*(num[m]-1);
	y[num[m]]+=res+1;
	for(int i=m-1;i;--i)
	{
		res-=num[i]*fc[i-1];
		for(int j=0;j<num[i];++j)
			y[j]+=fc[i-1];
		for(int j=0;j<=9;++j)
			y[j]+=f[i-1]*num[i];
		y[num[i]]+=res+1;
	}
}

int main()
{
	freopen("BZOJ1833.in","r",stdin);
	freopen("BZOJ1833.out","w",stdout);
	
	init();
	solve(a-1,ans1);solve(b,ans2);
	for(int i=0;i<=9;++i)
		printf("%lld ",ans2[i]-ans1[i]);
	
	return 0;
}
