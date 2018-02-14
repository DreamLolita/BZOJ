#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1ll<<62;
const int N=1e6+10;
int n,s;
int a[N];
LL f[N];

int main()
{
	freopen("BZOJ3830.in","r",stdin);
	freopen("BZOJ3830.out","w",stdout);
	
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),f[i]=INF;
	sort(a+1,a+n+1);
	for(int i=2;i<=n;++i)
		a[i]=max(a[i],a[i-1]+1);
	int j=0;
	for(int i=1;i<=n;++i,--j)
		while(j<i && max(f[j]+i-j-1,(LL)a[i])+i-j-1+2*s<f[i])
			f[i]=max(f[j]+i-j-1,(LL)a[i])+i-j-1+2*s,++j;
	printf("%lld\n",f[n]);
	
	return 0;
}
