#include<bits/stdc++.h>
#define pii pair<int,int> 
#define mkp(A,B) make_pair(A,B)
using namespace std;

const int INF=1e9;
const int N=2010;
const int M=1e5+10;
int n,m,tot,S,E;
int A[N],B[N],C[N],D[N],tmp1[N],tmp2[N],val[N];
int head[M],dis[M],vis[M],T[55][N];
priority_queue<pii>q;

struct Tway
{
	int v,w,nex;
};
Tway e[M<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,w,head[u]};
	head[u]=tot;
}

int main()
{
	freopen("BZOJ5074.in","r",stdin);
	freopen("BZOJ5074.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&S,&E);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
		for(int j=0;j<C[i];++j)
			val[j]=(A[i]*j+B[i])%C[i]+D[i];
		tmp1[0]=val[0],tmp2[C[i]-1]=C[i]-1+val[C[i]-1];
		for(int j=1;j<C[i];++j)
			tmp1[j]=min(tmp1[j-1],j+val[j]);
		for(int j=C[i]-2;j>=0;--j)
			tmp2[j]=min(tmp2[j+1],j+val[j]);
		for(int j=0;j<C[i];++j)
			T[i][j]=min(C[i]-j+tmp1[j],tmp2[j]-j);
	}
	for(int i=1;i<=E;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	
	for(int i=0;i<M;++i)
		dis[i]=INF;
	dis[1]=S;q.push(mkp(-S,1));
	while(!q.empty())
	{
		int u=q.top().second;q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+T[w][dis[u]%C[w]])
			{
				dis[v]=dis[u]+T[w][dis[u]%C[w]];
				q.push(mkp(-dis[v],v));
			}
		}
	}
	for(int i=2;i<=n;++i)
	{
		if(dis[i]==INF)
			printf("-1\n");
		else
			printf("%d\n",dis[i]-S);
	}
	
	return 0;
}
