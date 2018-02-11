#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,m,q,ans,cnt;
int fa[N],sum[N],d[N];

struct Tway
{
	int u,v,c;
};
Tway e[N];

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

int main()
{
	freopen("BZOJ3706.in","r",stdin);
	freopen("BZOJ3706.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
		int fu=findf(e[i].u),fv=findf(e[i].v);
		if(fu!=fv)
		{
			fa[fu]=fv;
			if(sum[fu] && sum[fv])
				--ans;
			sum[fv]+=sum[fu];
		}
		if(e[i].c)
		{
			sum[fv]++;
			if(sum[fv]==1)
				++ans;
			d[e[i].u]++;d[e[i].v]++;
			(d[e[i].u]&1)?++cnt:--cnt;
			(d[e[i].v]&1)?++cnt:--cnt;
		}
		else
		if(fu!=fv && sum[fu] && sum[fv])
			--ans;
	}
	
	scanf("%d",&q);
	while(q--)
	{
		int opt,x;
		scanf("%d",&opt);
		if(opt&1)
		{
			scanf("%d",&x);++x;
			e[x].c^=1;
			int fu=findf(e[x].u);
			
			if(e[x].c)
			{
				sum[fu]++;
				if(sum[fu]==1)
					++ans;
				d[e[x].u]++;d[e[x].v]++;
				(d[e[x].u]&1)?++cnt:--cnt;
				(d[e[x].v]&1)?++cnt:--cnt;
			}
			else
			{
				sum[fu]--;
				if(sum[fu]==0)
					--ans;
				d[e[x].u]--;d[e[x].v]--;
				(d[e[x].u]&1)?++cnt:--cnt;
				(d[e[x].v]&1)?++cnt:--cnt;
			}
		}
		else
			cnt?puts("-1"):printf("%d\n",ans);
	}
	
	return 0;
}
