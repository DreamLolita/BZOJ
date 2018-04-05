#include<bits/stdc++.h>
using namespace std;

const int N=400000;

int main()
{
	freopen("BZOJ4115.in","w",stdout);
	srand(time(0));_sleep(200);
	int T=100000;
	printf("%d\n",T);
	for(int i=1;i<=T;++i)
	{
		int l,r;
		l=rand()%N+1;r=rand()%N+1;
		if(l>r)
			swap(l,r);
		printf("%d %d\n",l,r);
	}
	
	return 0;
}
