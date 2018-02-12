#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1ll<<62;
const int K=65;
const int N=1e5+10;
int n,c[K][2];
LL sum,f[K][N];

int main()
{
	freopen("BZOJ5043.in","r",stdin);
	freopen("BZOJ5043.out","w",stdout);
	
	scanf("%d%lld",&n,&sum);
	while(n--)
	{
		LL x;
		scanf("%lld",&x);
		for(int i=0;i<60;++i)
			c[i][((x>>i)&1)^1]++;
	}
	for(int i=0;i<K;++i)
		for(int j=0;j<N;++j)
			f[i][j]=INF;
	f[60][0]=0;
	for(int i=59;~i;--i)
		for(int j=0;j<N;++j)
			if(f[i+1][j]<INF)
				for(int k=0;k<2;++k)
				{
					int tmp=j*2-c[i][k]+((sum>>i)&1);
					if(tmp>=0 && tmp<N)
						f[i][tmp]=min(f[i][tmp],(LL)f[i+1][j]*2+k);
				}
	if(f[0][0]==INF)
		f[0][0]=-1;
	printf("%lld\n",f[0][0]);
	
	return 0;
}
