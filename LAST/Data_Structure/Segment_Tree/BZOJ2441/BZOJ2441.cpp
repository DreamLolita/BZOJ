#include<bits/stdc++.h>
using namespace std;

const int INF=2e9;
const int mod=1e9+7;
const int MAXN=2e5+10;
typedef long long LL;
int n,tot,b[MAXN];
LL f[MAXN][2],c[MAXN],ans;

struct Tree
{
	int l,r,len;
	LL tar,sum;
};
Tree tr[MAXN<<2];

struct Tdata
{
	int x,xx,y,id;
};
Tdata a[MAXN];

bool cmp(Tdata A,Tdata B)
{
	return A.x<B.x;
}

bool cmp2(Tdata A,Tdata B)
{
	return A.y<B.y;
}

void debug(int rt,int l,int r)
{
	if(l==r)
		return;
	printf("%d %d %I64d %I64d\n",l,r,tr[rt].sum,tr[rt].tar);
	int mid=(l+r)>>1;
	debug(rt<<1,l,mid);
	debug(rt<<1|1,mid+1,r);
}

void pushup(int rt)
{
	if(tr[rt].l==tr[rt].r)
		return;
	tr[rt].sum=0;
	tr[rt].len=tr[rt<<1].len+tr[rt<<1|1].len;
	if(tr[rt<<1].len)
		tr[rt].sum=(tr[rt].sum+tr[rt<<1].sum)%mod;
	if(tr[rt<<1|1].len)
		tr[rt].sum=(tr[rt].sum+tr[rt<<1|1].sum)%mod;
}

void pushdown(int rt)
{
	if(tr[rt].l==tr[rt].r || !tr[rt].tar)
		return;
	int p=tr[rt].tar;
	tr[rt<<1].tar=(tr[rt<<1].tar+p)%mod;
	tr[rt<<1|1].tar=(tr[rt<<1|1].tar+p)%mod;
	tr[rt<<1].sum=(tr[rt<<1].sum+1ll*p*tr[rt<<1].len)%mod;
	tr[rt<<1|1].sum=(tr[rt<<1|1].sum+1ll*p*tr[rt<<1|1].len)%mod;
	tr[rt].tar=0;
}

LL query(int rt,int l,int r,int L,int R)
{
//	printf("%d %d %I64d\n",l,r,tr[rt].sum);
	if(tr[rt].len==0 || L>R)
		return 0;
	pushdown(rt);
	if(L<=l && r<=R)
		return tr[rt].sum;
	
	int mid=(l+r)>>1;
	LL ret=0;
	if(R<=mid)
		return query(rt<<1,l,mid,L,R);
	else
	if(L>mid)
		return query(rt<<1|1,mid+1,r,L,R);
	else
		return (query(rt<<1,l,mid,L,mid)+query(rt<<1|1,mid+1,r,mid+1,R))%mod;
/*	if(L<=mid)
		ret+=query(rt<<1,l,mid,L,R);
	if(R>mid)
		ret+=query(rt<<1|1,mid+1,r,L,R);*/
	return ret;
}

void update(int rt,int l,int r,int p,LL v)
{
//	printf("%d %d %d %I64d\n",l,r,p,v);
	if(l==r)
	{
		tr[rt].len=1;
		tr[rt].sum=(tr[rt].tar+v)%mod;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;;
	if(p<=mid)
		update(rt<<1,l,mid,p,v);
	else
		update(rt<<1|1,mid+1,r,p,v);
	pushup(rt);
}

void update2(int rt,int l,int r,int L,int R,LL v)
{
//	printf("%d %d %d %d %I64d\n",l,r,L,R,v);
	if(L>R)
		return;
	if(L<=l && r<=R)
	{
		tr[rt].tar=(tr[rt].tar+v)%mod;
		tr[rt].sum=(tr[rt].sum+1ll*tr[rt].len*v)%mod;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(R<=mid)
		update2(rt<<1,l,mid,L,R,v);
	else
	if(L>mid)
		update2(rt<<1|1,mid+1,r,L,R,v);
	else
		update2(rt<<1,l,mid,L,mid,v),update2(rt<<1|1,mid+1,r,mid+1,R,v);
/*	if(L<=mid)
		update2(rt<<1,l,mid,L,R,v);
	if(R>mid)
		update2(rt<<1|1,mid+1,r,L,R,v);*/
	pushup(rt);
}

void build(int rt,int l,int r)
{
	tr[rt].l=l;tr[rt].r=r;
	tr[rt].sum=tr[rt].tar=tr[rt].len=0;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
}

void solve()
{
	build(1,1,n);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;++i)
	{
		int j=i;
		while(j<n && a[i].y==a[j+1].y)
			++j;
		for(int k=i;k<=j;++k)
			update2(1,1,n,a[k].xx,n,-1);
//		printf("debug:\n");
//		debug(1,1,n);
		for(int k=i;k<=j;++k)
			f[a[k].id][0]=query(1,1,n,1,a[k].x-1);
	
		for(int k=i;k<=j;++k)
			update(1,1,n,a[k].id,a[k].x-1);
		i=j;
	}
}

void solve2()
{
	build(1,1,n);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;++i)
	{
		int j=i;
		while(j<n && a[i].y==a[j+1].y)
			++j;
		for(int k=i;k<=j;++k)
			update2(1,1,n,1,a[k].x-1,-1);
		for(int k=i;k<=j;++k)
			f[a[k].id][1]=query(1,1,n,a[k].xx,n);
		
		for(int k=i;k<=j;++k)
			update(1,1,n,a[k].id,n-a[k].xx+1);
		i=j;
	}
}

int main()
{
//	freopen("BZOJ2441.in","r",stdin);
//	freopen("BZOJ2441.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		b[++tot]=a[i].x;
	}
	b[++tot]=INF;
	sort(b+1,b+1+tot);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		a[i].xx=upper_bound(b+1,b+tot+1,a[i].x)-b;
		a[i].x=lower_bound(b+1,b+tot+1,a[i].x)-b;
		a[i].id=i;
//		printf("%d %d %d\n",a[i].x,a[i].xx,a[i].id);
	}
	solve();
	solve2();
	for(int i=1;i<=n;++i)
	{
		ans=(ans+f[i][0]*f[i][1])%mod;
//		printf("%I64d %I64d\n",f[i][0],f[i][1]);
	}
	printf("%lld\n",ans);
	
	return 0;
}
