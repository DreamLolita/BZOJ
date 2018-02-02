#include<bits/stdc++.h>
using namespace std;

const int N=22;
const int M=1<<N;
int n,T,cnt;
int ans[N],w[N][N];
bool f[M];

int main()
{
//	freopen("BZOJ4057.in","r",stdin);
//	freopen("BZOJ4057.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<(1<<n);++i)
			f[i]=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&w[i][j]);
		f[0]=1;
		for(int i=0;i<(1<<n);++i)
		{
			if(f[i])
			{
				for(int j=0;j<n;++j)
				{
					if(!(i>>j&1) && !f[i|(1<<j)])
					{
						int sum=0;
						for(int k=0;k<n;++k)
							if(!(i>>k&1))
								sum-=w[j][k];
						if(sum<0)
							f[i|(1<<j)]=1;
					}
				}
			}
		}
		cnt=0;
		for(int i=0;i<n;++i)
			if(f[((1<<n)-1)^(1<<i)])
				ans[++cnt]=i+1;
		sort(ans+1,ans+cnt+1);
		for(int i=1;i<=cnt;++i)
			printf(i!=cnt?"%d ":"%d\n",ans[i]);
		if(!cnt)
			printf("0\n");
	}
	
	return 0;
}
