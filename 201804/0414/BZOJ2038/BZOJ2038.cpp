#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5e4+10;
int n,m;
int pos[N],col[N];
LL ans,sum[N];

struct Tnode
{
	int l,r,id;
	LL x,y;
};
Tnode a[N];

bool cmp1(Tnode A,Tnode B)
{
	if(pos[A.l]^pos[B.l])
		return A.l<B.l;
	return A.r<B.r;
}

bool cmp2(Tnode A,Tnode B)
{
	return A.id<B.id;
}

LL gcd(LL a,LL b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}

LL sqr(LL x)
{
	return (LL)x*x;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	int lim=(int)sqrt(n);
	for(int i=1;i<=n;++i)
		pos[i]=(i-1)/lim+1;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id=i;
	}
}

void update(int x,int v)
{
	ans-=sqr(sum[col[x]]);
	sum[col[x]]+=v;
	ans+=sqr(sum[col[x]]);
}

void solve()
{
	sort(a+1,a+m+1,cmp1);
	
	int l=1,r=0;
	for(int i=1;i<=m;++i)
	{
		for(;r<a[i].r;++r)	update(r+1,1);
		for(;r>a[i].r;--r)	update(r,-1);
		for(;l<a[i].l;++l)	update(l,-1);
		for(;l>a[i].l;--l)	update(l-1,1);
		if(a[i].l==a[i].r)
		{
			a[i].x=0;a[i].y=1;
			continue;		
		}	
		a[i].x=ans-(a[i].r-a[i].l+1);
		a[i].y=1ll*(a[i].r-a[i].l+1)*(a[i].r-a[i].l);
		LL k=gcd(a[i].x,a[i].y);
		a[i].x/=k;a[i].y/=k;
	}
	sort(a+1,a+m+1,cmp2);
	for(int i=1;i<=m;++i)
		printf("%lld/%lld\n",a[i].x,a[i].y);
}

int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
