#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=2e4+5;
const int M=5e4+5;
const int K=12;

int n,m,ans,tot;
int a[N],dep[N],p[N],vis[N],head[N],q[K];
int f[K][N+M];

struct Tway
{
	int v,nex;
};
Tway e[M];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

int bit(int x,int y)
{
	return x/p[y]%3;
}

void dfs(int x,int tp)
{
	vis[x]=1;dep[x]=tp;
	if(!tp)
		f[0][0]=a[x],f[0][1]=0,f[0][2]=INF;
	else
	{
		int cnt=0;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(vis[v] && dep[v]<tp)
				q[cnt++]=dep[v];
		}
		for(int i=p[tp+1]-1;~i;--i)
			f[tp][i]=INF;
		for(int i=p[tp]-1;~i;--i)
		{
			int u=1,v=i;
			for(int j=0;j<cnt;++j)
				if(bit(i,q[j])==0)
					u=2;
				else
				if(bit(i,q[j])==1)
					v+=p[q[j]];
			f[tp][i+u*p[tp]]=min(f[tp][i+u*p[tp]],f[tp-1][i]);
			f[tp][v]=min(f[tp][v],f[tp-1][i]+a[x]);
		}
	}
	
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			dfs(v,tp+1);
			for(int j=0;j<p[tp+1];++j)
				f[tp][j]=min(f[tp+1][j],f[tp+1][j+2*p[tp+1]]);
		}
	}
}

int main()
{
	freopen("BZOJ3836.in","r",stdin);
	freopen("BZOJ3836.out","w",stdout);
	
	p[0]=1;
	for(int i=1;i<K;++i)
		p[i]=p[i-1]*3;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			dfs(i,0),ans+=min(f[0][0],f[0][2]);
	printf("%d\n",ans);
	
	return 0;
}
