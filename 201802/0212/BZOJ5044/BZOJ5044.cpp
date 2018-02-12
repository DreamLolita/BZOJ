#include<bits/stdc++.h>
using namespace std;

int n,k,x,y;

int main()
{
	freopen("BZOJ5044.in","r",stdin);
	freopen("BZOJ5044.out","w",stdout);
	
	scanf("%d",&n);
	printf("0 0\n");
	k=(n-3-(n&1^1))/2;
	for(int i=1;i<=k;++i)
	{
		if(i&1)
			x-=3,y+=4;
		else
			x+=3,y+=4;
		printf("%d %d\n",x,y);
	}
	x+=4;y-=3;
	printf("%d %d\n",x,y);
	for(int i=k;i;--i)
	{
		if(i&1)
			x+=3,y-=4;
		else
			x-=3,y-=4;
		printf("%d %d\n",x,y);
	}
	if(n&1)
		printf("-20 -21\n");
	else
		printf("1 -7\n-3 -4\n");
	
	return 0;
}
