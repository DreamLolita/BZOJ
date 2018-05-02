#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("BZOJ1146.in","w",stdout);
	
	srand(time(0));
	int n=5000,m=10000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;++i)
		printf("%d ",rand()%100+1);
	puts("");
	for(int i=2;i<=n;++i)
	{
		int v=rand()%(i-1)+1;
		printf("%d %d\n",v,i);
	}
	for(int i=1;i<=m;++i)
	{
		int op=rand()%2,u,v;
		if(op)
		{
			op=rand()%50+1;v=rand()%(n-1)+1;u=rand()%(n-1)+1;
			printf("%d %d %d\n",op,u,v);
		}
		else
		{
			u=rand()%(n-1)+1;v=rand()%100+1;
			printf("%d %d %d\n",op,u,v);
		}
	}
	return 0;
}
