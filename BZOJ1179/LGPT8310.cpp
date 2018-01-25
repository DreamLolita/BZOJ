#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN=5e5+10;
int n,m,tot,beg,p,cnt,sc,num;
int val[MAXN],head[MAXN],ps[MAXN];
int pub[MAXN],sum[MAXN],dis[MAXN],alc[MAXN];
int ins[MAXN],col[MAXN],dfn[MAXN],low[MAXN];
bool pum[MAXN],inq[MAXN];
vector<int>mp[MAXN];
stack<int>q;

struct Tway
{
	int u,v,nex;
};
Tway e[MAXN<<1];

inline int ri()
{
	char ch=getchar();
	int u=0;
	while(ch<'0' || ch>'9')
		ch=getchar();
	while(ch>='0' && ch<='9')
	{
		u=u*10+(ch-'0');
		ch=getchar();
	}
	return u;
}

inline void add(int u,int v)
{
	++tot;
	e[tot].u=u;e[tot].v=v;
	e[tot].nex=head[u];head[u]=tot;
}

inline void init()
{
	memset(head,-1,sizeof(head));
	n=ri();m=ri();
	for(int i=1;i<=m;++i)
	{
		int u,v;
		u=ri();v=ri();
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		val[i]=ri();
	beg=ri();p=ri();
	for(int i=1;i<=p;++i)
	{
		ps[i]=ri();
		pub[ps[i]]=true;
	}
}

inline void dfs(int u)
{
	dfn[u]=low[u]=++cnt;
	ins[u]=1;
	q.push(u);
	for(int i=head[u];i!=-1;i=e[i].nex)
	{
		int v=e[i].v;

		if(!dfn[v])
		{
			dfs(v);
			low[u]=min(low[u],low[v]);
		}
		else
		if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}

	if(low[u]==dfn[u])
	{
		sum[++sc]=alc[sc]=0;
		while(!q.empty())
		{
			int tmp=q.top();q.pop();
			ins[tmp]=0;col[tmp]=sc;sum[sc]+=val[tmp];
			if(tmp==beg)
				beg=sc;
			if(pub[tmp])
				alc[sc]=1;
			if(tmp==u)
				break;		
		}
	}
}

inline void tarjan()
{
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			dfs(i);
	for(int i=1;i<=tot;++i)
	{
		int u=col[e[i].u],v=col[e[i].v];
		if(u!=v)
			mp[u].push_back(v);
	}
}

inline void spfa(int beg)
{
	queue<int>qq;
	memset(dis,-1,sizeof(dis));
	inq[beg]=true;dis[beg]=sum[beg];
	qq.push(beg);
	while(!qq.empty())
	{
		int u=qq.front(),siz=mp[u].size();
		qq.pop();inq[u]=false;
		for(int i=0;i<siz;++i)
		{
			int v=mp[u][i];
			if(dis[v]<dis[u]+sum[v])
			{
				dis[v]=dis[u]+sum[v];
				if(!inq[v])
				{
					inq[v]=true;
					qq.push(v);
				}
			}
		}
	}
	
	int ans=0;
	for(int i=1;i<=sc;++i)
		if(alc[i])
			ans=max(ans,dis[i]);
	printf("%d\n",ans);
}

int main()
{
//	freopen("LGPT8310.in","r",stdin);
//	freopen("LGPT8310.out","w",stdout);BZOJ1179
	
	init();
	tarjan();
	spfa(beg);
	
	return 0;
}
