#include<bits/stdc++.h>
using namespace std;

int n,a[3000];

int main()
{
	
/*	freopen("tasksauthor2.out","w",stdout);
	n=1990;
	printf("%d\n",n);
	for(int i=n;i>=1;--i)
		if(i==522)
			printf("1\n");
		else
			printf("0\n");*/
	
/*	freopen("tasksauthor3.out","w",stdout);
	n=1984;
	printf("%d\n",n);
	for(int i=0;i<n;++i)
		a[i]=i;
	for(int i=0;i<n;++i) swap(a[i/2], a[i]);	
	for(int i=0;i<n;++i) printf("%d\n", a[i]);*/
	
	freopen("tasksauthor4.out","w",stdout);
	
	n=1001;int mx=44;
	printf("%d\n",n);
	for(int i=25;i>=13;--i)
	{
		for(int j=0;j<=mx;++j)
			printf("%d\n",i),--n;
		--mx;
	}
	mx=43;
	for(int i=12;i>=0;--i)
	{
		for(int j=0;j<=mx;++j)
			printf("%d\n",i),--n;
		--mx;
	}
	
	return 0;
}
