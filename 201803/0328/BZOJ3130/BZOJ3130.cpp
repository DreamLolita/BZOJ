#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
const int INF=1e9;
const int N=105;
const int M=2005;
int n,m,tot,S,T,p;
int head[N],dep[N];
double l,r,ans;
queue<int>q;

struct Tway
{
	int u,v,nex;
	double w;
};
Tway e[M],mp[M];

void add(int u,int v,double w)
{
	e[++tot]=(Tway){u,v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v],0};head[v]=tot;
}

bool bfs()
{
	for(int i=1;i<=n;++i)
		dep[i]=-1;
	while(!q.empty())
		q.pop();
	dep[S]=0;q.push(S);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w>eps && dep[v]==-1)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return ~dep[T];
}

double dfs(int x,double f)
{
	if(x==T)
		return f;
	double used=0,w;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].w>eps && dep[v]==dep[x]+1)
		{
			w=dfs(v,min(e[i].w,f-used));
			e[i].w-=w;e[i^1].w+=w;used+=w;
			if(fabs(f-used)<eps)
				return f;
		}
	}
	if(fabs(used)<eps)
		dep[x]=-1;
//	printf("%d %lf %lf\n",x,f,used);
	return used;
}

double check(double now)
{
	tot=1;
	for(int i=1;i<=n;++i)
		head[i]=0;
	for(int i=1;i<=m;++i)
		add(mp[i].u,mp[i].v,min(now,mp[i].w));
//	for(int i=2;i<=tot;++i)
//		printf("%d %d %d %lf\n",e[i].u,e[i].v,e[i].nex,e[i].w);
	
	double sum=0,ret;
	while(bfs())
	{
//		printf("sum: %0.4lf\n",sum);
		while((ret=dfs(S,(double)INF))>eps)
			sum+=ret;
	}
	return sum;
}

int main()
{
	freopen("BZOJ3130.in","r",stdin);
	freopen("BZOJ3130.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&p);S=1;T=n;
	for(int i=1;i<=m;++i)
		scanf("%d%d%lf",&mp[i].u,&mp[i].v,&mp[i].w),r=max(r,mp[i].w);
	
	ans=check(r);
	while(r-l>eps)
	{
		double mid=(l+r)/2.0;
		if(fabs(ans-check(mid))<eps)
			r=mid;
		else
			l=mid;
	}
	printf("%0.0lf\n%0.4lf\n",ans,l*p);
	
	return 0;
}
