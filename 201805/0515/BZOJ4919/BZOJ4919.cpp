#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=2e5+10;
const int M=N*64;
int n,m,tot,ans;
int head[N];
int rt[N],v[N],p[N],val[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

struct Segment
{
	int sz;
	int ls[M],rs[M],sum[M],tar[M];
	
	void pushdown(int x)
	{
		int l=ls[x],r=rs[x];
		if(l)
			sum[l]+=sum[x],tar[l]=max(tar[l]+sum[x],tar[x]);
		if(r)
			sum[r]+=sum[x],tar[r]=max(tar[r]+sum[x],tar[x]);
		sum[x]=0;
	}
	
	int merge(int x,int y)
	{
		if(!x || !y)
			return x+y;
		pushdown(x);pushdown(y);
		
		if(!ls[x])	
			ls[x]=ls[y],tar[ls[x]]+=tar[x],sum[ls[x]]+=tar[x]+sum[x];
		else
		if(!ls[y])
			tar[ls[x]]+=tar[y],sum[ls[x]]+=tar[y]+sum[y];
		else
			ls[x]=merge(ls[x],ls[y]);
			
		if(!rs[x])	
			rs[x]=rs[y],tar[rs[x]]+=tar[x],sum[rs[x]]+=tar[x]+sum[x];
		else
		if(!rs[y])
			tar[rs[x]]+=tar[y],sum[rs[x]]+=tar[y]+sum[y];
		else
			rs[x]=merge(rs[x],rs[y]);	
			
		tar[x]+=tar[y];	
		return x;
	}
	
	void update(int &x,int l,int r,int L,int R,int c)
	{
		if(!x)
			x=++sz;
		if(L<=l && r<=R)
		{
			tar[x]=max(tar[x],c);
			return;
		}
		pushdown(x);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(ls[x],l,mid,L,R,c);
		if(R>mid)
			update(rs[x],mid+1,r,L,R,c);
	}
	
	int query(int x,int l,int r,int p)
	{
		if(!x || !p)
			return 0;
		if(l==r)
			return tar[x];
		pushdown(x);
		int mid=(l+r)>>1;
		if(p<=mid)
			return max(tar[x],query(ls[x],l,mid,p));
		return max(tar[x],query(rs[x],mid+1,r,p));
	}
	
	void findans(int x)
	{
		ans=max(ans,tar[x]);
		pushdown(x);
		if(ls[x])
			findans(ls[x]);
		if(rs[x])
			findans(rs[x]);
	}
}tr;

void dfs(int x)
{
	for(int i=head[x];i;i=e[i].nex)
	{
		int vs=e[i].v;
		dfs(vs);
		rt[x]=tr.merge(rt[x],rt[vs]);
	}
	tr.update(rt[x],1,m,v[x],m,tr.query(rt[x],1,m,v[x]-1)+1);
}

bool cmp(int x,int y)
{
	return val[x]<val[y];
}

int main()
{
	freopen("BZOJ4919.in","r",stdin);
	freopen("BZOJ4919.out","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)
	{
		val[i]=read();p[i]=i;
		int x=read();
		if(i^1)
			add(x,i);
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		if(i==1 || val[p[i]]>val[p[i-1]])
			++m;
		v[p[i]]=m;
	}
	dfs(1);tr.findans(rt[1]);
	printf("%d\n",ans);
	

	return 0;
}

