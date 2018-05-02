#include<bits/stdc++.h>
using namespace std;

const int N=30;
int n,m,mod,totans;
int nex[N];
char s[N];

struct Matrix
{
	int a[N][N];
	
	Matrix(){
		memset(a,0,sizeof(a));
	}
	void init(){
		for(int i=0;i<m;++i)
			a[i][i]=1;
	}
	Matrix operator * (Matrix const &A)const{
		Matrix ret;
		for(int i=0;i<m;++i)
			for(int j=0;j<m;++j)
				for(int k=0;k<m;++k)
					(ret.a[i][j]+=a[i][k]*A.a[k][j])%=mod;
		return ret;
	}
}ans,mi;

void getnex(char *s)
{
	int len=strlen(s);nex[0]=nex[1]=0;
	for(int i=1;i<len;++i)
	{
		int j=nex[i];
		while(j && s[i]!=s[j])
			j=nex[j];
		nex[i+1]=s[i]==s[j]?j+1:0;
	}
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<=9;++j)
		{
			int k=i;
			while(k && s[k]!=(j^48))
				k=nex[k];
			if(s[k]==(j^48))
				++k;
			if(k!=m)
				mi.a[i][k]++;
		}
	}
}

int main()
{
	freopen("BZOJ1009.in","r",stdin);
	freopen("BZOJ1009.out","w",stdout);
	
	scanf("%d%d%d%s",&n,&m,&mod,s);
	getnex(s);

/*	for(int i=0;i<m;++i)
	{
		for(int j=0;j<m;++j)
			printf("%d ",mi.a[i][j]);
		puts("");
	}*/
	
	ans.init();
	for(int i=n;i;i>>=1,mi=mi*mi)
		if(i&1)
			ans=ans*mi;
	for(int i=0;i<m;++i)
		totans=(totans+ans.a[0][i])%mod;
	printf("%d\n",totans);
	
	return 0;
}
