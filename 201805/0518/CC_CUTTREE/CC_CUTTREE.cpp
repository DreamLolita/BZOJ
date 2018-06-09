#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=4e5+10;
const int mod=1e9+7;
const int M=32768;
const ldb pi=acos(-1);
int n,m,L,tot,root,mx,sum;
int son[N],siz[N],rev[N],vis[N];
int head[N],cnt[N],dis[N];
LL inv[N],fac[N],ans[N],dep[N];

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
Tway es[N<<1];

void add(int u,int v)
{
	es[++tot]=(Tway){v,head[u]};head[u]=tot;
	es[++tot]=(Tway){u,head[v]};head[v]=tot;
}

struct E
{
	ldb r,i;
	E(){};
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
};
E da,db,dc,dd;
E a[N],b[N],e[N],f[N],g[N],h[N];

E conj(E a) {return E(a.r,-a.i);}

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

void getroot(int x,int f)
{
	siz[x]=1;son[x]=0;
	for(int i=head[x];i;i=es[i].nex)
	{
		int v=es[i].v;
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

void getdep(int x,int f,int dp)
{
	cnt[dp]++;siz[x]=1;mx=max(mx,dp);
	for(int i=head[x];i;i=es[i].nex)
	{
		int v=es[i].v;
		if(vis[v] || v==f)
			continue;
		getdep(v,x,dp+1);
		siz[x]+=siz[v];
	}
}

void calc(int mx,int f)
{
	L=0;m=1;
	for(;m<=mx*2;m<<=1,++L);
	for(int i=0;i<m;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
		
	for(int i=0;i<=mx;++i)
		a[i]=E(cnt[i],0);
	for(int i=mx+1;i<m;++i)
		a[i]=E(0,0);
	fft(a,m,1);
	for(int i=0;i<m;++i)
		a[i]=a[i]*a[i];
	fft(a,m,-1);
	for(int i=1;i<=min(n-1,mx*2);++i)
		(dis[i]+=(LL)(a[i].r+0.5)%mod*f)%=mod;
	
}

void solve(int x)
{
	vis[x]=1;mx=0;getdep(x,0,0);calc(mx,1);
	for(int i=0;i<=mx;++i)
		cnt[i]=0;
	for(int i=head[x];i;i=es[i].nex)
	{
		int v=es[i].v;
		if(vis[v])
			continue;
		mx=0;getdep(v,x,1);calc(mx,-1);
		for(int j=0;j<=mx;++j)
			cnt[j]=0;
	}
	for(int i=head[x];i;i=es[i].nex)
	{
		int v=es[i].v;
		if(vis[v])
			continue;
		sum=siz[v];root=0;getroot(v,x);
		solve(root);
	}
}

void prepare()
{
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod,inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*inv[i-1]*inv[i]%mod;
	dis[0]=n;
	for(int i=1;i<n;++i)
		dis[i]=(dis[i]+mod)%mod;
	
	L=0;m=1;
	for(;m<=n*2;m<<=1,++L);
	for(int i=0;i<m;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
}

void calc_ans()
{
	prepare();
	for(int i=0;i<=m;++i)
		a[i]=b[i]=E(0,0);
	for(int i=0;i<n;++i)
	{
		a[i]=E(1ll*dis[i]*fac[n-i-1]%mod/M,1ll*dis[i]*fac[n-i-1]%mod%M);	
		b[i]=E(inv[i]/M,inv[i]%M);
	}
	fft(a,m,1);fft(b,m,1);
	
	for(int i=0;i<m;++i)
	{
		int j=(m-i)&(m-1);
		da=(a[i]+conj(a[j]))*E(0.5,0);db=(a[i]-conj(a[j]))*E(0,-0.5);
		dc=(b[i]+conj(b[j]))*E(0.5,0);dd=(b[i]-conj(b[j]))*E(0,-0.5); 
		e[i]=da*dc;f[i]=da*dd;
		g[i]=db*dc;h[i]=db*dd;
	}
	for(int i=0;i<m;++i)
		a[i]=e[i]+f[i]*E(0,1),b[i]=g[i]+h[i]*E(0,1); 
	fft(a,m,-1);fft(b,m,-1);
	
	for(int i=0;i<n;++i)
	{
		ans[i]+=(LL)(a[i].r+0.5)%mod*M%mod*M%mod;//add 0.5!
		ans[i]+=(LL)(a[i].i/m+0.5)%mod*M%mod;
		ans[i]+=(LL)(b[i].r+0.5)%mod*M%mod;
		ans[i]+=(LL)(b[i].i/m+0.5)%mod;
		ans[i]%=mod;
	}
	
	printf("%d ",1ll*n*n%mod);
	for(int i=1;i<n;++i)
		printf("%d ",1ll*ans[n-i-1]*fac[n-i-1]%mod*inv[n-1]%mod);
}

int main()
{
	freopen("CC_CUTTREE.in","r",stdin);
	freopen("CC_CUTTREE.out","w",stdout);

	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	son[0]=n;sum=n;root=0;getroot(1,0);
	solve(root);
	calc_ans();

	return 0;
}
