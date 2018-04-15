#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define sqr(x) ((LL)(x)*(LL)(x))
const int N=2e5+10;
int n,m;
int pos[N],col[N],sum[N*5];
LL ans;

struct Tnode
{
	int l,r,id;
	LL x,y,ans;
};
Tnode a[N];

inline bool cmp1(Tnode A,Tnode B)
{
	if(pos[A.l]^pos[B.l])
		return A.l<B.l;
	return A.r<B.r;
}

inline bool cmp2(Tnode A,Tnode B)
{
	return A.id<B.id;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	int lim=(int)sqrt(m);
	for(int i=1;i<=n;++i)
		pos[i]=(i-1)/lim+1;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id=i;
	}
}

inline void update(int x,int v)
{
	ans-=1ll*sqr(sum[col[x]])*col[x];
	sum[col[x]]+=v;
	ans+=1ll*sqr(sum[col[x]])*col[x];
}

inline void solve()
{
	sort(a+1,a+m+1,cmp1);
	
	int l=1,r=0;
	for(int i=1;i<=m;++i)
	{
		if(a[i].l==a[i].r)
		{
			a[i].ans=col[a[i].l];
			continue;
		}
		for(;l<a[i].l;++l)	update(l,-1);
		for(;l>a[i].l;--l)	update(l-1,1);
		for(;r<a[i].r;++r)	update(r+1,1);
		for(;r>a[i].r;--r)	update(r,-1);
		a[i].ans=ans;
	}
	sort(a+1,a+m+1,cmp2);
	for(int i=1;i<=m;++i)
		printf("%I64d\n",a[i].ans);
}

int main()
{
//	freopen("E.in","r",stdin);
//	freopen("E.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
