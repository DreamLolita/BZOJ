#include<bits/stdc++.h>
using namespace std;

const int INF=707406378;
const int N=1005;
int n,m,S,T,mx;
int A[N][N],ans[N][N],tmp[N][N];

void fac(int x[N][N],int (*y)[N])
{
	for(int i=1;i<=mx;++i)
		for(int j=1;j<=mx;++j)
			tmp[i][j]=INF;
	for(int k=1;k<=mx;++k)
		for(int i=1;i<=mx;++i)
			if(x[i][k]==INF)
				continue;
			else
			for(int j=1;j<=mx;++j)
				if(y[k][j]==INF)
					continue;
				else
					tmp[i][j]=min(tmp[i][j],x[i][k]+y[k][j]);
	for(int i=1;i<=mx;++i)
		for(int j=1;j<=mx;++j)
			y[i][j]=tmp[i][j];
}


int main()
{
	freopen("BZOJ1706.in","r",stdin);
	freopen("BZOJ1706.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&S,&T);

	memset(A,127/3,sizeof(A));
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&w,&u,&v);
		A[u][v]=A[v][u]=w;
		mx=max(mx,u);mx=max(mx,v);
	}

	memset(ans,127/3,sizeof(ans));
	for(int i=1;i<=mx;++i)
		ans[i][i]=0;
	for(;n;n>>=1,fac(A,A))
		if(n&1)
			fac(A,ans);
			
	printf("%d\n",ans[S][T]);
	
	return 0;
}
