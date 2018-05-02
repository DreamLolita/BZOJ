#include<bits/stdc++.h>
using namespace std;

const int N=2262150;
const double pi=acos(-1);
int n,m,len;
int rev[N];

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct E
{
	double r,i;
	E(){}
	E(double rx,double ix):r(rx),i(ix){}
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
E a[N],b[N];

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

int main()
{
	freopen("LGP3803.in","r",stdin);
	freopen("LGP3803.out","w",stdout);
	
	n=read();m=read();
	for(int i=0;i<=n;++i)
		a[i].r=read();
	for(int i=0;i<=m;++i)
		b[i].r=read();
	m+=n;
	for(n=1;n<=m;n<<=1)
		++len;
	for(int i=0;i<=n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	fft(a,1);fft(b,1);
	for(int i=0;i<=n;++i)
		a[i]=a[i]*b[i];
	fft(a,-1);
	for(int i=0;i<=m;++i)
		printf("%d ",(int)(a[i].r+0.5));
	return 0;
}
