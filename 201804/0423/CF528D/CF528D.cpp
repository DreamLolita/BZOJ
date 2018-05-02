#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const double eps=1e-4;
const int N=524288;
int l1,l2,n,m,K,len,cnt,totans;
int rev[N],s[N],sum[N];
char mp[]={'A','G','C','T'},c;
char a[N],b[N];

struct E
{
	double r,i;
	E(){}
	E(double rr,double ii){r=rr;i=ii;}
	E operator + (E const &A)const{
		return E(r+A.r,i+A.i);
	}
	E operator - (E const &A)const{
		return E(r-A.r,i-A.i);
	}
	E operator * (E const &A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}A[N],B[N],ans[N];

void fft(E *a,int n,int f)
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
	freopen("CF528D.in","r",stdin);
	freopen("CF528D.out","w",stdout);
	
	scanf("%d%d%d%s%s",&l1,&l2,&K,a+1,b+1);
	for(n=1,len=0;n<=max(l1,l2)*2;n<<=1,len++);
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	for(int x=0;x<4;++x)
	{
		memset(s,0,sizeof(s));memset(A,0,sizeof(A));memset(B,0,sizeof(B));
		cnt=0;c=mp[x];
		for(int i=1;i<=l1;++i)
			if(a[i]==c)
				s[max(1,i-K)]++,s[min(l1+1,i+K+1)]--;
		for(int i=1;i<=l1;++i)
		{
			s[i]+=s[i-1];
			if(s[i])
				A[i]=E(1,0);
		}
		for(int i=1;i<=l2;++i)
			if(b[i]==c)
				B[l2-i+1]=E(1,0),++cnt;
		
		fft(A,n,1);fft(B,n,1);
		for(int i=0;i<n;++i)
			ans[i]=A[i]*B[i];
		fft(ans,n,-1);
		for(int i=1;i<=l1-l2+1;++i)
			if(fabs(ans[i+l2].r-cnt)<eps)
				sum[i]++;
	}
	for(int i=1;i<=l1-l2+1;++i)
		if(sum[i]==4)
			++totans;
	printf("%d\n",totans);
	
	return 0;
}
