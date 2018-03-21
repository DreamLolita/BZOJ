#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double eps=1e-8;
const int INF=1e9;
const int N=1005;
int n,S,T,D,tot=-1;
int du[N],head[N];
int vis[N][N];
double ans,d[N][N],dis[N][N];

struct Tway
{
	int x,y;
};
Tway e[N<<3],E[N<<3];

struct Tpoint
{
	LL x,y;
	Tpoint(){}
	Tpoint(LL xx,LL yy){
		x=xx;y=yy;
	}
	Tpoint operator -(const Tpoint &A)const{
		return Tpoint(x-A.x,y-A.y);
	} 
	LL operator *(const Tpoint &A)const{
		return x*A.y-y*A.x;
	} 
	LL operator ^(const Tpoint &A)const{
		return x*A.x+y*A.y;
	}
};
Tpoint a[N];

LL sqr(LL x)
{
	return x*x;
}

double ds(Tpoint A,Tpoint B)
{
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

bool dfs(int x,int y,double m)
{
	if(d[x][y]>m || vis[x][y]==D)
		return 0;
	vis[x][y]=D;
	if(du[x]==1 && ((du[E[y].x]==1 && dis[x][E[y].x]<m) || (du[E[y].y]==1 && dis[x][E[y].y]<m)))
		return 1;
	for(int i=head[x];~i;i=e[i].y)
	{
		if(dfs(E[y].x,i>>1,m))
			return 1;
		if(dfs(E[y].y,i>>1,m))
			return 1;
		if(dfs(e[i].x,y,m))
			return 1;
	}
	return 0;
}

double get_dis(Tpoint A,Tpoint x,Tpoint y)
{
	if(((A-x)^(y-x))<0)
		return ds(A,x);
	if(((A-y)^(x-y))<0)
		return ds(A,y);
	LL t=(A-x)*(A-y);
	if(t<0)
		t=-t;
	double len=ds(x,y);
	return (double)t/len;
}

int main()
{
	freopen("UOJ371.in","r",stdin);
	freopen("UOJ371.out","w",stdout);
	
	memset(head,-1,sizeof(head));
	scanf("%d%d%d",&n,&S,&T);
	for(int i=1;i<=n;++i)
		scanf("%lld%lld",&a[i].x,&a[i].y);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		for(int j=1;j<=n;++j)
			d[j][i-1]=get_dis(a[j],a[u],a[v]);
		++du[u];++du[v];
		E[i-1].x=u;E[i-1].y=v;
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=ds(a[i],a[j]);
	double l=ds(a[S],a[T]),r=1e8;
	while(fabs(l-r)>eps)
	{
		
		double mid=(l+r)*0.5;++D;
//printf("%0.6lf %0.6lf %0.6lf\n",l,r,mid);
		bool flag=false;
		for(int i=head[T];~i;i=e[i].y)
			if(dfs(S,i>>1,mid))
			{
				flag=true;
				break;
			}
		if(flag)
			ans=mid,r=mid;
		else
			l=mid;
	}
	printf("%0.10lf\n",ans);
	
	return 0;
}
