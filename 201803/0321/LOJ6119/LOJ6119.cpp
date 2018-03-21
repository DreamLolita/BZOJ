#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,tot,root,sum,top;
int a[N],head[N],siz[N],son[N];
int dis[N],w[N],id[N],sta[N],t[N<<1];
LL ans,cnt,s;
bool vis[N];


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

void getroot(int x,int f)
{
	siz[x]=1;son[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v] || v==f)
			continue;
		getroot(v,x);
		siz[x]+=siz[v];son[x]=max(son[x],siz[v]);
	}
	son[x]=max(son[x],sum-siz[x]);
	if(son[x]<son[root])
		root=x;
}

void dfs(int x,int f,int val)
{
	sta[++top]=x;dis[x]=val;t[val+N]++;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f || vis[v])
			continue;
		dfs(v,x,val+a[v]);
	}
}

void calc(int now,int x,int opt,int st)
{
	top=0;dfs(x,x,st+a[x]);
	for(int i=1;i<=top;++i)
		w[sta[i]]+=opt*t[N-dis[sta[i]]+a[now]];
	for(int i=1;i<=top;++i)
		t[N+dis[sta[i]]]--;
}

void solve(int x)
{
	vis[x]=1;calc(x,x,1,0);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(vis[v])
			continue;
		calc(x,v,-1,a[x]);
		root=0;sum=siz[v];
		getroot(v,x);solve(root);
	}
}

int main()
{
	freopen("LOJ6119.in","r",stdin);
	freopen("LOJ6119.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),a[i]?:a[i]=-1;
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	root=0;sum=n;son[0]=n+1;
	getroot(1,0);
	solve(root);
	for(int i=1;i<=n;++i)
		s+=w[i];
	for(int i=1,l=1;i<=n;++i)
	{
		cnt+=w[i];
		while(l<i && cnt>s-cnt)
			cnt-=w[l++];
		ans+=l-1;
	}
	printf("%lld\n",ans);
	
	return 0;
}
