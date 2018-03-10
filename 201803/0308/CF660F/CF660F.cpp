#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N=2e5+10;
LL n,res;
LL a[N],pre[N],pre2[N],c[N];
vector<LL>q;

double slope(LL x,LL y)
{
	return (double)(c[x]-c[y])/(x-y);
}

LL binary(LL x,LL l,LL r)
{
	while(l+1<r)
	{
		LL mid=(l+r)>>1;
		if(slope(q[mid],q[mid-1])>x)
			l=mid;
		else
			r=mid;
	}
	return q[l];
}

int main()
{
	freopen("CF660F.in","r",stdin);
	freopen("CF660F.out","w",stdout);
	
	scanf("%I64d",&n);
	for(LL i=1;i<=n;++i)
	{
		scanf("%I64d",&a[i]);
		pre[i]=pre[i-1]+a[i];
		pre2[i]=pre2[i-1]+a[i]*i;
		c[i]=1ll*i*pre[i]-pre2[i];
	}

	q.push_back(0);
	for(LL i=1;i<=n;++i)
	{
		LL j=binary(pre[i],0,q.size());
		res=max(res,pre2[i]-pre2[j]-j*(pre[i]-pre[j]));
		while(q.size()>1 && slope(q[q.size()-1],q[q.size()-2])<slope(i,q[q.size()-1]))
			q.pop_back();
		q.push_back(i);
	}
	printf("%I64d\n",res);
	
	return 0;
}
