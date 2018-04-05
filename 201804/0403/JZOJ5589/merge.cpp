#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m,tot,totE;
int ind,sum,lef,mx,rt,ans,cnt,trees;
int head[N],headE[N];
int dfn[N],low[N],bl[N],du[N],siz[N];
bool vis[N];
stack<int>q;
map<int,bool>mp[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1],E[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

void dfs(int x,int f)
{
	dfn[x]=low[x]=++ind;q.push(x);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		if(!dfn[v])
			dfs(v,x),low[x]=min(low[x],low[v]);
		else
			low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		int now=0;cnt++;
		while(now!=x)
		{
			now=q.top();q.pop();
			bl[now]=cnt;++siz[cnt];
		}
	}
}

void dfs1(int x,int f,int dp,int opt)
{
	++sum;vis[x]=true;
	if(dp>mx)	
		rt=x,mx=dp;
	if(du[x]==1)
		++lef;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=f && !vis[v])
			dfs1(v,x,dp+1,opt);
	}
	if(opt)
		vis[x]=false;
}

void _reset()
{
	memcpy(E,e,sizeof(e));memcpy(headE,head,sizeof(head));totE=tot;
	memset(head,0,sizeof(head));tot=0;
}

int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			dfs(i,0);
	_reset();

	for(int i=1;i<=n;++i)
		for(int j=headE[i];j;j=E[j].nex)
		{
			int v=E[j].v;
			if(bl[i]!=bl[v] && !mp[bl[i]][bl[v]])
				add(bl[i],bl[v]),++du[bl[v]],mp[bl[i]][bl[v]]=1;
		}

	for(int i=1;i<=cnt;++i)
	{
		ans+=siz[i]-1;
		if(!vis[i])
		{
			++trees;
			rt=mx=0;dfs1(i,0,1,1);
			mx=lef=sum=0;dfs1(rt,0,1,0);
			if(sum==1)
				continue;
			ans+=sum-(mx+lef-2);
		}
	}
	printf("%d\n",ans+trees-1);
	
	return 0;
}
