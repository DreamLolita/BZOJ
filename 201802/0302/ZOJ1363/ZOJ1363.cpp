#include<bits/stdc++.h>
using namespace std;

const int N=6e4+10;
const int M=105;
int c,n,m;
double f[N][M];

inline void solve_water()
{
	if(n>60000)
		n=60000+(n&1);
	for(int i=0;i<N;++i)
		for(int j=0;j<=c+1;++j)
			f[i][j]=0;
	f[1][1]=1;

	for(int i=2;i<=n;++i)
	{
		for(int j=0;j<=min(i,c);++j)
		{
			if((i+j)&1)
			{
				f[i][j]=0;
				continue;
			} 
		 if(j)
				f[i][j]+=1.0*f[i-1][j-1]*(c-j+1)/c;
			if(j<i)
				f[i][j]+=1.0*f[i-1][j+1]*(j+1)/c;
		}
	}
	printf("%0.3lf\n",f[n][m]);
}

int main()
{
	freopen("chocolate.in","r",stdin);
	freopen("chocolate.out","w",stdout);
	
	while(~scanf("%d",&c))
	{
		if(c==0)
			break;
		scanf("%d%d",&n,&m);
		if(n==0 && m==0)
		{
			puts("1.000");
			continue;
		}
		if(n<m || m>c || (m+n)&1)
		{
			puts("0.000");
			continue;
		}
		solve_water();
	}
	
	return 0;
}
