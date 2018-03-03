#include<bits/stdc++.h>
using namespace std;

int T,n,m,a,b;

int main()
{
	freopen("BZOJ3609.in","r",stdin);
	freopen("BZOJ3609.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		a=((n-1)%m)%2;b=((n-1)/m)%2;
		if(m%2)
			printf("%d\n",a^1);
		else
			printf("%d\n",a^b^1);
	}
	
	return 0;
}
