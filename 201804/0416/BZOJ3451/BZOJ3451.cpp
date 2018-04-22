#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double pi=acos(-1);
const int N=6e4+10;
int n,m,tot,ind,sum,root;
int c[N],rev[N],tim[N];
int head[N],siz[N],mx[N];
LL dis[N];
bool vis[N];
double totans;

struct Tway
{
	int v,nex;
};
Tway e[N];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

struct E
{
	double r,i;
	
	E(){}
	E(double rx,double ix){
		r=rx;i=ix;
	}
	
	E operator + (E const &A)const{
		return E(r+A.r,i+A.i);
	}
	
	E operator - (E const &A)const{
		return E(r-A.r,i-A.i);
	}
	
	E operator * (E const &A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}a[N];

void fft(E *a,int f)
{
	for(int i=0;i<m;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<m;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<m;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;++k,w=w*wn)
			{
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)
		for(int i=0;i<m;++i)
			a[i].r/=m;
}

void calc(int f)
{
	int t=m<<1,len=0;
	for(m=1;m<=t;m<<=1)
		++len;
	for(int i=0;i<m;++i)
		rev[i]=rev[i>>1]>>1|((i&1)<<(len-1));
	for(int i=0;i<m;++i)
	{
		if(tim[i]!=ind)
			c[i]=0;
		a[i].r=c[i];a[i].i=0;
	}
	fft(a,1);
	for(int i=0;i<m;++i)
		a[i]=a[i]*a[i];
	fft(a,-1);
	for(int i=0;i<min(n,m);++i)
		dis[i]+=(LL)(a[i].r+0.5)*f;
}

void getroot(int x,int f)
{
	siz[x]=1;mx[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=f)
		{
			getroot(v,x);
			siz[x]+=siz[v];
			mx[x]=max(mx[x],siz[v]);
		}
	}
	mx[x]=max(mx[x],sum-siz[x]);
	if(mx[x]<mx[root])
		root=x;
}

void dfs(int x,int f,int dep)
{
	if(tim[dep]!=ind)
		c[dep]=0;
	++c[dep];tim[dep]=ind;
	m=max(m,dep);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=f)
			dfs(v,x,dep+1);
	}
}

void solve(int x)
{
	vis[x]=1;++ind;m=0;
	dfs(x,0,0);calc(1);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v])
			continue;
		m=0;++ind;
		dfs(v,0,1);calc(-1);
		sum=siz[v];root=0;
		getroot(v,0);
		solve(root);
	}
}

int main()
{
	freopen("BZOJ3451.in","r",stdin);
	freopen("BZOJ3451.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);++u;++v;
		add(u,v);
	}
	mx[0]=n+1;sum=n;
	getroot(1,0);
	solve(root);
	for(int i=0;i<=n-1;++i)
		totans+=1.0*dis[i]/(i+1);
	printf("%0.4lf\n",totans);
	
	return 0;
}
