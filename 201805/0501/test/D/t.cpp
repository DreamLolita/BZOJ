#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("C.in","w",stdout);

	int n=2e5,q=2e5;
	long long t1=(LL)999999999,t2=(LL)1234567890;
	printf("%d %d\n",n,q);
	for(int i=1;i<=n;++i)
		printf("%lld ",t1);
	puts("");
	for(int i=1;i<=q;++i)
		printf("%lld ",t2);

	return 0;
}

