#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e5+10;
int n,m,tot;
int dep[N],dead[N],en[N],beg[N],rt[N],head[N];
LL A[N],V[N],D[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct Tree
{
	int l,r,dis;
	LL lc,lp,v;
};
Tree q[N];

LL read()
{
    LL x=0,t=1;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')
		ch=getchar();
    if(ch=='-')
		t=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
		x=x*10+ch-48,ch=getchar();
    return x*t;
}

void add(int u,int v)
{
	++tot;
	e[tot].v=v;e[tot].nex=head[u];head[u]=tot;
}

void update(int r,LL mul,LL plu)
{
	if(!r)	return;
	q[r].v*=mul;q[r].v+=plu;
	q[r].lp*=mul;q[r].lp+=plu;
	q[r].lc*=mul;
}

void pushdown(int r)
{
	update(q[r].l,q[r].lc,q[r].lp);
	update(q[r].r,q[r].lc,q[r].lp);
	q[r].lc=1;q[r].lp=0;
}

int merge(int r1,int r2)
{
	if(!r1 || !r2)	
		return r1+r2;
	pushdown(r1);pushdown(r2);
	
	if(q[r1].v>q[r2].v)	
		swap(r1,r2);
	q[r1].r=merge(q[r1].r,r2);
	if(q[q[r1].l].dis<q[q[r1].r].dis)
		swap(q[r1].l,q[r1].r);
	q[r1].dis=q[q[r1].r].dis+1;
	return r1;
}

int pop(int r)
{
	return merge(q[r].l,q[r].r);
}

void dfs(int u,int f)
{
	dep[u]=dep[f]+1;
	for(int i=head[u];i;i=e[i].nex)
		dfs(e[i].v,u);
	for(int i=head[u];i;i=e[i].nex)
		rt[u]=merge(rt[u],rt[e[i].v]);
	while(rt[u] && q[rt[u]].v<D[u])
	{
		pushdown(rt[u]);
		dead[u]++;en[rt[u]]=u;
		rt[u]=pop(rt[u]);
	}
	if(!A[u])	update(rt[u],1,V[u]);
		else	update(rt[u],V[u],0);
}

int main()
{
	freopen("BZOJ4003.in","r",stdin);
	freopen("BZOJ4003.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
		D[i]=read();
	for(int i=2;i<=n;++i)
	{
		int v=read();add(v,i);
		A[i]=read();V[i]=read();
	}

	for(int i=1;i<=m;++i)
		q[i].lp=0,q[i].lc=1;
	for(int i=1;i<=m;++i)
	{
		q[i].v=read();beg[i]=read();
		rt[beg[i]]=merge(rt[beg[i]],i);
	}
	dfs(1,0);
	
	for(int i=1;i<=n;++i)
		printf("%d\n",dead[i]);
	for(int i=1;i<=m;++i)
		printf("%d\n",dep[beg[i]]-dep[en[i]]);
	
	return 0;
}
