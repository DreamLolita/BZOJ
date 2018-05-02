#include<bits/stdc++.h>
using namespace std;

const int K=1;
int mod[]={998244353,19260817,1004535809};
int n,m,mx;
int sum1[K],sum2[K];

struct Tmatrix
{
	int a[3][3];	
	Tmatrix(){memset(a,0,sizeof(a));}
	void init()
	{
		a[0][0]=a[0][1]=a[1][0]=1;
		a[1][1]=0;	
	}	
	void reinit()
	{
		a[0][0]=a[1][1]=1;
		a[0][1]=a[1][0]=1;
	}
}mi[5],rt[5];

Tmatrix mul(Tmatrix A,Tmatrix B,int now)
{
	Tmatrix ret;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k)
				(ret.a[i][j]+=1ll*A.a[i][k]*B.a[k][j]%now)%=now;
	return ret;
}

int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&m);
		mx=max(mx,m);
		for(int j=0;j<K;++j)
			mi[j].reinit(),rt[j].init();
		if(m<=2)
		{
			for(int j=0;j<K;++j)
				(sum1[j]+=1)%=mod[j];
			continue;
		}
		for(m-=2;m;m>>=1)
		{
			if(m&1)
			{
				for(int j=0;j<K;++j)
					mi[j]=mul(mi[j],rt[j],mod[j]);
			}
			for(int j=0;j<K;++j)
				rt[j]=mul(rt[j],rt[j],mod[j]);
		}
		for(int j=0;j<K;++j)
			(sum1[j]+=mi[j].a[0][0])%=mod[j];
	}
	
	for(int i=mx+1;i<=mx+100;++i)
	{
		bool flag=true;m=i;
		if(m<=2)
		{
			for(int j=0;j<K;++j)
				(sum2[j]+=1)%=mod[j];
			for(int j=0;j<K;++j)
				if(sum2[j]!=sum1[j])
				{
					flag=false;
					break;
				}
			if(flag)
			{
				printf("%d\n",m);
				return 0;
			}
			continue;
		}
		for(int j=0;j<K;++j)
			mi[j].reinit(),rt[j].init();
		for(m-=2;m;m>>=1)
		{
			if(m&1)
			{
				for(int j=0;j<K;++j)
					mi[j]=mul(mi[j],rt[j],mod[j]);
			}
			for(int j=0;j<K;++j)
				rt[j]=mul(rt[j],rt[j],mod[j]);
		}
		for(int j=0;j<K;++j)
			sum2[j]=mi[j].a[0][0]%mod[j];
		for(int j=0;j<K;++j)
			if(sum2[j]!=sum1[j])
			{
				flag=false;
				break;
			}
		if(flag)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	puts("NO");
	
	return 0;
}
