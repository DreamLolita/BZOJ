#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=3e5+10;
const int M=2e6+10;
int n,m,ta,tb,cnt,pt,tot,dfsclk,tp;
int head[N],stk[N],a[N],b[N];
int mx[N],mn[N],sc[N],q[N],id[N],dfn[N],low[N]; 
bool vis[N];

struct Tway
{
	int u,v,nex,w;
};
Tway E[M],e[M];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){u,v,head[u],w};head[u]=tot;
	if(w==2)
		e[++tot]=(Tway){v,u,head[v],w},head[v]=tot;
}

void dfs(int u)
{
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
			dfs(v);
	}
}

void tarjan(int u)
{
	dfn[u]=low[u]=++dfsclk;stk[++tp]=u;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else
		if(!sc[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++cnt;mx[cnt]=-INF;mn[cnt]=INF;
		
		int v;
		while(true)
		{
			sc[stk[tp]]=cnt;
			if(v=id[stk[tp]])
			{
				mx[cnt]=max(mx[cnt],v);
				mn[cnt]=min(mn[cnt],v);
			}
			if(stk[tp--]==u)
				break;
		}
	}
}

void dp(int u)
{
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
			dp(v);
		mx[u]=max(mx[u],mx[v]);
		mn[u]=min(mn[u],mn[v]);
	}
}

bool cmp(const int &x,const int &y)
{
	return b[x]>b[y];
}

int main()
{
	freopen("BZOJ2387.in","r",stdin);
	freopen("BZOJ2387.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&ta,&tb);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
		add(E[i].u,E[i].v,E[i].w);
	}
	for(int i=1;i<=n;++i)
		if(!a[i])
			dfs(i);
	for(int i=1;i<=n;++i)
		if(a[i]==ta && vis[i])
			q[++pt]=i;

	sort(q+1,q+pt+1,cmp);
	for(int i=1;i<=pt;++i)
		id[q[i]]=i;
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	tot=0;
	memset(head,0,sizeof(head));
	for(int i=1;i<=m;++i)
	{
		int x=sc[E[i].u],y=sc[E[i].v];
		if(x!=y)
			add(x,y,1);
	}
	
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=cnt;++i)
		dp(i);
	pt=0;
	for(int i=1;i<=n;++i)
		if(!a[i])
			q[++pt]=i;
	sort(q+1,q+pt+1,cmp);
	for(int i=1;i<=pt;++i)
		printf("%d\n",max(0,mx[sc[q[i]]]-mn[sc[q[i]]]+1));
	
	return 0;
}
