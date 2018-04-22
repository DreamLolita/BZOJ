#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5e5+10;
const double pi=acos(-1);
int T,n,m,q,len1,len2;
int a[N],b[N],rev[N];
LL ans[N];

struct E
{
	double r,i;
	E(){}
	E(double rx,double ix){r=rx;i=ix;}
	E operator + (E const &A)const{
		return E(r+A.r,i+A.i);
	}
	E operator - (E const &A)const{
		return E(r-A.r,i-A.i);
	}
	E operator * (E const &A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}x[N],y[N];

int read()
{
	int ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3)+(ret<<1)+(ch-'0');ch=getchar();}
	return ret*f;
}

void fft(E *a,int M,int f)
{
	for(int i=0;i<M;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<M;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<M;j+=(i<<1))
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
		for(int i=0;i<M;++i)
			a[i].r/=M;
}

void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1,len=0,M;
	for(M=1;M<=r-l+1;M<<=1)
		++len;
	for(int i=0;i<M;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	for(int i=0;i<M;++i)
		x[i]=y[i]=E(0,0);
	for(int i=l;i<=mid;++i)
		x[i-l].r=a[i];
	for(int i=mid+1;i<=r;++i)
		y[i-mid-1].r=b[i];
	fft(x,M,1);fft(y,M,1);
	for(int i=0;i<M;++i)
		x[i]=x[i]*y[i];
	fft(x,M,-1);
	for(int i=0;i<M;++i)
		ans[i+mid+1+l]+=(LL)(x[i].r+0.5);
	for(int i=0;i<M;++i)
		x[i]=y[i]=E(0,0);
	for(int i=mid+1;i<=r;++i)
		x[i-mid-1].r=a[i];
	for(int i=l;i<=mid;++i)
		y[mid-i].r=b[i];
	fft(x,M,1);fft(y,M,1);
	for(int i=0;i<M;++i)
		x[i]=x[i]*y[i];
	fft(x,M,-1);
	for(int i=0;i<M;++i)
		ans[i+1]+=(LL)(x[i].r+0.5);
	solve(l,mid);solve(mid+1,r);
}

void _reset()
{
	memset(ans,0,sizeof(ans));
	memset(a,0,sizeof(a));memset(b,0,sizeof(b));
	len1=len2=0;
}

int main()
{
	freopen("BZOJ4836.in","r",stdin);
	freopen("BZOJ4836.out","w",stdout);
	
	T=read();
	while(T--)
	{
		_reset();int t;
		n=read();m=read();q=read();
		for(int i=1;i<=n;++i)
			t=read(),a[t]++,len1=max(len1,t);
		for(int i=1;i<=m;++i)
			t=read(),b[t]++,len2=max(len2,t);
		for(int i=1;i<=min(len1,len2);++i)
			ans[0]+=1ll*a[i]*b[i];
		solve(0,max(len1,len2));
		for(int i=1;i<=q;++i)
		{
			t=read();
			printf("%lld\n",ans[t]);	
		}
	}
	return 0;
}
