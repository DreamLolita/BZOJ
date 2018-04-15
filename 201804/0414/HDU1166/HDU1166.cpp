#include<bits/stdc++.h>
using namespace std;

const int N=5e4+10;
const int M=N*4;
int T,n;
int a[N],sum[M];

void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r)
{
	if(l==r)
	{
		sum[rt]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
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

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	
	scanf("%d",&T);
	for(int cas=1;cas<=T;++cas)
	{
		printf("Case %d:\n",cas);
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		build(1,1,n);
		while(true)
		{
			char opt[6];int l,r;
			scanf("%s",opt);
			if(opt[0]=='E')
				break;
			scanf("%d%d",&l,&r);
			if(opt[0]=='A')
				update(1,1,n,l,r);
			else
			if(opt[0]=='S')
				update(1,1,n,l,-r);
			else
				printf("%d\n",query(1,1,n,l,r));
		}
	}
	
	return 0;
}
