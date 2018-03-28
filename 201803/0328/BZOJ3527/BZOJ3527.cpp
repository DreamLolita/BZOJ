#include<bits/stdc++.h>
using namespace std;

const int N=262144;
const double pi=acos(-1);
int n,m,len;
int rev[N];

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
};
E f[N],g[N],h[N],e1[N],e2[N];

void fft(E *a,int f)
{
	for(int i=0;i<n;++i)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
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
		for(int i=0;i<n;++i)
			a[i].r/=n;
}

void init()
{
	scanf("%d",&n);--n;
	for(int i=0;i<=n;++i)
	{
		double x;
		scanf("%lf",&x);
		f[i].r=g[n-i].r=x;
	}
	for(int i=1;i<=n;++i)
		h[i].r=(double)1.0/i/i;
	m=2*n;
	for(n=1;n<=m;n<<=1)
		++len;
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
}

void solve()
{	
	fft(f,1);fft(h,1);fft(g,1);
	for(int i=0;i<n;++i)
		e1[i]=f[i]*h[i],e2[i]=g[i]*h[i];
	fft(e1,-1);fft(e2,-1);
	for(int i=0;i<=m/2;++i)
		printf("%0.3lf\n",e1[i].r-e2[m/2-i].r);
}

int main()
{
	freopen("BZOJ3527.in","r",stdin);
	freopen("BZOJ3527.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
