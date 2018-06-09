#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=264115;
const int mod=1e9+7;
const int M=32768;
const ldb pi=acos(-1);
int n,L,m,rev[20][N];
LL a[N],b[N],c[N],tp[N],tp2[N];
bool flag[50];

char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

LL read()
{
	LL ret=0,f=1;char c=nc();
	while(!isdigit(c)){if(c=='-')f=0;c=nc();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=nc();}
	return f?ret:-ret;
}

void write(LL x)
{
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar((x%10)^48);
}

struct E
{
	ldb r,i;
	E(){}
	E(ldb rx,ldb ix){r=rx;i=ix;}
	
	E operator + (const E&t)const{
		return E(r+t.r,i+t.i);
	}
	
	E operator - (const E&t)const{
		return E(r-t.r,i-t.i);
	}
	
	E operator * (const E&t)const{
		return E(r*t.r-i*t.i,r*t.i+i*t.r);
	}
};
E da,db,dc,dd;
E A[N],B[N],C[N],D[N],G[N],H[N];

E conj(E t){return E(t.r,-t.i);}

int qpow(int x,int y)
{
	int ret=1;
	for(;y;y>>=1,x=1ll*x*x%mod)
		if(y&1)
			ret=1ll*ret*x%mod;
	return ret;	
}

void fft(E *a,int n,int f,int dep)
{
	for(int i=0;i<n;++i)
		if(i<rev[dep][i])
			swap(a[i],a[rev[dep][i]]);
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
			a[i].r/=(ldb)n,a[i].i/=(ldb)n;
}

void MTT(LL *a,LL *b,int deg,int dep,LL *ret)
{
	for(int i=0;i<m;++i)
		A[i]=B[i]=C[i]=D[i]=G[i]=H[i]=E(0,0),ret[i]=0;
	for(int i=0;i<deg;++i)
	{
		a[i]%=mod;b[i]%=mod;
		A[i]=E(a[i]/M,a[i]%M);B[i]=E(b[i]/M,b[i]%M);
	}
	fft(A,m,1,dep);fft(B,m,1,dep);
	for(int i=0;i<m;++i)
	{
		int j=(m-i)&(m-1);
		da=(A[i]+conj(A[j]))*E(0.5,0);db=(A[i]-conj(A[j]))*E(0,-0.5);
		dc=(B[i]+conj(B[j]))*E(0.5,0);dd=(B[i]-conj(B[j]))*E(0,-0.5); 
		C[i]=da*dc;D[i]=da*dd;
		G[i]=db*dc;H[i]=db*dd;
	}
	for(int i=0;i<m;++i)
		A[i]=C[i]+D[i]*E(0,1),B[i]=G[i]+H[i]*E(0,1);
	fft(A,m,-1,dep);fft(B,m,-1,dep);
	
	for(int i=0;i<deg;++i)
	{
		ret[i]+=(LL)(A[i].r+0.5)%mod*M%mod*M%mod;
		ret[i]+=(LL)(A[i].i+0.5)%mod*M%mod;
		ret[i]+=(LL)(B[i].r+0.5)%mod*M%mod;
		ret[i]+=(LL)(B[i].i+0.5)%mod;
		ret[i]%=mod;
	}
}

void poly_inv(LL *a,LL *b,int deg,int dep)
{
	if(deg==1)
	{
		b[0]=qpow(a[0],mod-2);
		return;
	}
	poly_inv(a,b,(deg+1)>>1,dep+1);
	for(L=0,m=1;m<2*deg;++L,m<<=1);
	
	if(!flag[dep])
	{
		for(int i=1;i<m;++i)
			rev[dep][i]=(rev[dep][i>>1]>>1)|((i&1)<<(L-1));
		flag[dep]=1;
	}
	MTT(a,b,deg,dep,tp);MTT(tp,b,deg,dep,tp2);
	for(LL i=0;i<deg;++i)
		b[i]=(b[i]+b[i]+mod-tp2[i])%mod;
}

int main()
{
	freopen("LGP4239.in","r",stdin);
	freopen("LGP4239.out","w",stdout);

	n=read();
	for(int i=0;i<n;++i)
		a[i]=read();
	poly_inv(a,b,n,0);
	for(int i=0;i<n;++i)
		write(b[i]),putchar(' ');

	return 0;
}

