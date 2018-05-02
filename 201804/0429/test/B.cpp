#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL n,A,B,sum;
LL a[1000007];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);

	n=read();A=read();B=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),sum+=a[i];
	sort(a+2,a+n+1);
	for(int i=n;i>=1;--i)
	{
		if(1ll*A*a[1]>=1ll*B*sum)
		{
			printf("%d\n",n-i);
			return 0;
		}
		sum-=a[i];
	}
	puts("0");
	return 0;
}

