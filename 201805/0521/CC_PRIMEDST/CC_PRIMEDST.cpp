#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=262145;
const ldb pi=acos(-1);
int n,m,L,mx,tot,prinum,root,sum;
int dep[N],head[N],pri[N];
int siz[N],son[N],rev[N];
LL ans;
bool vis[N],isnotpri[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}


struct E
{
	ldb r,i;
	E(){} 
	E(ldb rx,ldb ix){r=rx;i=ix;}
	
	E operator + (const E&A)const{
		return E(r+A.r,i+A.i);
	}
	
	E operator - (const E&A)const{
		return E(r-A.r,i-A.i);
	}
	
	E operator * (const E&A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}a[N];

void fft(E *a,int n,int f)
{
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn=E(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w=E(1,0);
			for(int k=0;k<i;++k,w=w*wn)
			{
				E x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y;a[i+j+k]=x-y;
			}
		}
	}
	if(f==-1)
		for(int i=0;i<n;++i)
			a[i].r/=(ldb)n;
}

void getprime()
{
	isnotpri[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!isnotpri[i])
			pri[++prinum]=i;
		for(int j=1;j<=prinum && i*pri[j]<N;++j)
		{
			isnotpri[i*pri[j]]=1;
			if(!(i%pri[j]))
				break;
		}
	}
}

void getroot(int x,int f)
{
	siz[x]=1;son[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v] || v==f)
			continue;
		getroot(v,x);
		siz[x]+=siz[v];
		son[x]=max(son[x],siz[v]);
	}
	son[x]=max(son[x],sum-siz[x]);
	if(son[x]<son[root])
		root=x;
}

void getdis(int x,int f,int dp)
{
	dep[dp]++;mx=max(mx,dp);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v] || v==f)
			continue;
		getdis(v,x,dp+1);
	}
}

void calc(int f)
{
	for(m=1,L=0;m<=2*mx;m<<=1,++L);
	for(int i=0;i<m;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=0;i<=mx;++i)
		a[i]=E(dep[i],0);
	for(int i=mx+1;i<m;++i)
		a[i]=E(0,0);
	fft(a,m,1);
	for(int i=0;i<m;++i)
		a[i]=a[i]*a[i];
	fft(a,m,-1);
	for(int i=1;i<=prinum;++i)
	{
		if(pri[i]>=m)
			break;
		ans+=f*(LL)(a[pri[i]].r+0.5);
	}
}

void solve(int x)
{
	vis[x]=1;
	for(int i=0;i<=mx;++i) dep[i]=0;
	mx=0;getdis(x,0,0);
	calc(1);
/*	printf("add %d: ",x);
	for(int i=0;i<=mx;++i)
		printf("%d ",dep[i]);
	puts("");
	printf("ansnow:%lld\n",ans);*/
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v])
			continue;
		for(int i=0;i<=mx;++i) dep[i]=0;
		mx=0;getdis(v,x,1);
/*		printf("del %d: ",v);
		for(int i=0;i<=mx;++i)
			printf("%d ",dep[i]);
		puts("");*/
		calc(-1);
	}
//printf("ansnow:%lld\n",ans);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v])
			continue;
		sum=siz[v];root=0;
		getroot(v,x);solve(root);
	}
}

int main()
{
	freopen("CC_PRIMEDST.in","r",stdin);
	freopen("CC_PRIMEDST.out","w",stdout);
	
	getprime();
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	sum=n;son[0]=n+1;
	getroot(1,0);solve(root);
	printf("%0.10lf\n",(double)ans/n/(n-1));

	return 0;
}

