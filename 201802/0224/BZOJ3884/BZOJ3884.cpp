#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e7+10;
int T,p,cnt;
int pri[N],phi[N];
bool mark[N];

void getphi()
{
	phi[1]=1;
	for(int i=2;i<N;i++)
	{
		if(!mark[i])phi[i]=i-1,pri[++cnt]=i;
		for(int j=1;j<=cnt&&i*pri[j]<N;j++)
		{
			mark[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			else phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
}

int qpow(ll a,ll b,int p)
{
	ll ans=1;a%=p;
	for(ll i=b;i;i>>=1,a=a*a%p)
		if(i&1)ans=ans*a%p;
	return ans;
}

int solve(int p)
{
	if(p==1)
        return 0;
	int k=0;
	while(~p&1)
        p>>=1,k++;
	int pp=phi[p],res=solve(pp);
	res=(res+pp-k%pp)%pp;
	res=qpow(2,res,p)%p;
	return res<<k;
}

int main()
{
    freopen("BZOJ3884.in","r",stdin);
    freopen("BZOJ3884.out","w",stdout);

	getphi();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&p);
		printf("%d\n",solve(p));
	}
	return 0;
}
