#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,mid,pos,ans;
int num[N],sum[N],l[N<<1],r[N<<1];

int main()
{
	freopen("BZOJ1303.in","r",stdin);
	freopen("BZOJ1303.out","w",stdout);
	
	scanf("%d%d",&n,&mid);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&num[i]);
		if(num[i]>mid)
			num[i]=1;
		else
		if(num[i]<mid)
			num[i]=-1;
		else
		{
			num[i]=0;
			pos=i;
		}
	}
	l[n]=r[n]=1;
	for(int i=pos-1;i;--i)
	{
		sum[i]=sum[i+1]+num[i];
		l[sum[i]+n]++;
	}
	for(int i=pos+1;i<=n;++i)
	{
		sum[i]=sum[i-1]+num[i];
		r[sum[i]+n]++;
	}
	for(int i=0;i<=2*n-1;++i)
		ans+=l[i]*r[2*n-i];
	printf("%d\n",ans);
	
	return 0;
}
