#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
double INF=1e9;
double eps=1e-12;
int n;
double E,ans;

struct Tnode
{
	double s,k,v,x;
};
Tnode a[N];

double calc(double lambda)
{
	double ret=0;
	for(int i=1;i<=n;++i)
	{
		double l=max(0.0,a[i].v),r=1.0*INF;
		while(r-l>eps)
		{
			double mid=(l+r)/2.0;
			if(2.0*lambda*a[i].k*mid*mid*(mid-a[i].v)>1.0)
				r=mid;
			else
				l=mid;
		}
		a[i].x=(l+r)/2.0;
		ret+=a[i].k*(a[i].x-a[i].v)*(a[i].x-a[i].v)*a[i].s;
	}
	return ret;
}

void solve()
{
	double l=0.0,r=1.0*INF;
	while(r-l>eps)
	{
		double mid=(l+r)/2.0;
		if(calc(mid)>=E)
			l=mid;
		else
			r=mid;
	}
}

int main()
{
//	freopen("BZOJ2876.in","r",stdin);
//	freopen("BZOJ2876.out","w",stdout);
	
	scanf("%d%lf",&n,&E);
	for(int i=1;i<=n;++i)
		scanf("%lf%lf%lf",&a[i].s,&a[i].k,&a[i].v);
	solve();
	for(int i=1;i<=n;++i)
		ans+=a[i].s/a[i].x;
	printf("%0.10lf\n",ans);
	
	return 0;
}
