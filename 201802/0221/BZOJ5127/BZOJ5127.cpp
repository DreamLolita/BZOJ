#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m;
int a[N],f[N];

int main()
{
	freopen("BZOJ5127.in","r",stdin);
	freopen("BZOJ5127.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	f[1]=1;
	for(int i=2;i<=n;++i)
		f[i]=abs(a[i]-a[i-1])<=1?f[i-1]:i;
	for(int i=1;i<=m;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		puts(f[r]<=l?"YES":"NO");
	}	
	
	return 0;
}
