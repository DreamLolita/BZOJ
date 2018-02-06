#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n;
int a[N],f[N],g[N];

int main()
{
//	freopen("BZOJ2386.in","r",stdin);
//	freopen("BZOJ2386.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		if(i>=a[i])
			f[i]=g[i-a[i]]+1;
		g[i]=max(f[i],g[i-1]);
	}
	printf("%d\n",f[n]);
	
	return 0;
}
