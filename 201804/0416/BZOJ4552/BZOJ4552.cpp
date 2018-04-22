#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=N*8;
int n,m,pos,ans;
int a[N];

struct Tquery
{
	int opt,l,r;
};
Tquery q[N];

struct Seqment
{
	int sum[M],tar[M],mk[M];
	
	void pushup(int rt)
	{
		sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	}
	
	void pushdown(int rt,int l,int r)
	{
		int mid=(l+r)>>1;
		if(mk[rt])
		{
			sum[rt<<1]=(tar[rt]?0:mid-l+1);tar[rt<<1]=tar[rt];mk[rt<<1]=1;
			sum[rt<<1|1]=(tar[rt]?0:r-mid);tar[rt<<1|1]=tar[rt];mk[rt<<1|1]=1;
			mk[rt]=0;
		}
	}
	
	void update(int rt,int l,int r,int L,int R,int v)
	{
		if(L>R)
			return;
		if(L<=l && r<=R)
		{
			sum[rt]=(v?0:r-l+1);tar[rt]=v;
			mk[rt]=1;
			return;
		}
		pushdown(rt,l,r);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(rt<<1,l,mid,L,R,v);
		if(R>mid)
			update(rt<<1|1,mid+1,r,L,R,v);
		pushup(rt);
	}
	
	int query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return sum[rt];
		pushdown(rt,l,r);
		int mid=(l+r)>>1,ret=0;
		if(L<=mid)
			ret+=query(rt<<1,l,mid,L,R);
		if(R>mid)
			ret+=query(rt<<1|1,mid+1,r,L,R);
		return ret;
	}
	
	bool check(int x)
	{
		for(int i=1;i<=n;++i)
			if(a[i]<x)
				update(1,1,n,i,i,0);
			else
				update(1,1,n,i,i,1);
		for(int i=1;i<=m;++i)
		{
			int t=query(1,1,n,q[i].l,q[i].r);
			if(q[i].opt)
			{
				update(1,1,n,q[i].l,q[i].r-t,1);
				update(1,1,n,q[i].r-t+1,q[i].r,0);
			}
			else
			{
				update(1,1,n,q[i].l,q[i].l+t-1,0);
				update(1,1,n,q[i].l+t,q[i].r,1);
			}
		}
		return !query(1,1,n,pos,pos);
	}
};
Seqment tr;

int main()
{
	freopen("BZOJ4552.in","r",stdin);
	freopen("BZOJ4552.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;++i)
		scanf("%d%d%d",&q[i].opt,&q[i].l,&q[i].r);
	scanf("%d",&pos);
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(tr.check(mid))
			ans=mid,l=mid+1;
		else
			r=mid-1;	
	}	
	printf("%d\n",ans);
		
	return 0;
}
