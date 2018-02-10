#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=4e6+10;
int n,seg,siz=1;
LL ans,cnt1,cnt2;
int v[N],l[N],r[N],root[N];
int sum[N],ls[N],rs[N];

void init(int x)
{
	scanf("%d",&v[x]);
	if(!v[x])
	{
		l[x]=++siz;
		init(l[x]);
		r[x]=++siz;
		init(r[x]);
	}
}

void pushup(int x)
{
	sum[x]=sum[ls[x]]+sum[rs[x]];
}

void build(int &rt,int l,int r,int val)
{
	if(!rt)
		rt=++seg;
	if(l==r)
	{
		sum[rt]=1;
		return;
	}
	int mid=(l+r)>>1;
	if(val<=mid)
		build(ls[rt],l,mid,val);
	else
		build(rs[rt],mid+1,r,val);
	pushup(rt);
}

int merge(int x,int y)
{
	if(!x || !y)
		return x+y;
	cnt1+=1ll*sum[rs[x]]*sum[ls[y]];
	cnt2+=1ll*sum[ls[x]]*sum[rs[y]];
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	pushup(x);
	return x;
}

void solve(int x)
{
	if(!x)
		return;
	solve(l[x]);solve(r[x]);
	if(!v[x])
	{
		cnt1=cnt2=0;
		root[x]=merge(root[l[x]],root[r[x]]);
		ans+=min(cnt1,cnt2);
	}
}

int main()
{
	freopen("BZOJ3702.in","r",stdin);
	freopen("BZOJ3702.out","w",stdout);
	
	scanf("%d",&n);
	init(1);
	for(int i=1;i<=siz;i++)
		if(v[i])
			build(root[i],1,n,v[i]);
	solve(1);
	printf("%lld\n",ans);
	
	return 0;
}
