#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
const LL N=3005;
LL t,l,r,n,m,ans;
LL a[N],b[N];
bool vis[N];

LL gcd(LL x,LL y)
{
	if(!(x%y))
		return y;
	return gcd(y,x%y);
}

void init(LL x,LL y)
{
	if(x>t || y>r)
		return;
	if(x>0)
		a[++m]=y;
	init(x+1,y*10ll+2);
	init(x+1,y*10ll+9);	
}

void dfs(LL x,LL y,LL z)
{
//	printf("%lld %lld %lld\n",x,y,z);
	if(x>n)
	{
		if(y&1)
			ans+=r/z-(l-1)/z;
		else
		if(y)
			ans-=r/z-(l-1)/z;
		return;
	}
	dfs(x+1,y,z);
	LL nex=(LL)a[x]*z/gcd(a[x],z);
	if(nex<=r)
		dfs(x+1,y+1,nex);
}

int main()
{
	freopen("BZOJ2393.in","r",stdin);
	freopen("BZOJ2393.out","w",stdout);
	
	scanf("%llu%llu",&l,&r);
	t=(LL)(log(r)/log(10))+1;
	init(0,0);
	sort(a+1,a+m+1);
	
	for(LL i=1;i<=m;++i)
	{
		if(!vis[i])
		{
			b[++n]=a[i];
			for(LL j=i+1;j<=m;++j)
				if(!(a[j]%a[i]))
					vis[j]=true;
		}
	}

	for(LL i=1;i<=n;++i)
		a[n-i+1]=b[i];
	dfs(1,0,1);
	printf("%llu\n",ans);
	
	return 0;
}
