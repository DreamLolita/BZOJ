#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,tmp,A,B;
int x[N],a[N],b[N];

int main()
{
	freopen("BZOJ4723.in","r",stdin);
	freopen("BZOJ4723.out","w",stdout);
	
	scanf("%d%d",&n,&tmp);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&x[i],&a[i],&b[i]);
	for(int i=1;i<=n;++i)
	{
		tmp=x[i]-x[i-1];
		A=max(A-tmp,a[i]+1);B=min(B+tmp,b[i]-1);
		if((A&1)!=(x[i]&1))
			++A;
		if((B&1)!=(x[i]&1))
			--B;
		if(A>B)
		{
			puts("NIE");
			return 0;
		}
	}
	printf("%d\n",(A+x[n])/2);
	
	return 0;
}
