#include<bits/stdc++.h>
using namespace std;

typedef long double ldb;
const int N=4e6+10;
const ldb pi=acos(-1);
int n,K,len1,len2;
int c[N],d[N];

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct E
{
    ldb r,i;
    E(){}
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
E a[N],b[N],A[N];

int rev(int id,int n)
{
    int ret=0;
    for(int i=0;(1<<i)<n;++i)
    {
        ret<<=1;
        if(id&(1<<i))
            ret|=1;
    }
    return ret;
}

void fft(E *a,int n,int f)
{
	for(int i=0;i<n;++i)
		A[rev(i,n)]=a[i];
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;++k,w=w*wn)
			{	
				E x=A[j+k],y=w*A[j+k+i];
				A[j+k]=x+y;A[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)
		for(int i=0;i<n;++i)
			A[i].r/=n;
    for(int i=0;i<n;++i)
        a[i]=A[i];
}

void solve(int *x,int &n,int *y,int &m)
{
    int len=1;
    while(len<=n+m)
        len<<=1;
    for(int i=0;i<len;++i)
        a[i]=E(x[i],0),b[i]=E(y[i],0);
    fft(a,len,1);fft(b,len,1);
    for(int i=0;i<len;++i)
        a[i]=a[i]*b[i];
    fft(a,len,-1);
    for(int i=0;i<len;++i)
    {
        if(a[i].r>0.5)
            x[i]=1;
        else
            x[i]=0;
    }
    n+=m;
}

int main()
{
    freopen("CF632E.in","r",stdin);
    freopen("CF632E.out","w",stdout);

    n=read();K=read();
    for(int i=0;i<n;++i)
    {
        int x=read();
        c[x]=1;
    }
    d[0]=1;len1=1;len2=1001;
    while(K)
    {
        if(K&1)
            solve(d,len1,c,len2);
        solve(c,len2,c,len2);
        K>>=1;
    }
    for(int i=0;i<len1;++i)
        if(d[i])
            printf("%d ",i);
                

    return 0;
}
