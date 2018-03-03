#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=45989;
const int N=505;
int n,m,s,tot=1,cnt;
LL q;
int num[N],c[N][2];

struct Tmat
{
	int mat[N][N];
	
	void clear(){
		memset(mat,0,sizeof(mat));
	}
};
Tmat a,ans;

Tmat operator *(Tmat &A,Tmat &B)
{
	Tmat ret;ret.clear();
	for(int k=1;k<=m;++k)
		for(int i=1;i<=m;++i)
		{
			if(A.mat[i][k]==0)
				continue;
			for(int j=1;j<=m;++j)
			{
				if(B.mat[k][j]==0)
					continue;
				(ret.mat[i][j]+=A.mat[i][k]*B.mat[k][j]%mod)%=mod;
			}
		}
	return ret;
}

void add(int u,int v)
{
	c[++tot][0]=u;c[tot][1]=v;
	c[++tot][0]=v;c[tot][1]=u;
}

void qpow()
{
	for(int i=1;i<=m;++i)
		ans.mat[i][i]=1;
	--q;
	for(;q;q>>=1,a=a*a)
		if(q&1)
			ans=ans*a;
}

int main()
{
	freopen("BZOJ3792.in","r",stdin);
	freopen("BZOJ3792.out","w",stdout);
	
	scanf("%d%d%d%lld",&n,&m,&s,&q);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	m=tot;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(i!=j && i!=(j^1) && c[i][1]==c[j][0])
				a.mat[i][j]=1;
	qpow();
	for(int i=1;i<=m;++i)
		if(c[i][0]==s)
			num[++cnt]=i;
	for(int i=1;i<=n;++i)
	{
		int sum=0;
		for(int j=1;j<=m;++j)
			if(c[j][1]==i)
				for(int k=1;k<=cnt;++k)
					(sum+=ans.mat[num[k]][j])%=mod;
		printf("%d\n",sum);
	}
	
	return 0;
}
