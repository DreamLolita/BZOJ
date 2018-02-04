#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=4e4+4;
const int M=1e9+10;
int n,cnt;
LL mod;
bool flag[N];
int pri[N];

struct Matrix
{
	LL m[2][2];

	Matrix(){
		memset(m,0,sizeof(m));
	}
};
Matrix init;

LL mul(LL a,LL b)
{
	a%=mod;b%=mod;
	if(a<0)	a+=mod;
	if(b<0)	b+=mod;
	LL ret=0;
	while(b)
	{
		if(b&1)
		{
			ret+=a;
			if(ret>=mod)
				ret-=mod;
		}
		a<<=1ll;
		if(a>=mod)
			a-=mod;
		b>>=1ll;
	}
	return ret;
}

Matrix operator * (Matrix a,Matrix b)
{
	Matrix ret;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k)
				(ret.m[i][j]+=mul(a.m[i][k],b.m[k][j]))%=mod;
	return ret;
}

Matrix operator ^ (Matrix a,int b)
{
	Matrix ret;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			ret.m[i][j]=(i==j);
	while(b)
	{
		if(b&1)
			ret=ret*a;
		a=a*a;
		b>>=1;
	}
	return ret;
}

void Prime()
{
	int t=sqrt(M);
	for(int i=0;i<=t;++i)
		flag[i]=false;
	flag[1]=true;
	
	for(int i=2;i<=t;++i)
	{
		if(!flag[i])
			pri[cnt++]=i;
		for(int j=0;j<cnt && i*pri[j]<=t;++j)
		{
			flag[i*pri[j]]=true;
			if(!(i%pri[j]))
				break;
		}
	}
}

int Eular(int t)
{
	int ret=1;
	for(int i=0;i<cnt && pri[i]*pri[i]<=t;++i)
	{
		if(!(t%pri[i]))
		{
			t/=pri[i];ret*=pri[i]-1;
			while(!(t%pri[i]))
			{
				t/=pri[i];
				ret=(ret*pri[i])%mod;
			}
		}
	}
	if(t>1)
		ret*=t-1;
	return ret%mod;
}

LL Get_T(int k)
{
	if(k==1)	
		return 1;
	else
	if(k==2)
		return 5;
	Matrix tmp=init^(k-2);
	LL f=3ll*tmp.m[0][0]+1ll*tmp.m[1][0]%mod;
	LL g=2ll*(f-(3ll*tmp.m[0][1]+tmp.m[1][1])-1)%mod;
	return ((g+f)%mod+mod)%mod;
}

LL Polya()
{
	LL sum=0;
	int i;
	for(i=1;i*i<n;++i)
		if(!(n%i))
		{
			sum=(sum+mul(Eular(i),Get_T(n/i)))%mod;
			sum=(sum+mul(Eular(n/i),Get_T(i)))%mod;
		}
	if(i*i==n)
		sum=(sum+mul(Get_T(i),Eular(i)))%mod;
	return sum/n;
}

int main()
{
	freopen("BZOJ3113.in","r",stdin);
	freopen("BZOJ3113.out","w",stdout);
	
	Prime();
	init.m[0][0]=3;init.m[0][1]=1;init.m[1][0]=-1;init.m[1][1]=0;
	while(scanf("%d%lld",&n,&mod)!=EOF)
	{
		mod=1ll*n*mod;
		printf("%lld\n",Polya()%(mod/n));
	}
	
	return 0;
}
