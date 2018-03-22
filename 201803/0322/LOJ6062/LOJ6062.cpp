#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10;
const int INF=2e9;
int n,m,h,ans;
int a[N],b[N];

struct Tree
{
	int mi[N<<1],tar[N<<1];
	
	void pushup(int x)
	{
		mi[x]=min(mi[x<<1],mi[x<<1|1]);
	}
	
	void pushdown(int x)
	{
		if(tar[x])
		{
			mi[x<<1]+=tar[x];mi[x<<1|1]+=tar[x];
			tar[x<<1]+=tar[x];tar[x<<1|1]+=tar[x];
			tar[x]=0;
		}
	}
	
	void build(int rt,int l,int r)
	{
		if(l==r)
		{
			mi[rt]=-l;
			return;	
		}	
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	
	void update(int rt,int l,int r,int L,int R,int v)
	{
		if(L<=l && r<=R)
		{
			mi[rt]+=v;tar[rt]+=v;
			return;	
		}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(rt<<1,l,mid,L,R,v);
		if(R>mid)
			update(rt<<1|1,mid+1,r,L,R,v);
		pushup(rt);
	}
};
Tree tr;

int findpos(int x)
{
	int l=1,r=m,ret=m+1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(b[mid]<x)
			l=mid+1;
		else
			r=mid-1,ret=mid;
	}
	return ret;
}

int main()
{
	freopen("LOJ6062.in","r",stdin);
	freopen("LOJ6062.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&h);
	for(int i=1;i<=m;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(b+1,b+m+1);
	tr.build(1,1,m);
	for(int i=1;i<m;++i)
	{
		int x=findpos(h-a[i]);
		if(x<=m)
			tr.update(1,1,m,x,m,1);
	}
	for(int i=m;i<=n;++i)
	{
		int x=findpos(h-a[i]);
		if(x<=m)
			tr.update(1,1,m,x,m,1);
		if(tr.mi[1]>=0)
			++ans;
		x=findpos(h-a[i-m+1]);
		if(x<=m)
			tr.update(1,1,m,x,m,-1);
	}
	printf("%d\n",ans);

	return 0;
}
