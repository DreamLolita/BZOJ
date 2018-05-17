#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const ldb pi=acos(-1);
const int N=262144;
const int M=32768;
int n,m,L,mod;
int rev[N],F[N],G[N];
LL ans[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct E
{
	ldb r,i;
	E(ldb rx=0.0,ldb ix=0.0):r(rx),i(ix){}
	
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
E a[N],b[N],da,db,dc,dd;
E e[N],f[N],g[N],h[N],wn[N];

E conj(E a) {return E(a.r,-a.i);}

void fft(E *a,int n,int f)
{
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E ww=wn[i];ww.i*=(ldb)f;
		for(int j=0;j<n;j+=(i<<1))
		{
			E w=E(1,0);
			for(int k=0;k<i;++k,w=w*ww)
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

void init()
{
	n=read();m=read();mod=read();
	for(int i=0;i<=n;++i)
		F[i]=read();
	for(int i=0;i<=m;++i)
		G[i]=read();
	
	m+=n;
	for(L=0,n=1;n<=m;n<<=1)
		++L;
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=1;i<n;i<<=1)
		wn[i]=E(cos(pi/i),sin(pi/i));
}

void MTT()
{
	for(int i=0;i<=m;++i)
		a[i]=E(F[i]/M,F[i]%M),b[i]=E(G[i]/M,G[i]%M);
	fft(a,n,1);fft(b,n,1);
	for(int i=0;i<n;++i)
	{
		int j=(n-i)&(n-1);
		da=(a[i]+conj(a[j]))*E(0.5,0);db=(a[i]-conj(a[j]))*E(0,-0.5);
		dc=(b[i]+conj(b[j]))*E(0.5,0);dd=(b[i]-conj(b[j]))*E(0,-0.5); 
		e[i]=da*dc;f[i]=da*dd;
		g[i]=db*dc;h[i]=db*dd;
	}
	for(int i=0;i<n;++i)
		a[i]=e[i]+f[i]*E(0,1),b[i]=g[i]+h[i]*E(0,1); 
	fft(a,n,-1);fft(b,n,-1);
	
	for(int i=0;i<=m;++i)
	{
		ans[i]+=(LL)(a[i].r+0.5)%mod*M%mod*M%mod;//add 0.5!
		ans[i]+=(LL)(a[i].i/n+0.5)%mod*M%mod;
		ans[i]+=(LL)(b[i].r+0.5)%mod*M%mod;
		ans[i]+=(LL)(b[i].i/n+0.5)%mod;
		ans[i]%=mod;
	}
	for(int i=0;i<=m;++i)
		printf("%lld ",ans[i]);
}

int main()
{
	freopen("LGP4245.in","r",stdin);
	freopen("LGP4245.out","w",stdout);
	
	init();
	MTT();

	return 0;
}

