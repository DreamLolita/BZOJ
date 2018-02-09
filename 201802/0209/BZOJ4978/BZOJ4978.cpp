#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1e5+10;
const int K=9000;
int n;
int a[N],b[N],p1[N],p2[N];
int ans[N<<1];

int main()
{
	freopen("BZOJ4978.in","r",stdin);
	freopen("BZOJ4978.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]),p1[a[i]]=i;
	for(int i=0;i<n;++i)
		scanf("%d",&b[i]),p2[b[i]]=i;
	for(int i=0;i<=n*2;++i)
		ans[i]=INF;
		
	for(int i=0;i<K;++i)
		for(int j=0;j<=i;++j)
		{
			if(j>=n || i-j>=n)
				continue;
			ans[p1[j]+p2[i-j]]=min(ans[p1[j]+p2[i-j]],i);
		}
	for(int i=0;i<n*2-1;++i)
		if(ans[i]==INF)
		{
			for(int j=0;j<=i;++j)
				if(j<n && i-j<n)
					ans[i]=min(ans[i],a[i-j]+b[j]);
		}
	for(int i=0;i<n*2-1;++i)
		printf("%d ",ans[i]);
		
	return 0;
}
