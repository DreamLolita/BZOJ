#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;
int n,r,p;
LL f[N];

LL dfs(int x)
{
	if(f[x])
		return f[x];
	LL mn=1ll*p*x;
	for(int i=2;i<x;i=(x-1)/((x-1)/i)+1)
		mn=min(mn,1ll*p*i+dfs((x-1)/i+1));
	return x>=2?f[x]=mn+r-p:0;
}

int main()
{
	freopen("BZOJ4428.in","r",stdin);
	freopen("BZOJ4428.out","w",stdout);
	
	scanf("%d%d%d",&n,&r,&p);
	printf("%lld\n",dfs(n));
	
	return 0;
}
