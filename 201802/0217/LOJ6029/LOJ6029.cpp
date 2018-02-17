#include<bits/stdc++.h>
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;

typedef long long LL;
const LL INF=(LL)1e18;
const int N=1e5+10;
int n,q;
int a[N];

struct Tree
{
	LL mx,mi,sum,tar;
};
Tree tr[N<<2];

void pushup(int x)
{
	tr[x].sum=tr[ls].sum+tr[rs].sum;
	tr[x].mx=max(tr[ls].mx,tr[rs].mx);
	tr[x].mi=min(tr[ls].mi,tr[rs].mi);
}

void pushtar(int x,LL tag,int len)
{
	tr[x].mx+=tag;tr[x].mi+=tag;
	tr[x].sum+=1ll*tag*len;
	tr[x].tar+=tag;
}

void pushdown(int x,int l,int r)
{
	if(tr[x].tar==0)
		return;
	int mid=(l+r)>>1;
	pushtar(ls,tr[x].tar,mid-l+1);
	pushtar(rs,tr[x].tar,r-mid);
	tr[x].tar=0;
}

void build(int x,int l,int r)
{
	if(l==r)
	{
		tr[x].mx=tr[x].mi=tr[x].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(x);
}

void add(int x,int l,int r,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		pushtar(x,v,r-l+1);
		return;
	}
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		add(ls,l,mid,L,R,v);
	if(R>mid)
		add(rs,mid+1,r,L,R,v);
	pushup(x);
}

void divi(int x,int l,int r,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		LL A,B;
		if(tr[x].mi<0)	
			A=(tr[x].mi-v+1)/v;
		else	
			A=tr[x].mi/v;
		if(tr[x].mx<0)	
			B=(tr[x].mx-v+1)/v;
		else	
			B=tr[x].mx/v;
		if(tr[x].mi-A==tr[x].mx-B)
		{
			pushtar(x,A-tr[x].mi,r-l+1);
			return;
		}
	}
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		divi(ls,l,mid,L,R,v);
	if(R>mid)
		divi(rs,mid+1,r,L,R,v);
	pushup(x);
}

LL get_min(int x,int l,int r,int L,int R)
{
	if(L<=l && r<=R)
		return tr[x].mi;
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	LL ret=INF;
	if(L<=mid)
		ret=min(ret,get_min(ls,l,mid,L,R));
	if(R>mid)
		ret=min(ret,get_min(rs,mid+1,r,L,R));
	return ret;
}

LL get_sum(int x,int l,int r,int L,int R)
{
	if(L<=l && r<=R)
		return tr[x].sum;
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	LL ret=0;
	if(L<=mid)
		ret+=get_sum(ls,l,mid,L,R);
	if(R>mid)
		ret+=get_sum(rs,mid+1,r,L,R);
	return ret;
}

int main()
{
	freopen("LOJ6029.in","r",stdin);
	freopen("LOJ6029.out","w",stdout);
	
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	build(1,1,n);
	while(q--)
	{
		int opt,l,r,x;
		scanf("%d%d%d",&opt,&l,&r);++l;++r;
		if(opt==1)
		{
			scanf("%d",&x);
			add(1,1,n,l,r,x);
		}
		else
		if(opt==2)
		{
			scanf("%d",&x);
			divi(1,1,n,l,r,x);
		}
		else
		if(opt==3)
			printf("%lld\n",get_min(1,1,n,l,r));
		else
			printf("%lld\n",get_sum(1,1,n,l,r));
	}
	
	return 0;
}
