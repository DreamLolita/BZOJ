#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=5e5+5;
LL sum;
int n,m,o;
int fa[N],ans[N];


struct Troom
{
	int c,p;
};
Troom a[N],b[N];

bool cmpc(Troom A,Troom B)
{
	return A.c>B.c;
}

bool cmpp(Troom A,Troom B)
{
	if(A.p==B.p)
		return A.c<B.c;
	return A.p<B.p;
}

int getf(int x)
{
	return x==fa[x]?x:fa[x]=getf(fa[x]);
}

int findf(int x)
{
	int l=1,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(a[getf(mid)].p<x)
			l=mid+1;
		else
			r=mid;
	}
	return getf(l);
}

int main()
{
//	freopen("BZOJ2385.in","r",stdin);
//	freopen("BZOJ2385.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&o);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].c,&a[i].p);
	for(int i=1;i<=m;++i)
		scanf("%d%d",&b[i].c,&b[i].p);
	sort(a+1,a+n+1,cmpp);sort(b+1,b+m+1,cmpc);
	for(int i=1;i<=n+1;++i)
		fa[i]=i;
	a[n+1].p=INF;
	
	for(int i=1;i<=m;++i)
	{
		int j=findf(b[i].p);
		if(j<=n && a[j].c<b[i].c)
			ans[i]=b[i].c-a[j].c,fa[j]=j+1;
	}
	sort(ans+1,ans+m+1);
	
	for(int i=m-o+1;i<=m;++i)
		sum+=ans[i];
	printf("%lld\n",sum);
	
	return 0;
}
