#include<bits/stdc++.h>
using namespace std;

const int INF=0x3fffff;
const int N=2e3+5;
const int M=1e5+5;
int n,m,k,tot,S;
int sum[N],ans[N],head[N];
int tmp[10],f[N][N];
bool vis[N];
queue<int>q;

struct Tpoint
{
	int col,w;
};
Tpoint p[N];

struct Tway
{
	int v,w,nex;
};
Tway e[M];

void add(int u,int v,int w)
{
	++tot;
	e[tot].v=v;e[tot].w=w;
	e[tot].nex=head[u];head[u]=tot;
}

void init()
{	
	scanf("%d%d%d",&n,&m,&k);
	S=1<<k;
	
	for(int i=1;i<=n;++i)
        for(int s=0;s<S;++s) 
			f[i][s]=INF;
    for(int s=0;s<S;++s) 
		ans[s]=INF;

	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	
	for(int i=1;i<=k;++i)
		scanf("%d%d",&p[i].col,&p[i].w),sum[p[i].col]++;
	for(int i=1;i<=k;++i)
		f[p[i].w][1<<(i-1)]=0;
}

void spfa(int s)
{
	while(!q.empty())
		q.pop();
	for(int i=1;i<=n;++i)
		vis[i]=1,q.push(i);
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(f[u][s]+e[i].w<f[v][s])
			{
				f[v][s]=f[u][s]+e[i].w;
				if(!vis[v])
				{
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}

void Steiner()
{
	for(int s=0;s<S;++s)
	{
		for(int i=1;i<=n;++i)
			for(int ns=s;ns;ns=(ns-1)&s)
				f[i][s]=min(f[i][s],f[i][ns]+f[i][s^ns]);	

		spfa(s);
	}
}

bool check(int s)
{
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=k;++i)
		if(s&(1<<(i-1)))
			tmp[p[i].col]++;
	for(int i=1;i<=10;++i)
		if(tmp[i] && tmp[i]!=sum[i])
			return 0;
	return 1;
}

void dp_ans()
{
	for(int s=0;s<S;++s)
		for(int i=1;i<=n;++i)
			ans[s]=min(ans[s],f[i][s]);
	for(int s=0;s<S;++s)
		if(check(s))
			for(int ns=s;ns;ns=(ns-1)&s)
				if(check(ns))
					ans[s]=min(ans[s],ans[ns]+ans[s^ns]);
	printf("%d\n",ans[(1<<k)-1]);
}

int main()
{
//	freopen("BZOJ4006.in","r",stdin);
//	freopen("BZOJ4006.out","w",stdout);
	
	init();
	Steiner();
	dp_ans();
	
	return 0;
}
