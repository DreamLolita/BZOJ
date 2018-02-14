#include<bits/stdc++.h>
using namespace std;

const int N=2e6+2;
int n,m,mx,nn,x,i,j;
int sum[N],cnt[N],las[N];

int main()
{
	freopen("BZOJ3827.in","r",stdin);
	freopen("BZOJ3827.out","w",stdout);
	
	scanf("%d%d",&n,&m);nn=n*2;
	for(i=1;i<=n;++i)
	{
		scanf("%d",&sum[i]);
		mx=max(mx,sum[i]);
		sum[i+n]=sum[i];
	}
	for(i=1;i<=nn;++i)
		sum[i]+=sum[i-1];
	while(m--)
	{
		scanf("%d",&x);
		if(x<mx)
		{
			puts("NIE");
			continue;
		}
		
		for(i=1;i<=nn;++i)
			las[i]=i,cnt[i]=0;
		
		j=1;
		for(i=n+1;i<=nn;++i)
		{
			while(sum[i]-sum[j]>x)
				++j;
			las[i]=las[j];cnt[i]=cnt[j]+1;
			if(i-las[i]>=n)
			{
				printf("%d\n",cnt[i]);
				break;
			}
		}
	}
	
	return 0;
}
