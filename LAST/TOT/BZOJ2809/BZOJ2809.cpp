#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=1e5+10;
LL ans;
int n,m,cnt,tot;
int head[MAXN],c[MAXN],l[MAXN];
int rt[MAXN],siz[MAXN];
LL sum[MAXN];

struct Tway
{
	int v,nex;
};
Tway e[MAXN];

struct Tree
{
	int ls,rs,v;
};
Tree tr[MAXN];

void add(int u,int v)
{
	++tot;
	e[tot].v=v;e[tot].nex=head[u];head[u]=tot;
}

int merge(int x,int y)//xie heap
{
	if(!x)	return y;
	if(!y) 	return x;
	if(tr[x].v<tr[y].v)
		swap(x,y);
	tr[x].rs=merge(tr[x].rs,y);
	swap(tr[x].ls,tr[x].rs);
	return x;
}

void popheap(int &x)
{
	x=merge(tr[x].ls,tr[x].rs);
}

int get_top(int x)
{
	return tr[x].v;
}

void dfs(int x)
{
	rt[x]=++cnt;siz[x]=1;
	tr[cnt].v=sum[x]=c[x];
	
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;dfs(v);
		sum[x]+=sum[v];siz[x]+=siz[v];
		rt[x]=merge(rt[x],rt[v]);
	}
	
	while(sum[x]>m)
	{
		sum[x]-=get_top(rt[x]);
		popheap(rt[x]);
		--siz[x];
	}
	ans=max(ans,1ll*siz[x]*l[x]);
}

int main()
{
//	freopen("BZOJ2809.in","r",stdin);
//	freopen("BZOJ2809.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		add(x,i);
		scanf("%d%d",&c[i],&l[i]);
	}
	dfs(1);
	printf("%lld\n",ans);
	
	return 0;
}
