#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const int M=N*30;
int n,m,ed,ans,mx;
int a[N];

struct Tree
{
	int rt[M],ls[M],rs[M],v[M];

	int build(int x,int l,int r,int p)
	{
		int mid=(l+r)>>1,now=++ed;
		ls[now]=ls[x];rs[now]=rs[x];v[now]=v[x]+1;
		if(l^r)
		{	
			if(p<=mid)
				ls[now]=build(ls[x],l,mid,p);
			else
				rs[now]=build(rs[x],mid+1,r,p);
		}
		return now;
	}
	
	int query(int i,int j,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return v[j]-v[i];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid)
			ret+=query(ls[i],ls[j],l,mid,L,R);
		if(R>mid)
			ret+=query(rs[i],rs[j],mid+1,r,L,R);
		return ret;
	}
	
	bool ask(int i,int j,int l,int r)
	{
		int L=max(l,0),R=min(r,mx);
		if(L>R)
			return 0;
		int sum=query(rt[i-1],rt[j],0,mx,L,R);
		return sum!=0;
	}
};
Tree tr;

int main()
{
	freopen("BZOJ4571.in","r",stdin);
	freopen("BZOJ4571.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),mx=max(mx,a[i]);
	for(int i=1;i<=n;++i)
		tr.rt[i]=tr.build(tr.rt[i-1],0,mx,a[i]);
	for(int i=1;i<=m;++i)
	{
		int u,v,l,r;ans=0;
		scanf("%d%d%d%d",&u,&v,&l,&r);
		for(int i=17;~i;--i)
		{
			int now=ans+((1^(u>>i&1))<<i);
			if(tr.ask(l,r,now-v,now+(1<<i)-v-1))
				ans=now;
			else
				ans+=(u>>i&1)<<i;
		}
		printf("%d\n",ans^u);
	}
	
	return 0;
}
