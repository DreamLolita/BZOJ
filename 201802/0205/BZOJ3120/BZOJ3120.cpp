#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=188;
const int mod=1e9+7;
int n,P,Q,cnt;
int num[5][11][11],C[11][11];
LL m;

struct Matrix
{
	int a[N][N];
	void init()
	{ 
		memset(a,0,sizeof(a));
		for(int i=1;i<=cnt;++i)
			a[i][i]=1;
	}
	void _clear(){
		memset(a,0,sizeof(a));
	}
};
Matrix ans;

Matrix operator *(Matrix A,Matrix B)
{
	Matrix ret;ret._clear();
	for(int i=1;i<=cnt;++i)
		for(int k=1;k<=cnt;++k)
			if(A.a[i][k])
				for(int j=1;j<=cnt;++j)
					if(B.a[k][j])
						(ret.a[i][j]+=1ll*A.a[i][k]*B.a[k][j]%mod)%=mod;
	return ret;				
} 

Matrix operator ^(Matrix x,LL y)
{
	Matrix ret;ret.init();
	for(;y;y>>=1,x=x*x)
		if(y&1)
			ret=ret*x;
	return ret;
}

void init()
{
	scanf("%d%lld%d%d",&n,&m,&P,&Q);
	for(int i=0;i<=n;++i)
	{
		C[i][0]=1;
		for(int j=1;j<=n;++j)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	
	for(int i=0;i<=Q;++i)
		for(int j=0;j<=n;++j)
			for(int k=0;j+k<=n;++k)
				if(P!=2 || j+k==n)
					num[i][j][k]=++cnt;
	for(int i=0;i<=Q;++i)
		for(int j=0;j<=n;++j)
			for(int k=0;j+k<=n;++k)
				if(P!=2 || j+k==n)
				{
					int t1=num[i][j][k];
					for(int p=0;p<=j;++p)
						for(int q=0;q<=k;++q)
							if(P!=2 || q==0)
							{
								int t2=num[i+(p+q==n)][(n-j-k)+(j-p)+(k-q)][p];
								if(i+(p+q==n)>Q)
									continue;
								(ans.a[t1][t2]+=C[j][p]*C[k][q])%=mod;
							}
				}
}

void solve()
{
	if(P==1)
	{
		puts("1");
		return;
	}
	
	ans=ans^m;
	int ret=0;
	for(int i=1;i<=cnt;++i)
		(ret+=ans.a[num[0][n][0]][i])%=mod;
	printf("%d\n",ret);
}

int main()
{
//	freopen("BZOJ3120.in","r",stdin);
//	freopen("BZOJ3120.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
