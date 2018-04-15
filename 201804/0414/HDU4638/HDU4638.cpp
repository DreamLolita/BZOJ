#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int T,n,m,cnt;
int vis[N],pos[N],ans[N],a[N];

struct Tnode
{
	int l,r,id;
};
Tnode q[N];

struct Seqment
{
	int sum[N<<2];
	
	void pushup(int rt)
	{
		sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	}
	
	void build(int rt,int l,int r)
	{
		if(l==r)
		{
			sum[rt]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
	}
	
	void update(int rt,int l,int r,int p,int v)
	{
		if(l==r)
		{
			sum[rt]+=v;
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			update(rt<<1,l,mid,p,v);
		else
			update(rt<<1|1,mid+1,r,p,v);
		pushup(rt);
	}
	
	int query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return sum[rt];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid)
			ret+=query(rt<<1,l,mid,L,R);
		if(R>mid)
			ret+=query(rt<<1|1,mid+1,r,L,R);
		return ret;
	}
}tr;

bool cmp(Tnode A,Tnode B)
{
	return A.r<B.r;
}

int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			pos[a[i]]=i;
		}
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d",&q[i].l,&q[i].r);
			q[i].id=i;
		}
		sort(q+1,q+m+1,cmp);
		tr.build(1,1,n);cnt=1;
		for(int i=1;i<=n && cnt<=m;++i)
		{
			tr.update(1,1,n,i,1);vis[a[i]]=1;
			if(vis[a[i]-1])
				tr.update(1,1,n,pos[a[i]-1],-1);
			if(vis[a[i]+1])
				tr.update(1,1,n,pos[a[i]+1],-1);
			while(q[cnt].r==i && cnt<=m)
			{
				ans[q[cnt].id]=tr.query(1,1,n,q[cnt].l,q[cnt].r);
				++cnt;
			}
		}
		for(int i=1;i<=m;++i)
			printf("%d\n",ans[i]);
	}
	
	return 0;
}
