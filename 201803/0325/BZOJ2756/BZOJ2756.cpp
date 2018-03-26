#include<bits/stdc++.h>
#define p(x,y) ((x-1)*m+y)
#define inmp(x,y) (x>=1 && x<=n && y>=1 && y<=m)
using namespace std;

typedef long long LL;
const LL INF=(LL)1ll<<50;
const int N=45;
const int M=N*N;
int n,m,S,T,tot,cas,mx;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int dep[M],head[M],cur[M];
int a[N][N],col[N][N];
LL s0,s1,c0,c1,sum;
queue<int>q;

struct Tway
{
	int v,nex;
	LL w;
};
Tway e[M*10];

void add(int u,int v,LL w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],0};head[v]=tot;
}

bool bfs()
{
	while(!q.empty())
		q.pop();
	memset(dep,-1,sizeof(dep));
	q.push(S);dep[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dep[v]==-1)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return ~dep[T];
}

LL dfs(int x,LL f)
{
	if(x==T)
		return f;
	LL w,used=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dep[v]!=dep[x]+1)
			continue;
		w=dfs(v,min(f-used,e[i].w));
		e[i].w-=w;e[i^1].w+=w;
//		if(e[i].w)
//			cur[x]=i;
		used+=w;
		if(used==f)
			return f;
	}
	if(!used)
		dep[x]=-1;
	return used;
}

LL dinic()
{
	LL ret=0;
	while(bfs())
	{
//		for(int i=S;i<=T;++i)
//			cur[i]=head[i];
		ret+=dfs(S,INF);
	}
	return ret;
}

bool check(LL x)
{
	memset(head,0,sizeof(head));tot=1;
	S=0;T=n*m+1;sum=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(col[i][j])
			{
				add(S,p(i,j),x-a[i][j]);sum+=x-a[i][j];
				for(int k=0;k<4;++k)
				{
					int nx=i+dx[k],ny=j+dy[k];
					if(inmp(nx,ny))
						add(p(i,j),p(nx,ny),INF);
				}
			}
			else
				add(p(i,j),T,x-a[i][j]);
	if(dinic()==sum)
		return true;
	return false;
}

int main()
{
	freopen("BZOJ2756.in","r",stdin);
	freopen("BZOJ2756.out","w",stdout);
	
	scanf("%d",&cas);
	while(cas--)
	{
		c0=c1=s0=s1=mx=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				scanf("%d",&a[i][j]);
				mx=max(mx,a[i][j]);
				col[i][j]=(i+j)&1;
				if(col[i][j])
					s1+=a[i][j],++c1;
				else
					s0+=a[i][j],++c0;
			}
		if(c0!=c1)
		{
			LL x=(s0-s1)/(c0-c1);
			if(x>=mx)
				if(check(x))
				{
					printf("%lld\n",(LL)x*c1-s1);
					continue;
				}
			puts("-1");
		}
		else
		{
			if(s0!=s1)
				puts("-1");
			else
			{
				LL l=mx,r=INF;
				while(l<=r)
				{
					
					LL mid=(LL)(l+r)>>1;
					if(check(mid))
						r=mid-1;
					else
						l=mid+1;
				}
				printf("%lld\n",(LL)l*c1-s1);
			}
		}
	}
	
	return 0;
}
