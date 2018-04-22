#include<bits/stdc++.h>
using namespace std;

int n,x,y,ans;

int main()
{
	freopen("2466.in","r",stdin);
	freopen("2466.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&y);ans=0;
		while(x!=y)
		{
			++ans;
			if(y>x)
				swap(x,y);
			x>>=1;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
