#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
const int mod=1e9+9;
int n,m,u,v,fu,fv,ans;
int fa[N];

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

int main()
{
	freopen("BZOJ2389.in","r",stdin);
	freopen("BZOJ2389.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		fu=findf(u);fv=findf(v);
		if(fu!=fv)
			fa[fu]=fv;
		else
			ans=(ans*2+1)%mod;
		printf("%d\n",ans);
	}
	
	return 0;
}
