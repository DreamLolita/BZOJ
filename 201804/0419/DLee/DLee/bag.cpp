#include<bits/stdc++.h>
using namespace std;

const int INF=2139062143;
const int N=22;
const int K=(1<<22)+1;
int n,S,mx;
int a[N],f[K],g[K];

int read()
{
	int ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3)+(ret<<1)+(ch-'0');ch=getchar();}
	return ret;
}

int main()
{
	freopen("bag.in","r",stdin);
	freopen("bag.out","w",stdout);
	
	memset(f,127,sizeof(f));memset(g,127,sizeof(g));
	n=read();S=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	mx=(1<<n)-1;
	f[0]=1;g[0]=0;
	for(int i=0;i<=mx;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if(i^(1<<j-1))
			{
				int ns=i^(1<<j-1);
				if(f[i]<f[ns] && g[i]+a[j]<=S)
					f[ns]=f[i],g[ns]=g[i]+a[j];
				else
				if(f[i]+1<f[ns])
					f[ns]=f[i]+1,g[ns]=a[j];
			}
		}
	}
	printf("%d\n",f[mx]);
	
	return 0;
}
