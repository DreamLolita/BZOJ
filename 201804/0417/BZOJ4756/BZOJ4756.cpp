#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=N<<5;
int n,sum,tot,cnt;
int p[N],a[N],root[N],head[N],ans[N];

int read()
{
	int ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3)+(ret<<1)+(ch-'0');ch=getchar();}
	return ret*f;
}

struct Seqment
{
	int siz;
	int ls[M],rs[M],sum[M];
	
	void pushup(int rt)
	{
		sum[rt]=sum[ls[rt]]+sum[rs[rt]];
	}
	
	int merge(int x,int y)
	{
		if(!x || !y)
			return x+y;
		ls[x]=merge(ls[x],ls[y]);
		rs[x]=merge(rs[x],rs[y]);
		pushup(x);
		return x;
	}
	
	void insert(int &rt,int l,int r,int p)
	{
		rt=++siz;
		if(l==r)
		{
			sum[rt]=1;
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			insert(ls[rt],l,mid,p);
		else
			insert(rs[rt],mid+1,r,p);
		pushup(rt);
	}
	
	int query(int rt,int l,int r,int L,int R)
	{
//cerr<<rt<<" "<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
		if(!rt)
			return 0;
		if(L<=l && r<=R)
			return sum[rt];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid)
			ret+=query(ls[rt],l,mid,L,R);
		if(R>mid)
			ret+=query(rs[rt],mid+1,r,L,R);
		return ret;
	}
}tr;

struct Tway
{
	int v,nex;
};
Tway e[N];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

void init()
{
	n=read();
	for(int i=1;i<=n;++i)
		p[i]=read(),a[i]=p[i];
	sort(a+1,a+n+1);
	cnt=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;++i)	
		p[i]=lower_bound(a+1,a+cnt+1,p[i])-a;
	for(int i=2;i<=n;++i)
	{
		int u=read();
		add(u,i);
	}
}

void dfs(int x)
{
//cerr<<x<<endl;
	for(int i=head[x];i;i=e[i].nex)
	{
		dfs(e[i].v);
		root[x]=tr.merge(root[x],root[e[i].v]);
	}
	ans[x]=tr.query(root[x],1,n,p[x]+1,cnt);
}

void solve()
{
	for(int i=1;i<=n;++i)
		tr.insert(root[i],1,n,p[i]);
	dfs(1);
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
}

int main()
{
	freopen("BZOJ4756.in","r",stdin);
	freopen("BZOJ4756.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
