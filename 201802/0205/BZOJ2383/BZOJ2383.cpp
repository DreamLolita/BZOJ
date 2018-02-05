#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n;
double a[N],r[N];
stack<int>q;

double sqr(double x)
{
	return x*x;
}

int main()
{
//	freopen("BZOJ2383.in","r",stdin);
//	freopen("BZOJ2383.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%lf%lf",&a[i],&r[i]);
		while(!q.empty())
		{
			int j=q.top();
			r[i]=min(r[i],sqr(a[i]-a[j])/4.0/r[j]);
			if(r[i]>=r[j])
				q.pop();
			else
				break;
		}
		q.push(i);
		printf("%0.3f\n",r[i]);
	}
	
	return 0;
}
