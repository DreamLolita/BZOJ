#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m,tot,tim;
int fa[N],top[N],siz[N],son[N];
int head[N],dep[N],beg[N],en[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct Tree
{
	int sum,ans;
	int tar[2];
};
Tree tr[N<<2];

void add(int u,int v)
{
	++tot;
	e[tot].v=v;e[tot].nex=head[u];head[u]=tot;
}

void dfs1(int u,int f)
{
	dep[u]=dep[f]+1;siz[u]=1;fa[u]=f;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
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
	beg[u]=++tim;top[u]=tp;
	if(son[u])
		dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[u] || v==son[u])
			continue;
		dfs2(v,v);
	}
	en[u]=tim;
}

void pushup(int rt)
{
	tr[rt].sum=tr[rt<<1].sum+tr[rt<<1|1].sum;
	tr[rt].ans=tr[rt<<1].ans+tr[rt<<1|1].ans;
}

void change(int rt,int l,int r,int v)
{
	tr[rt].tar[1]+=v;
	tr[rt].sum+=v*(r-l+1);
}

void change2(int rt,int v)
{
	tr[rt].tar[0]=v;
	tr[rt].ans=tr[rt].sum*v;
}

void pushdown(int rt,int l,int r)
{
	if(tr[rt].tar[1])
	{
		int mid=(l+r)>>1;
		change(rt<<1,l,mid,tr[rt].tar[1]);
		change(rt<<1|1,mid+1,r,tr[rt].tar[1]);
		tr[rt].tar[1]=0;
	}
	if(tr[rt].tar[0]!=-1)
	{
		change2(rt<<1,tr[rt].tar[0]);
		change2(rt<<1|1,tr[rt].tar[0]);
		tr[rt].tar[0]=-1;	
	}
}

void build(int rt,int l,int r)
{
	tr[rt].tar[0]=-1;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
}

void update(int rt,int l,int r,int L,int R,int v)
{
	if(tr[rt].tar[0]==v)
		return;
	if(L<=l && r<=R)
	{
		change2(rt,v);
		return;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		update(rt<<1,l,mid,L,R,v);
	if(R>mid)
		update(rt<<1|1,mid+1,r,L,R,v);
	pushup(rt);
}

void update2(int rt,int l,int r,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		change(rt,l,r,v);
		return;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		update2(rt<<1,l,mid,L,R,v);
	if(R>mid)
		update2(rt<<1|1,mid+1,r,L,R,v);
	pushup(rt);
}

void solve(int u,int v,int opt)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
//printf("!%d %d\n",beg[top[u]],beg[u]);
		update(1,1,n,beg[top[u]],beg[u],opt);
		u=fa[top[u]];
	}

	if(dep[u]>dep[v])
		swap(u,v);
//printf("!%d %d\n",beg[u],beg[v]);
	update(1,1,n,beg[u],beg[v],opt);
}

void debug(int rt,int l,int r)
{
printf("%d %d %d:",rt,l,r);
printf("%d %d\n",tr[rt].sum,tr[rt].ans);
    if(l==r)
    	return;
   	int mid=(l+r)>>1;
   	debug(rt<<1,l,mid);
   	debug(rt<<1|1,mid+1,r);
}

int main()
{
//	freopen("BZOJ3589.in","r",stdin);
//	freopen("BZOJ3589.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}	
	dfs1(1,1);dfs2(1,1);
	build(1,1,n);

	scanf("%d",&m);
	while(m--)
	{
		int opt,x,u,v;
		scanf("%d%d",&opt,&x);
		if(opt)
		{
			for(int i=1;i<=x;++i)
			{
				scanf("%d%d",&u,&v);
				solve(u,v,1);
			}
			printf("%d\n",tr[1].ans&((1<<31)-1));
			change2(1,0);
		}
		else
		{
			scanf("%d",&u);
			update2(1,1,n,beg[x],en[x],u);
		}
//		debug(1,1,n);
	}
	
	return 0;
}
