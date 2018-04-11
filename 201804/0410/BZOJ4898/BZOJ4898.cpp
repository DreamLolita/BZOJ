#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=0x3f3f3f3f;
const int N=105;
const int M=1005;
const double eps=1e-8;
int n,m,k,tot,ans;
int head[N],len[N];
int mp[N][N],td[N][N],B[N][M],S[N][M];
double dis[N];
bool inq[N];
queue<int>q;

struct Tway
{
	int v,nex;
	double w;
};
Tway e[M*20];

void add(int u,int v,double w)
{
	e[++tot]=(Tway){v,head[u],w};
	head[u]=tot;
} 

bool check(double x)
{
	tot=0;
	memset(head,0,sizeof(head));memset(dis,0,sizeof(dis));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j && td[i][j]>=0)
				add(i,j,td[i][j]-x*mp[i][j]);
	for(int i=1;i<=n;++i)
		q.push(i),inq[i]=1,len[i]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[v]<dis[u]+e[i].w)
			{
				dis[v]=dis[u]+e[i].w;len[v]=len[u]+1;
				if(len[v]>n)
					return 1;
				if(!inq[v])
					q.push(v),inq[v]=1;
			}
		}
	}
	return 0;
}

int main()
{
	freopen("BZOJ4898.in","r",stdin);
	freopen("BZOJ4898.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	memset(mp,0x3f,sizeof(mp));memset(td,0x3c,sizeof(td));
	for(int i=1;i<=n;++i)
	{
		mp[i][i]=0;
		for(int j=1;j<=k;++j)
			scanf("%d%d",&B[i][j],&S[i][j]);
	}
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		mp[u][v]=min(mp[u][v],w);
	}
	for(int t=1;t<=n;++t)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				mp[i][j]=min(mp[i][j],mp[i][t]+mp[t][j]);
	
	double l=0,r=0,mid;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j && mp[i][j]<INF)
			{
				td[i][j]=0;
				for(int t=1;t<=k;++t)
					if(B[i][t]!=-1 && S[j][t]!=-1 && B[i][t]<S[j][t])
						td[i][j]=max(td[i][j],S[j][t]-B[i][t]);
				r=max(r,(double)td[i][j]);
			}
	while(l+eps<r)
	{
		mid=(l+r)/2.0;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%d\n",(int)(l+eps));
	
	return 0;
}
