#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,k;
int a[N],q[N];
LL sum[N],f[N],g[N];

double cross(int i,int j)
{
	return (double)(1.0*sum[j]*sum[j]-1.0*sum[i]*sum[i]+g[i]-g[j])/(double)(sum[j]-sum[i]);
}

void init()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	
	int tmp=0;
	for(int i=1;i<=n;++i)
		if(a[i]!=0)
			a[++tmp]=a[i];
	n=tmp;
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
}

void solve()
{
	for(int i=1;i<=k;++i)
	{
		int head=1,tail=0;
		for(int j=i;j<=n;++j)
		{
			while(head<tail && cross(q[tail-1],q[tail])>cross(q[tail],j-1))
				--tail;
			q[++tail]=j-1;
			while(head<tail && cross(q[head],q[head+1])<sum[j])
				++head;
			int t=q[head];
			f[j]=g[t]+(sum[j]-sum[t])*sum[t];
		}
		for(int j=i;j<=n;++j)
			swap(f[j],g[j]);
	}
	printf("%lld\n",g[n]);
}

int main()
{
//	freopen("BZOJ3675.in","r",stdin);
//	freopen("BZOJ3675.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
