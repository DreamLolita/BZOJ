#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m,ans,sum,tot,ind,sc;
int head[N],cnt[N],bl[N],du[N];
int dfn[N],low[N],inq[N];
stack<int>q;

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int u,v,nex;
};
Tway e[N];

void add(int u,int v)
{
	e[++tot]=(Tway){u,v,head[u]};head[u]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++ind;inq[x]=1;q.push(x);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else
		if(inq[v])
			low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x])
	{
		++sc;int t=0;
		while(t!=x)
		{
			t=q.top();q.pop();inq[t]=0;
			bl[t]=sc;cnt[sc]++;
		}
	}
}

int main()
{
	freopen("BZOJ1051.in","r",stdin);
	freopen("BZOJ1051.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=m;++i)
	{
		if(bl[e[i].u]!=bl[e[i].v])
			++du[bl[e[i].u]];
	}
	for(int i=1;i<=sc;++i)
		if(!du[i])
			ans=cnt[i],++sum;
	if(sum==1)
		printf("%d\n",ans);
	else
		puts("0");
	
	return 0;
}
