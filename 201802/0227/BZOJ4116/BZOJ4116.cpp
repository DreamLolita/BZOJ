#include<bits/stdc++.h>
using namespace std;

const int N=2005;
int n,m,cnt,ans,tot=1;
int head[N],low[N],dfn[N],id[N];
int bridge[N],del[N],vis[N]; 

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

void tarjan(int x,int y)
{
	dfn[x]=low[x]=++cnt;
	for(int i=head[x];i;i=e[i].nex)
	{
		if((i^1)!=y && !del[i>>1])
		{
			int v=e[i].v;
			if(!dfn[v])
			{
				tarjan(v,i);
				low[x]=min(low[x],low[v]);
				if(low[v]>dfn[x])
					bridge[i>>1]=1;
			}
			else
				low[x]=min(low[x],dfn[v]);
		}
	}
}

int gcd(int a,int b)
{
	if(!(a%b))
		return b;
	return gcd(b,a%b);
}

void _reset()
{
	cnt=0;
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(bridge,0,sizeof(bridge));
}

int main()
{
	freopen("BZOJ4116.in","r",stdin);
	freopen("BZOJ4116.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i,0);
	memcpy(id,bridge,sizeof(bridge));
	
	int sum=0;
	for(int i=1;i<=m;++i)
	{
		if(!vis[i] && !id[i])
		{
			_reset();
			del[i]=vis[i]=sum=1;
			for(int j=1;j<=n;++j)
				if(!dfn[j])
					tarjan(j,0);
			for(int j=1;j<=m;++j)
				if(!id[j] && bridge[j])
					++sum,vis[j]=1;
			ans=(ans==0)?sum:gcd(ans,sum);
			del[i]=0;
		}
	}
	for(int i=1;i<ans;++i)
		if(ans%i==0)
			printf("%d ",i);
	if(ans)
		printf("%d\n",ans);
	
	return 0;
}
