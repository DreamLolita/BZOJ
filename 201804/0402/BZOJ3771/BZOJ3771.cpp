#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=40005;
const int M=N*6;
const double pi=acos(-1);
int n,m,len;
int rev[M];

struct E
{
	double r,i;
	E(){}
	E(double rr,double ii){
		r=rr;i=ii;
	}
	
	E operator + (E const &P)const{
		return E(r+P.r,i+P.i);
	}
	
	E operator - (E const &P)const{
		return E(r-P.r,i-P.i);
	}
	
	E operator * (E const &P)const{
		return E(r*P.r-i*P.i,r*P.i+i*P.r);
	}
	
	E operator / (E const &P)const{
		return E((r*P.r+i*P.i)/(P.r*P.r+P.i*P.i),(i*P.r-r*P.i)/(P.r*P.r+P.i*P.i));
	}
}A[M],B[M],C[M],D[M];

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
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		A[x].r++;B[x*2].r++;C[x*3].r++;
	}
	m=3*(N-5);
	for(n=1;n<=m;n<<=1)
		++len;
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
}

void solve()
{
	E t2=E(2,0),t3=E(3,0),t6=E(6,0);
	fft(A,1);fft(B,1);fft(C,1);
	
	for(int i=0;i<n;++i)
		A[i]=A[i]+(A[i]*A[i]-B[i])/t2+(A[i]*A[i]*A[i]-t3*A[i]*B[i]+t2*C[i])/t6;
	fft(A,-1);
	for(int i=1;i<m;++i)
	{
		LL ans=(LL)(A[i].r+0.5);
		if(ans!=0)
			printf("%d %lld\n",i,ans);
	}
	
/*	for(int i=0;i<n;++i)
		D[i]=B[i],B[i]=(A[i]*A[i]-B[i]),C[i]=A[i]*A[i]*A[i]-t3*A[i]*D[i]+t2*C[i];	
	fft(A,-1);fft(B,-1);fft(C,-1);
	for(int i=1;i<m;++i)
	{
		LL ans=(LL)(A[i].r+0.5)+(B[i].r+0.5)/2+(C[i].r+0.5)/6;
		if(ans!=0)
			printf("%d %lld\n",i,ans);
	}*/
}

int main()
{
	freopen("BZOJ3771.in","r",stdin);
	freopen("BZOJ3771.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
