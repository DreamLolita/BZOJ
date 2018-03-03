#include<bits/stdc++.h>
using namespace std;

typedef complex<double>E;
const int N=131072;
const double pi=(double)acos(-1);
int n,m,L;
char s[N];
int r[N],c[N];
E a[N],b[N];

void fft(E *x,int y)
{
	for(int i=0;i<n;++i)
		if(i<r[i])
			swap(x[i],x[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),y*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;++k,w*=wn)
			{
				E q=x[j+k],p=w*x[j+k+i];
				x[j+k]=q+p;x[j+k+i]=q-p;
			}
		}
	}
	if(y==-1)
		for(int i=0;i<n;++i)
			x[i]/=n;
}

int main()
{
	freopen("BZOJ2179.in","r",stdin);
	freopen("BZOJ2179.out","w",stdout);
	
	scanf("%d",&n);--n;
	scanf("%s",s);
	for(int i=0;i<=n;++i)
		a[i]=s[n-i]-'0';
	scanf("%s",s);
	for(int i=0;i<=n;++i)
		b[i]=s[n-i]-'0';
	m=2*n;
	for(n=1;n<=m;n<<=1,++L);
	for(int i=0;i<n;++i)
		r[i]=((r[i>>1]>>1) | ((i&1)<<(L-1)));
	fft(a,1);fft(b,1);
	for(int i=0;i<=n;++i)
		a[i]*=b[i];
	fft(a,-1);
	for(int i=0;i<=m;++i)
		c[i]=(int)(a[i].real()+0.1);
	for(int i=0;i<=m;++i)
		if(c[i]>=10)
		{
			c[i+1]+=c[i]/10;
			c[i]%=10;
			if(i==m)
				++m;
		}
	for(int i=m;i>=0;--i)
		printf("%d",c[i]);
	
	return 0;
}
