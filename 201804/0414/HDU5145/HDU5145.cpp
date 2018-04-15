#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e4+10;
const int mod=1e9+7;
int T,n,m,lim;
int a[N],cnt[N],pos[N];
LL ans,inv[N];

struct Tnode
{
	int l,r,id;
	LL ans;
};
Tnode q[N];

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

LL qpow(LL x,LL y)
{
	LL ret=1;
	for(;y;y>>=1,x=x*x%mod)
		if(y&1)
			ret=ret*x%mod;
	return ret;
}

void get_inv()
{
	for(int i=1;i<N;++i)
		inv[i]=qpow(i,mod-2);
}

void init()
{
	scanf("%d%d",&n,&m);lim=(int)sqrt(n);
	for(int i=1;i<=n;++i)
		pos[i]=(i-1)/lim+1;
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
}

void update1(int x,int y)
{
	++cnt[a[x]];
	ans=ans*(abs(x-y)+1)%mod*inv[cnt[a[x]]]%mod;
}

void update2(int x,int y)
{
	ans=ans*cnt[a[x]]%mod*inv[abs(x-y)+1]%mod;
	--cnt[a[x]];
}

void solve()
{
	sort(q+1,q+m+1,cmp1);
	int l=1,r=0;ans=1;memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=m;++i)
	{
		for(;r<q[i].r;++r)	update1(r+1,l);
		for(;r>q[i].r;--r)	update2(r,l);
		for(;l<q[i].l;++l)	update2(l,r);
		for(;l>q[i].l;--l)	update1(l-1,r);
		q[i].ans=ans;
	}
	sort(q+1,q+m+1,cmp2);
	for(int i=1;i<=m;++i)
		printf("%I64d\n",q[i].ans);
}

int main()
{
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	
	get_inv();
	scanf("%d",&T);
	while(T--)
	{
		init();
		solve();
	}
	
	return 0;
}
