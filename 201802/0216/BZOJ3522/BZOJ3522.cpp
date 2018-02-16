#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5010;
int n,tot;
int head[N],dep[N];
LL ans;
LL s[N],f[4][N];

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

void dfs(int x,int fa)
{
	s[dep[x]]++;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		dep[v]=dep[x]+1;
		dfs(v,x);
	}
}

int main()
{
//	freopen("BZOJ3522.in","r",stdin);
//	freopen("BZOJ3522.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
	{
		memset(f,0,sizeof(f));
		for(int j=1;j<=n;++j)
			f[0][j]=1;
		for(int j=head[i];j;j=e[j].nex)
		{
			memset(s,0,sizeof(s));
			int v=e[j].v;
			dep[v]=1;dfs(v,i);
			for(int k=3;k;--k)
				for(int q=1;s[q];++q)
					f[k][q]+=f[k-1][q]*s[q];
		}
		for(int j=1;f[3][j];++j)
			ans+=f[3][j];
	}
	printf("%lld\n",ans);
	
	return 0;
}
