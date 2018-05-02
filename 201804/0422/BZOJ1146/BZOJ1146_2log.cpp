#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

const int N=1e5+10;
const int M=N*130;
int n,m,Q,ind,tot,lf,rf,lca;
int root[N],a[N],dfn[N],siz[N],son[N];
int dep[N],pos[N],head[N],bit[N],L[N],R[N];
int fa[18][N],mp[N<<1];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<3)+(ret<<1)+(c-'0');c=getchar();}
	return ret*f;
}

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

struct Tquery
{
	int x,y,k;
};
Tquery q[N];

struct Seqment
{
	int sz;
	int ls[M],rs[M],w[M];
	
	void insert(int &k,int x,int l,int r,int p,int val)
	{
		k=++sz;w[k]=w[x]+val;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		ls[k]=ls[x];rs[k]=rs[x];
		if(p<=mid)
			insert(ls[k],ls[x],l,mid,p,val);
		else
			insert(rs[k],rs[x],mid+1,r,p,val);
	}
	
	void build(int x)
	{
		insert(root[x],root[fa[0][x]],1,m,a[x],1);
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v==fa[0][x])
				continue;
			build(v);
		}
	}
	
	void modify(int x,int p,int val)
	{
		for(;x<=n;x+=lowbit(x))
			insert(bit[x],bit[x],1,m,p,val);
	}
	
	int check()
	{
		int ret=0;
		for(int i=1;i<=lf;++i)
			ret-=w[L[i]];
		for(int i=1;i<=rf;++i)
			ret+=w[R[i]];
		return ret;
	}
	
	void getans(int rk)
	{
		int l=1,r=m;
		while(l<r)
		{
			int mid=(l+r)>>1,sum=0;
			for(int i=1;i<=lf;++i)
				sum-=w[rs[L[i]]];
			for(int i=1;i<=rf;++i)
				sum+=w[rs[R[i]]];
			if(sum>=rk)
			{
				for(int i=1;i<=lf;++i)
					L[i]=rs[L[i]];
				for(int i=1;i<=rf;++i)
					R[i]=rs[R[i]];
				l=mid+1;
			}
			else
			{
				for(int i=1;i<=lf;++i)
					L[i]=ls[L[i]];
				for(int i=1;i<=rf;++i)
					R[i]=ls[R[i]];
				rk-=sum;r=mid;
			}
		}
		printf("%d\n",mp[l]);
	}
}tr;

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<18;++i)
		if(t&(1<<i))
			x=fa[i][x];
	for(int i=17;~i;--i)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return x==y?x:fa[0][x];
}

void query(int x,int y,int rk)
{
	lf=rf=0;lca=LCA(x,y);
	L[++lf]=root[lca];L[++lf]=root[fa[0][lca]];
	R[++rf]=root[x];R[++rf]=root[y];
	for(int i=dfn[x];i;i-=lowbit(i))
		R[++rf]=bit[i];
	for(int i=dfn[y];i;i-=lowbit(i))
		R[++rf]=bit[i];
	for(int i=dfn[lca];i;i-=lowbit(i))
		L[++lf]=bit[i];
	for(int i=dfn[fa[0][lca]];i;i-=lowbit(i))
		L[++lf]=bit[i];
	if(tr.check()<rk)
	{
		puts("invalid request!");
		return;
	}
	tr.getans(rk);
}

void dfs(int x,int f)
{
	siz[x]=1;dfn[x]=++ind;pos[ind]=x;
	fa[0][x]=f;dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		dfs(v,x);siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])
			son[x]=v;
	}
}

void get_fa()
{
	for(int i=1;i<18;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
}

void init()
{
	n=read();Q=read();
	for(int i=1;i<=n;++i)
		a[i]=mp[++m]=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	for(int i=1;i<=Q;++i)
	{
		q[i].k=read();q[i].x=read();q[i].y=read();
		if(!q[i].k)
			mp[++m]=q[i].y;
	}
	dfs(1,0);
	get_fa();
	sort(mp+1,mp+m+1);
	int tmp=unique(mp+0,mp+m+1)-mp-1;
	m=tmp;
	for(int i=1;i<=n;++i)
		a[i]=lower_bound(mp+1,mp+m+1,a[i])-mp;
	tr.build(1);
}

void solve()
{
	for(int i=1;i<=Q;++i)
	{
		if(q[i].k)
			query(q[i].x,q[i].y,q[i].k);
		else
		{
			int u=q[i].x,v=q[i].y;
			tr.modify(dfn[u],a[u],-1);tr.modify(dfn[u]+siz[u],a[u],1);
			a[u]=lower_bound(mp+0,mp+m+1,v)-mp;
			tr.modify(dfn[u],a[u],1);tr.modify(dfn[u]+siz[u],a[u],-1);
		}
	}
}

int main()
{
	freopen("BZOJ1146.in","r",stdin);
	freopen("BZOJ1146.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
