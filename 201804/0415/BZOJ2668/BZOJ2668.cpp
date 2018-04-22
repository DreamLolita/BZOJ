#include<bits/stdc++.h>
#define id(x,y) ((x-1)*m+y)
using namespace std;

const int INF=707406378;
const int N=25;
const int M=2e6+10;
int S,T,b1,b2;
int n,m,tot,sum,flow,ans;
int head[M],dis[M],from[M];
int num[N][N],a[N][N],b[N][N],c[N][N];
char s1[N][N],s2[N][N],s3[N][N];
bool inq[M];
queue<int>q;

struct Tway
{
	int u,v,nex,w,c;
};
Tway e[M];

void add(int u,int v,int w,int c)
{
	e[++tot]=(Tway){u,v,head[u],w,c};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v],0,-c};head[v]=tot;
}

void init()
{
	scanf("%d%d",&n,&m);sum=n*m;S=0;T=sum*3+1;tot=1;
	for(int i=1;i<=n;++i)
		scanf("%s",s1[i]+1);
	for(int i=1;i<=n;++i)
		scanf("%s",s2[i]+1);
	for(int i=1;i<=n;++i)
		scanf("%s",s3[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			a[i][j]=s1[i][j]-'0';
			if(a[i][j])
				++b1;
			b[i][j]=s2[i][j]-'0';
			if(b[i][j])
				++b2;
			c[i][j]=s3[i][j]-'0';
			if(a[i][j] && b[i][j])
				a[i][j]=b[i][j]=0,--b1,--b2;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			int now=id(i,j);num[i][j]=now;
			if(a[i][j])
			{
				add(S,now,1,0);add(sum+now,now,c[i][j]/2,0);
				add(now,2*sum+now,(c[i][j]+1)/2,0);
			}
			else
			if(b[i][j])
			{
				add(now,T,1,0);add(sum+now,now,(c[i][j]+1)/2,0);
				add(now,2*sum+now,c[i][j]/2,0);
			}
			else
			{
				add(sum+now,now,c[i][j]/2,0);
				add(now,2*sum+now,c[i][j]/2,0);
			}
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			if(i>1)	add(2*sum+num[i][j],sum+num[i-1][j],INF,1);
			if(j>1)	add(2*sum+num[i][j],sum+num[i][j-1],INF,1);
			if(i<n)	add(2*sum+num[i][j],sum+num[i+1][j],INF,1);
			if(j<m)	add(2*sum+num[i][j],sum+num[i][j+1],INF,1);
			if(i>1 && j>1)	add(2*sum+num[i][j],sum+num[i-1][j-1],INF,1);
			if(i<n && j<m)	add(2*sum+num[i][j],sum+num[i+1][j+1],INF,1);
			if(i>1 && j<m)	add(2*sum+num[i][j],sum+num[i-1][j+1],INF,1);
			if(i<n && j>1)	add(2*sum+num[i][j],sum+num[i+1][j-1],INF,1);
		}		
}

bool spfa()
{
	memset(dis,127/3,sizeof(dis));
	q.push(S);inq[S]=1;dis[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dis[u]+e[i].c<dis[v])
			{
				dis[v]=dis[u]+e[i].c;from[v]=i;
				if(!inq[v])
				{
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
	return dis[T]!=INF;
}

void solve()
{
	if(b1==b2)
	{
		while(spfa())
		{
			int f=INF;
			for(int i=from[T];i;i=from[e[i].u])
				f=min(f,e[i].w);
			for(int i=from[T];i;i=from[e[i].u])
				e[i].w-=f,e[i^1].w+=f;
			flow+=f;ans+=f*dis[T];
		}
		if(flow!=b1)
			ans=-1;
	}
	else
		ans=-1;
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ2668.in","r",stdin);
	freopen("BZOJ2668.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
