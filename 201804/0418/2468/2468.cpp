#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=22;
const int M=(1<<18)+10;
int n,m,ans,tot;
int dis[N][N];
int f[N][M],g[N][M];

void init()
{
	memset(dis,127/3,sizeof(dis));
	memset(f,127/3,sizeof(f));memset(g,127/3,sizeof(g));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		dis[u][v]=dis[v][u]=min(dis[u][v],w);
	}
	for(int i=0;i<n;++i)	
		dis[i][i]=0;
}

void floyd()
{
	for(int k=0;k<n;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}

void solve()
{
	if(n==3)
	{
		printf("%d\n",(dis[0][1]+dis[1][2])*2);
		return;
	}
	
	for(int i=1;i<n-1;++i)
	{
		f[i][0]=g[i][0]=0;
		f[i][1<<(i-1)]=dis[0][i];g[i][1<<(i-1)]=dis[i][n-1];
	}
	
	int mx=1<<(n-2);
	for(int s=0;s<mx;++s)
	{
		for(int i=1;i<n-1;++i)
			if(s&(1<<(i-1)))
			{
				for(int j=1;j<n-1;++j)
				{
					f[j][s|(1<<(j-1))]=min(f[j][s|(1<<(j-1))],f[i][s]+dis[i][j]);
					g[j][s|(1<<(j-1))]=min(g[j][s|(1<<(j-1))],g[i][s]+dis[j][i]);
				}
			}
	}
	
	ans=INF;
	int sum=(n-2)/2;if(!sum) sum=n-2;
	for(int s=0;s<mx;++s)
	{
		tot=0;
		for(int i=1;i<n-1;++i)
			if(s&(1<<(i-1)))
				++tot;
		if(tot!=sum)
			continue;
		
		tot=INF;
		for(int i=1;i<n-1;++i)
			if(s&(1<<(i-1)))
			{
				int ns=s^(mx-1);
				if(!ns)
					ans=min(ans,f[i][s]+g[i][s]);
				for(int j=1;j<n-1;++j)
					tot=min(tot,f[i][s]+dis[i][j]+g[j][ns]);
			}
		for(int i=1;i<n-1;++i)
			if(s&(1<<(i-1)))
			{
				int ns=s^(mx-1);
				for(int j=1;j<n-1;++j)
					ans=min(ans,g[i][s]+dis[j][i]+f[j][ns]+tot);
			}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("2468.in","r",stdin);
	freopen("2468.out","w",stdout);
	
	init();
	floyd();
	solve();
	
	return 0;
}
