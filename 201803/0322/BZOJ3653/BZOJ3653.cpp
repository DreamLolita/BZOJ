#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e5+10;
int n,m,ind,tot;
int head[N],a[N],st[N],ed[N],rt[N];
int siz[N],dep[N];
LL ans;

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

struct Segment
{
	int cnt;
	int ls[N<<5],rs[N<<5];
	LL sum[N<<5];
	
	void cpy(int x)
	{
		++cnt;
		ls[cnt]=ls[x];rs[cnt]=rs[x];sum[cnt]=sum[x];
	}
	
	void update(int &x,int l,int r,int p,int w)
	{
		cpy(x);x=cnt;sum[x]+=w;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		if(p<=mid)
			update(ls[x],l,mid,p,w);
		else
			update(rs[x],mid+1,r,p,w);
	}
	
	LL query(int i,int j,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return sum[j]-sum[i];
		else
		{
			LL ret=0;
			int mid=(l+r)>>1;
			if(L<=mid)
				ret+=query(ls[i],ls[j],l,mid,L,R);
			if(R>mid)
				ret+=query(rs[i],rs[j],mid+1,r,L,R);
			return ret;
		}
	}
}tr;

void dfs(int x)
{
	st[x]=++ind;a[ind]=x;siz[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!st[v])
		{
			dep[v]=dep[x]+1;
			dfs(v);
			siz[x]+=siz[v];
		}
	}
	ed[x]=ind;
}

int main()
{
	freopen("BZOJ3653.in","r",stdin);
	freopen("BZOJ3653.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs(1);
	for(int i=1;i<=n;++i)
		rt[i]=rt[i-1],tr.update(rt[i],0,n,dep[a[i]],siz[a[i]]-1);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ans=1ll*(siz[x]-1)*min(dep[x],y);
		ans+=tr.query(rt[st[x]-1],rt[ed[x]],0,n,dep[x]+1,min(dep[x]+y,n));
		printf("%lld\n",ans);
	}
	
	return 0;
}
