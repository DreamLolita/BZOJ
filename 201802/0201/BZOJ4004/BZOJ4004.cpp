#include<bits/stdc++.h>
using namespace std;

typedef long double ldb;
const ldb eps=1e-8;
const int N=505;
int n,m,ans,cnt;
int vis[N];

struct THU
{
	ldb mat[N];
	int val;
};
THU a[N];

bool cmp(THU A,THU B)
{
	return A.val<B.val;
}

int main()
{
	freopen("BZOJ4004.in","r",stdin);
	freopen("BZOJ4004.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			double x;
			scanf("%lf",&x);
			a[i].mat[j]=x;
		}
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i].val);
	sort(a+1,a+n+1,cmp);
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(fabs(a[i].mat[j])>eps)
			{
				if(!vis[j])
				{
					vis[j]=i;
					ans+=a[i].val;
					++cnt;
					break;
				}
				else
				{
					ldb t=(ldb)1.0*a[i].mat[j]/a[vis[j]].mat[j];
					for(int k=j;k<=m;++k)
						a[i].mat[k]-=t*a[vis[j]].mat[k];
				}
			}
	printf("%d %d\n",cnt,ans);
	
	return 0;
}
