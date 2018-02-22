#include<bits/stdc++.h>
using namespace std;

const int N=2005;
const int M=7;
const int mod=998244353;

int n,m,ks,ans;
int a[N][M],b[N][M],f[N][N][2],g[N][N][2];

bool equal(int *x,int *y)
{
	for(int i=1;i<=ks;++i)
		if(x[i]^y[i])
			return 0;
	return 1;
}

bool bigger(int *x,int *y)
{
	for(int i=1;i<=ks;++i)
		if(x[i]<=y[i])
			return 0;
	return 1;
}

bool smaller(int *x,int *y)
{
	for(int i=1;i<=ks;++i)
		if(x[i]>=y[i])
			return 0;
	return 1;
}

int main()
{
	freopen("BZOJ5124.in","r",stdin);
	freopen("BZOJ5124.out","w",stdout);
	
	scanf("%d%d",&ks,&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=ks;++j)
			scanf("%d",&a[i][j]);
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=ks;++j)
			scanf("%d",&b[i][j]);
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<2;++k)
			{
				if(equal(a[i],b[j]))
				{
					int t=g[i][j][k^1];
					if(!k)
						(t+=1)%=mod;
					(ans+=t)%=mod;
					(f[i+1][j][k]+=t)%=mod;
				}
				if(f[i][j][k])
				{
					(f[i+1][j][k]+=f[i][j][k])%=mod;
					if(!k)
					{
						if(bigger(a[i],b[j]))
							(g[i][j+1][k]+=f[i][j][k])%=mod;
					}
					else
					{
						if(smaller(a[i],b[j]))
							(g[i][j+1][k]+=f[i][j][k])%=mod;
					}
				}
				if(g[i][j][k])
					(g[i][j+1][k]+=g[i][j][k])%=mod;
			}
	printf("%d\n",ans);
	
	return 0;
}
