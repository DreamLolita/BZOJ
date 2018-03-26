#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=2e4+10;
const int M=N<<2;
int n,m,ans;
int f[N],c[N],s[N],d[N],w[N],ed[N],st[N];
vector<int>mp[N];

struct Segment_Tree
{
	int tar[M],mi[M];

	void pushdown(int x)
	{
		if(tar[x])
		{
			tar[x<<1]+=tar[x];tar[x<<1|1]+=tar[x];
			mi[x<<1]+=tar[x];mi[x<<1|1]+=tar[x];
			tar[x]=0;
		}
	}
	
	void pushup(int x)
	{
		mi[x]=min(mi[x<<1],mi[x<<1|1]);
	}
	
	void build(int x,int l,int r)
	{
		tar[x]=0;
		if(l==r)
		{
			mi[x]=f[l];
			return;
		}
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pushup(x);
	}
	
	void update(int x,int l,int r,int L,int R,int del)
	{
		if(L>R)
			return;
		if(L<=l && r<=R)
		{
			tar[x]+=del;mi[x]+=del;
			return;
		}
		pushdown(x);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(x<<1,l,mid,L,R,del);
		if(R>mid)
			update(x<<1|1,mid+1,r,L,R,del);
		pushup(x);
	}
	
	int query(int x,int l,int r,int L,int R)
	{
		if(L>R)
			return INF;
		if(L<=l && r<=R)
			return mi[x];
		pushdown(x);
		int mid=(l+r)>>1,ret=INF;
		if(L<=mid)
			ret=min(ret,query(x<<1,l,mid,L,R));
		if(R>mid)
			ret=min(ret,query(x<<1|1,mid+1,r,L,R));
		return ret;
	}
}tr;

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;++i)
		scanf("%d",&d[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&s[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&w[i]);
	d[++n]=INF;w[n]=INF;++m;
	for(int i=1;i<=n;++i)
	{
		st[i]=lower_bound(d+1,d+n+1,d[i]-s[i])-d;
		ed[i]=lower_bound(d+1,d+n+1,d[i]+s[i])-d;
		if(d[ed[i]]>d[i]+s[i])
			--ed[i];
		mp[ed[i]].push_back(i);
	}
}

void solve()
{
	ans=INF;
	for(int i=1;i<=m;++i)
	{
		if(i==1)
		{
			int t=0;
			for(int j=1;j<=n;++j)
			{
				f[j]=t+c[j];
				for(int k=0;k<mp[j].size();++k)
				{
					int x=mp[j][k];
					t+=w[x];
				}
			}
			ans=f[n];
		}
		else
		{
			tr.build(1,1,n);
			for(int j=1;j<=n;++j)
			{
				f[j]=tr.query(1,1,n,1,j-1)+c[j];
				for(int k=0;k<mp[j].size();++k)
				{
					int x=mp[j][k];
					tr.update(1,1,n,1,st[x]-1,w[x]);
				}
			}
			ans=min(ans,f[n]);
		}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ1835.in","r",stdin);
	freopen("BZOJ1835.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
