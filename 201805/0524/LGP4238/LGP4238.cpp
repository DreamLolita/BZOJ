#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=466666;
const int mod=998244353;
const int G=3;
int n,L,m;
int a[N],b[N],c[N],rev[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int qpow(int x,int y)
{
	int ret=1;
	for(;y;y>>=1,x=1ll*x*x%mod)
		if(y&1)
			ret=1ll*ret*x%mod;
	return ret;	
}

void ntt(int *a,int n,int f)
{
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int wn=qpow(G,(mod-1)/(i<<1));
		if(f==-1)
			wn=qpow(wn,mod-2);
		for(int j=0;j<n;j+=(i<<1))
		{
			int w=1;
			for(int k=0;k<i;++k,w=1ll*w*wn%mod)
			{
				int x=a[j+k],y=1ll*w*a[i+j+k]%mod;
				a[j+k]=(x+y)%mod;a[i+j+k]=(((x-y)%mod)+mod)%mod;
				
			}
		}
	}
	if(f==-1)
		for(int i=0,inv=qpow(n,mod-2);i<n;++i)
			a[i]=1ll*a[i]*inv%mod;
}

void poly_inv(int *a,int *b,int deg)
{
	if(deg==1)
	{
		b[0]=qpow(a[0],mod-2);
		return;
	}
	poly_inv(a,b,(deg+1)>>1);
	for(L=0,m=1;m<2*deg;++L,m<<=1);
	for(int i=1;i<m;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=0;i<deg;++i)
		c[i]=a[i];
	for(int i=deg;i<m;++i)
		c[i]=0;
	ntt(c,m,1);ntt(b,m,1);
	for(int i=0;i<m;++i)
		b[i]=1ll*((2ll-1ll*c[i]*b[i]%mod)+mod)%mod*b[i]%mod;
	ntt(b,m,-1);
	for(int i=deg;i<m;++i)
		b[i]=0;
}

int main()
{
	freopen("LGP4238.in","r",stdin);
	freopen("LGP4238.out","w",stdout);

	n=read();
	for(int i=0;i<n;++i)
		a[i]=read();
	poly_inv(a,b,n);
	for(int i=0;i<n;++i)
		printf("%d ",b[i]); 

	return 0;
}

