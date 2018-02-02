#include<bits/stdc++.h>
using namespace std;

int n,ans,T;

int main()
{
//	freopen("BZOJ4063.in","r",stdin);
//	freopen("BZOJ4063.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ans=0;
		while(n--)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			double r=sqrt(x*x+y*y);
			int p=1;
			while(20*(11-p)>=r && p<=10)
				++p;
			ans+=p-1;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
