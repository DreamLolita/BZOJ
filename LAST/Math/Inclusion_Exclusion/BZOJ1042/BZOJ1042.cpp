#define FIO "BZOJ1042"
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm> 
using namespace std;

typedef long long LL;
const int MAXN=100005;
int c[MAXN],d[MAXN];
int s,T;
LL ans,f[MAXN];

void Pretreat()
{
	f[0]=1;
	for(int i=0;i<4;++i)
		for(int j=c[i];j<MAXN;++j)
			f[j]+=f[j-c[i]];
}

LL ret(int k)
{
	if(k>=0)
		return f[k];
	return 0;
}

void solve()
{
//printf("S=%d   F[S]:%d\n",s,f[s]);
	ans=f[s];
	for(int i=0;i<4;++i)
		ans-=ret(s-c[i]*(d[i]+1));
	for(int i=0;i<4;++i)
		for(int j=i+1;j<4;++j)
			ans+=ret(s-c[i]*(d[i]+1)-c[j]*(d[j]+1));
	
	int tmp;
	for(int i=0;i<4;++i)
	{
		tmp=0;
		for(int j=0;j<4;++j)
			if(j!=i)
				tmp+=c[j]*(d[j]+1);
		ans-=ret(s-tmp);
	}
	ans+=ret(s-tmp-c[3]*(d[3]+1));
}

int main()
{
//	freopen(FIO ".in","r",stdin);
//	freopen(FIO ".out","w",stdout);
	
	for(int i=0;i<4;++i)
		scanf("%d",&c[i]);
	Pretreat();
	
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<4;++i)
			scanf("%d",&d[i]);
		scanf("%d",&s);
		solve();
		cout<<ans<<endl;
	}
	
	return 0;
}
