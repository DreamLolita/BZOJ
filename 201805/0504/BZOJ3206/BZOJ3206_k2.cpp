#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=1e5+10;
const int M=3e5+10;
const int P=25;

int n,m,K,top,cnt,st;
int fa[N],fa2[N],p[N];
int po[P],dep[N],last[N],mn[N];
LL ans,val[N],sum[N];
bool mark[M];

LL read()
{
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct Tnode
{
	int u,v,w;
}e[M],ne[P],q[M];

bool operator<(Tnode a,Tnode b)
{
	return a.w<b.w;
}

struct Tway
{
	int to,next;
}ed[P<<1];


void insert(int u,int v)
{
	ed[++cnt]=(Tway){v,last[u]};last[u]=cnt;
	ed[++cnt]=(Tway){u,last[v]};last[v]=cnt;
}
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

int find2(int x)
{
	return x==fa2[x]?x:fa2[x]=find2(fa2[x]);
}

void dp(int x)
{
	sum[x]=val[x];
	for(int i=last[x];i;i=ed[i].next)
		if(ed[i].to!=fa2[x])
		{
			dep[ed[i].to]=dep[x]+1;
			fa2[ed[i].to]=x;
			dp(ed[i].to);
			sum[x]+=sum[ed[i].to];
		}
}

void solve()
{
	cnt=0;
	for(int i=1;i<=K+1;i++)
	{
		int p=po[i];
		last[p]=fa2[p]=0;
		fa[p]=p;mn[p]=INF;
	}
	for(int i=1;i<=K;i++)
		if(mark[i])
		{
			int x=find(ne[i].u),y=find(ne[i].v);
			if(x==y)return;
			fa[x]=y;
			insert(ne[i].u,ne[i].v);
        }
	for(int i=1;i<=K;i++)
	{
		int x=find(q[i].u),y=find(q[i].v);
		if(x!=y)fa[x]=y,insert(q[i].u,q[i].v);
	}
	
	dp(st);
	for(int i=1;i<=K;i++)
	{
		int u=q[i].u,v=q[i].v;
		if(dep[u]>dep[v])swap(u,v);
		while(dep[v]!=dep[u])mn[v]=min(mn[v],q[i].w),v=fa2[v];
		while(u!=v)
		{
            mn[v]=min(mn[v],q[i].w);
            mn[u]=min(mn[u],q[i].w);
            u=fa2[u];v=fa2[v];
        }
	}
	
	LL inc=0;
	for(int i=1;i<=K;i++)
		if(mark[i])
		{
			int u=ne[i].u,v=ne[i].v;
			if(dep[u]>dep[v])swap(u,v);
			inc+=mn[v]*sum[v];
		}
	ans=max(inc,ans);
}

void dfs(int x)
{
	if(x==K+1)
	{
		solve();
		return;
	}
	mark[x]=0;dfs(x+1);
	mark[x]=1;dfs(x+1);
}

void init()
{
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	sort(e+1,e+m+1);
	for(int i=1;i<=K;i++)
		ne[i].u=read(),ne[i].v=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)fa[i]=fa2[i]=i;
    for(int i=1;i<=K;i++)
		fa[find(ne[i].u)]=find(ne[i].v);
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v;
		if(find(u)!=find(v))
		{
			fa[find(u)]=fa[find(v)];
			fa2[find2(u)]=fa2[find2(v)];
		}
	}
}

void getmp()
{
	st=find2(1);
	for(int i=1;i<=n;i++)
	{
		val[find2(i)]+=p[i];
		if(find2(i)==i)po[++po[0]]=i;
	}
	for(int i=1;i<=K;i++)
		ne[i].u=find2(ne[i].u),ne[i].v=find2(ne[i].v);
	for(int i=1;i<=m;i++)
		e[i].u=find2(e[i].u),e[i].v=find2(e[i].v);
	for(int i=1;i<=m;i++)
	{
		int p=find2(e[i].u),q=find2(e[i].v);
		if(p!=q)mark[i]=1,fa2[p]=q;
	}
	for(int i=1;i<=m;i++)
		if(mark[i])q[++top]=e[i];
}

int main()
{
	freopen("BZOJ3206.in","r",stdin);
	freopen("BZOJ3206.out","w",stdout);
	
	init();
	getmp();
	dfs(1);
	printf("%lld\n",ans);
	
	return 0;
}
