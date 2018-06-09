#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double ldb;
const int N=3e6+10;
const int mod=100;
const ldb pi=acos(-1);
int n,siz,bas,ans;
int rev[N],t[N];
char s[N];
vector<int>a,b;

struct E
{
	ldb r,i;
	E(){}
	E(ldb rx,ldb ix){
		r=rx;i=ix;
	}
	E operator + (E const&A)const{
		return E(r+A.r,i+A.i);
	}
	E operator - (E const&A)const{
		return E(r-A.r,i-A.i);
	}
	E operator * (E const&A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}x1[N],x2[N];

void fft(E *a,int n,int f)
{
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
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
			a[i].r/=(ldb)n;
}

void mul(vector<int>a,vector<int>b,vector<int>&c)
{
	int L=0,m=1,s1=(int)a.size(),s2=(int)b.size();
/*	for(int i=0;i<s1;++i)
		printf("%d ",a[i]);
	puts("");
	for(int i=0;i<s2;++i)
		printf("%d ",b[i]);
	puts("");*/
	for(;m<=s1+s2-1;m<<=1,++L);
	for(int i=1;i<m;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=0;i<s1;++i)
		x1[i]=E(a[i],0);
	for(int i=s1;i<m;++i)
		x1[i]=E(0,0);
	for(int i=0;i<s2;++i)
		x2[i]=E(b[i],0);
	for(int i=s2;i<m;++i)
		x2[i]=E(0,0);
	fft(x1,m,1);fft(x2,m,1);
	for(int i=0;i<m;++i)
		x1[i]=x1[i]*x2[i];
	fft(x1,m,-1);
	c.clear();
	for(int i=0;i<s1+s2-1;++i)
		c.push_back((int)(x1[i].r+0.5));
//	printf("c:");
//	for(int i=0;i<(int)c.size();++i)
//		printf("%d ",c[i]);
//	puts("");
}

void update(vector<int>&a)
{
	int p=0,sz=(int)a.size();
	for(int i=0;i<sz || p;++i)
	{
		if(i>=sz)
			a.push_back(0);
		LL cnt=a[i]+p;
		a[i]=cnt%mod;p=cnt/mod;
	}
}

void mul3()
{
	for(int i=0;i<(int)b.size();++i)
		b[i]*=3;
	update(b);
}


int cmp(vector<int>a)
{
	int sz=(int)a.size();
	if(sz<siz)
		return 0;
	if(sz>siz)
		return 1;
	for(int i=sz-1;~i;--i)
	{
		if(a[i]<t[i])
			return 0;
		if(a[i]>t[i])
			return 1;
	}
	return 1;
}

void solve1()
{
	int x=s[0]-'0';
	if(x<=5)
		printf("%d\n",x);
	else
	if(x==6)
		puts("5");
	else
		puts("6");
}

int check(int x)
{
	vector<int>c;
	for(int i=0;i<(int)b.size();++i)
		c.push_back(b[i]*x);
	update(c);
	return cmp(c);
}

int main()
{
	freopen("CF986D.in","r",stdin);
	freopen("CF986D.out","w",stdout);

	scanf("%s",s);int len=strlen(s);
	if(len<2)
	{
		solve1();
		return 0;
	}
	reverse(s,s+len);
	for(int i=0;i<len;i+=2)
	{
		int x=s[i]-'0';
		if(i+1<len)
			x=x+(s[i+1]-'0')*10;
		t[siz++]=x;
	}
	bas=(len-1)*(ldb)(log(10)/log(3));--bas;ans+=bas*3;
	a.push_back(3);b.push_back(1);
	for(;bas;bas>>=1)
	{
		if(bas&1)
			mul(b,a,b),update(b);
		mul(a,a,a),update(a);
	}
//	for(int i=0;i<(int)b.size();++i)
//		printf("%d ",b[i]);
//	puts("");
	for(;;ans+=3,mul3())
	{
		for(int i=2;i<=4;++i)
			if(check(i))
			{
				printf("%d\n",ans+i);
				return 0;
			}
	}
	return 0;
}
