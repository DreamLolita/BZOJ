#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int INF=2100000000;
const int MAXN=30010;
int fa[MAXN],siz[MAXN],dep[MAXN];
int son[MAXN],top[MAXN],w[MAXN],val[MAXN];
int node,n,m,ans;
vector<int> way[MAXN];

struct Tcount
{
	int qmax,qsum;
};
Tcount tree[MAXN*4];

void readin()
{
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		way[a].push_back(b);
		way[b].push_back(a);
	}
}

void _reset()
{
	memset(w,0,sizeof(w));
	memset(fa,0,sizeof(fa));
	memset(son,0,sizeof(son));
	memset(top,0,sizeof(top));
	memset(siz,0,sizeof(siz));
	memset(dep,0,sizeof(dep));
	memset(val,0,sizeof(val));
}

void dfs1(int u,int f)
{
	fa[u]=f;siz[u]=1;
	dep[u]=dep[f]+1;
	for(int i=0;i<way[u].size();++i)
	{
		int v=way[u][i];
		if(v==f)
			continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
}

void dfs2(int u,int tp)
{
	w[u]=++node;
	top[u]=tp;
	if(son[u])
		dfs2(son[u],tp);
	for(int i=0;i<way[u].size();++i)
	{
		int v=way[u][i];
		if(v!=fa[u] && v!=son[u])
			dfs2(v,v);
	}
}

void pushup(int i)
{
	tree[i].qmax=max(tree[i*2].qmax,tree[i*2+1].qmax);
	tree[i].qsum=tree[i*2].qsum+tree[i*2+1].qsum;
}

void update(int u,int nl,int nr,int i,int del)
{
	if(nl==nr && nl==u)
	{
		tree[i].qsum=tree[i].qmax=del;
		return;
	}
	int mid=(nl+nr)/2;
	if(u<=mid)
		update(u,nl,mid,i*2,del);
	else
		update(u,mid+1,nr,i*2+1,del);
	pushup(i);
}

void build(int nl,int nr,int i)
{
//printf("i:%d l:%d r:%d\n",i,nl,nr);
	tree[i].qsum=tree[i].qmax=0;
	if(nl==nr)
		return;
	int mid=(nl+nr)>>1;
	build(nl,mid,i*2);
	build(mid+1,nr,i*2+1);
}

void query_sum(int l,int r,int nl,int nr,int i)
{
	if(l<=nl && nr<=r)
	{
		ans+=tree[i].qsum;
		return;
	}
	int mid=(nl+nr)>>1;
	if(l<=mid)
		query_sum(l,r,nl,mid,i*2);
	if(r>mid)
		query_sum(l,r,mid+1,nr,i*2+1);
}

void get_sum(int u,int v)
{
	ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);//v.top deeper
		query_sum(w[top[v]],w[v],1,n,1);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	query_sum(w[u],w[v],1,n,1);
	printf("%d\n",ans);
}

void query_max(int l,int r,int nl,int nr,int i)
{
	if(l<=nl && nr<=r)
	{
		ans=max(ans,tree[i].qmax);
		return;
	}
	int mid=(nl+nr)>>1;
	if(l<=mid)
		query_max(l,r,nl,mid,i*2);
	if(r>mid)
		query_max(l,r,mid+1,nr,i*2+1);
}

void get_max(int u,int v)
{
	ans=-INF;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);//v.top deeper
		query_max(w[top[v]],w[v],1,n,1);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	query_max(w[u],w[v],1,n,1);
	printf("%d\n",ans);
}

void debug()
{
	printf("debug:\n");
	for(int i=1;i<=n;++i)
		printf("%d--- w:%d top:%d son:%d\n",i,w[i],top[w[i]],son[w[i]]);
	printf("\n");
/*	for(int i=1;i<=n;++i)
	{
		get_max(i,i);
		get_sum(i,i);
		printf("\n");
	}*/
	get_max(2,2);
	
	for(int i=1;i<=20;++i)
		printf("%d ",tree[i].qmax);
	printf("\n");
	for(int i=1;i<=20;++i)
		printf("%d ",tree[i].qsum);
	printf("\n\n");
}

void solve()
{
	_reset();
	readin();
	dfs1(1,1);
	dfs2(1,1);
	
	build(1,n,1);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&val[w[i]]);
		update(w[i],1,n,1,val[w[i]]);
	}
//debug();
	
	scanf("%d",&m);
	for(int i=0;i<m;++i)
	{
		char st[10];
		int a,b;

		getchar();
		scanf("%s%d%d",st,&a,&b);
		if(st[1]=='H')
			update(w[a],1,n,1,b);
		else
		if(st[1]=='S')
			get_sum(a,b);
		else
			get_max(a,b);
	}

}

int main()
{
//	freopen("BZOJ1036.in","r",stdin);
//	freopen("BZOJ1036.out","w",stdout);
	
	solve();
	
	return 0;
}
