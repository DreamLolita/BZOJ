#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e5+10;
int n,m,lim;
int a[N];
LL sum[N],ans[N];

struct Tnode
{
	int x,y,id;
};
Tnode q[N];

bool cmp(Tnode A,Tnode B)
{
	return A.y<B.y;
}

int main()
{
	freopen("CF103D.in","r",stdin);
	freopen("CF103D.out","w",stdout);
	
	scanf("%d",&n);lim=sqrt(n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&q[i].x,&q[i].y);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		if(q[i].y<lim)
		{
			if(q[i].y!=q[i-1].y)
			{
				for(int j=n;j>=1;--j)
				{
					if(j>n-q[i].y)
						sum[j]=a[j];
					else
						sum[j]=sum[j+q[i].y]+a[j];
				}
			}
			ans[q[i].id]=sum[q[i].x];
		}
		else
		{
			for(int j=q[i].x;j<=n;j+=q[i].y)
				ans[q[i].id]+=a[j];
		}
	}
	for(int i=1;i<=m;++i)
		printf("%I64d\n",ans[i]);
	
	return 0;
}
