#include<bits/stdc++.h>
using namespace std;

const int INF=1e9+7;
const int N=20;
const int M=(1<<N);
int n,m;
int a[N],b[N],c[N<<1],f[M];

int main()
{
//	freopen("BZOJ3900.in","r",stdin);
//	freopen("BZOJ3900.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<(1<<n);++i)
	{
		int k=0,p=0;
		for(int j=0;(1<<j)<=i;++j)
			if((1<<j)&i)
			{
				if(abs(a[j+1]-b[j+1])>m)
					p=1;
				c[++k]=a[j+1];
				c[++k]=b[j+1];
			}
		if(p==0)
			f[i]=0;
		else
		{
			sort(c+1,c+k+1);
			p=0;
			for(int j=1;j<=k;j+=2)
				if(c[j+1]-c[j]>m)
				{
					p=1;
					break;
				}
			f[i]=p?INF:k/2-1;
		}
	}
	for(int i=1;i<(1<<n);++i)
		for(int j=(i-1)&i;j;j=(j-1)&i)
			f[i]=min(f[i],f[j]+f[i^j]);
	printf("%d\n",f[(1<<n)-1]==INF?-1:f[(1<<n)-1]);
	
	return 0;
}
