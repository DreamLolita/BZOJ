#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
const int M=1e7+5;
int n,m,ans,siz,tot;
int ls[M],rs[M],s[M];
int a[N],sa[N],root[N];

void update(int l,int r,int x,int &y,int p)
{
	y=++siz;s[y]=s[x]+1;
	if(l==r)
		return;
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if(p<=mid)
		update(l,mid,ls[x],ls[y],p);
	else
		update(mid+1,r,rs[x],rs[y],p);
}

int query(int l,int r,int x,int y,int k)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(s[ls[y]]-s[ls[x]]>=k)
		return query(l,mid,ls[x],ls[y],k);
	else
	if(s[rs[y]]-s[rs[x]]>=k)
		return query(mid+1,r,rs[x],rs[y],k);
	return 0;
}

int main()
{
	freopen("BZOJ3524.in","r",stdin);
	freopen("BZOJ3524.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		sa[i]=a[i];
	}
	sort(sa+1,sa+n+1);
	tot=unique(sa+1,sa+n+1)-sa-1;
	for(int i=1;i<=n;++i)
	{
		int t=lower_bound(sa+1,sa+tot+1,a[i])-sa;
		update(1,tot,root[i-1],root[i],t);
	}
	while(m--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		ans=query(1,tot,root[l-1],root[r],(r-l+1)/2+1);
		printf("%d\n",sa[ans]);
	}
	
	return 0;
}
