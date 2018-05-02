#include<bits/stdc++.h>
using namespace std;

int n,a[100];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("t.in","r",stdin);
	freopen("t.out","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)	
		a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=12;++i)
		printf("%d %d\n",i,lower_bound(a+1,a+n+1,i)-a);

	return 0;
}

