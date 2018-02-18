#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=2525;
const int M=1e6+10;
int n,m,S,T,ans,tot=-1;
int dep[N<<2],head[N<<2];
LL ref[N<<2],ra[N],rb[N];
map<LL,int>mp;
queue<int>q;

struct Tmp
{
	int v,nex,w; 
};
Tmp e[M];

void add(int u,int v,int w)
{
	e[++tot]=(Tmp){v,head[u],w};head[u]=tot;
	e[++tot]=(Tmp){u,head[v],0};head[v]=tot;
}

int dfs(int x,int mf)
{
	if(x==T)
		return mf;
	int tmp=mf;
	for(int i=head[x];~i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dep[v]==dep[x]+1 && e[i].w)
		{
			int res=dfs(v,min(tmp,e[i].w));
			if(!res)
				dep[v]=0;
			tmp-=res;e[i].w-=res;e[i^1].w+=res;
			if(!tmp)
				break;
		}
	}
	return mf-tmp;
}

bool bfs()
{
	while(!q.empty())
		q.pop();
	memset(dep,0,sizeof(dep));
	q.push(S);dep[S]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];~i;i=e[i].nex)
		{
			int v=e[i].v;
			if(!dep[v] && e[i].w)
			{
				dep[v]=dep[u]+1;
				if(v==T)
					return 1;
				q.push(v);
			}
		}
	}
	return 0;
}


int main()
{
	freopen("BZOJ4429.in","r",stdin);
	freopen("BZOJ4429.out","w",stdout);
	
	scanf("%d",&n);m=n;S=0;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;++i)
	{
		scanf("%lld%lld",&ra[i],&rb[i]);
		if(!mp[ra[i]+rb[i]])
			mp[ra[i]+rb[i]]=++m,ref[m]=ra[i]+rb[i];
		if(!mp[ra[i]-rb[i]])
			mp[ra[i]-rb[i]]=++m,ref[m]=ra[i]-rb[i];
		if(!mp[ra[i]*rb[i]])
			mp[ra[i]*rb[i]]=++m,ref[m]=ra[i]*rb[i];
		add(i,mp[ra[i]+rb[i]],1);add(i,mp[ra[i]-rb[i]],1);
		add(i,mp[ra[i]*rb[i]],1);add(S,i,1);
	}
	T=m+1;
	for(int i=n+1;i<=m;++i)
		add(i,T,1);
	while(bfs())
		ans+=dfs(S,INF);
	if(ans!=n)
	{
		puts("impossible");
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=head[i];~j;j=e[j].nex)
			if(!e[j].w)
			{
				int v=e[j].v;
				if(ref[v]==ra[i]+rb[i])
					printf("%lld + %lld = %lld\n",ra[i],rb[i],ra[i]+rb[i]);
				else
				if(ref[v]==ra[i]-rb[i])
					printf("%lld - %lld = %lld\n",ra[i],rb[i],ra[i]-rb[i]);
				else
				if(ref[v]==ra[i]*rb[i])
					printf("%lld * %lld = %lld\n",ra[i],rb[i],ra[i]*rb[i]);
			}
	}
	
	return 0;
}
