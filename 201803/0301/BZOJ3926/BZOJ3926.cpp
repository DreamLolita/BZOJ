#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,m,tot;
LL ans;
int col[N],head[N],du[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct Tsam
{
	int cnt;
	int pa[N*40],mx[N*40],ch[N*40][12];
	
	Tsam(){cnt=1;}
	int extend(int p,int c)
	{
		int np=++cnt;mx[np]=mx[p]+1;
		while(!ch[p][c] && p)
			ch[p][c]=np,p=pa[p];
		if(!p)
			pa[np]=1;
		else
		{
			int q=ch[p][c];
			if(mx[p]+1==mx[q])
				pa[np]=q;
			else
			{
				int nq=++cnt;mx[nq]=mx[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				pa[nq]=pa[q];pa[np]=pa[q]=nq;
				while(p && ch[p][c]==q)
					ch[p][c]=nq,p=pa[p];
			}
		}
		return np;
	}
	
	void solve()
	{
		for(int i=1;i<=cnt;++i)
			ans+=mx[i]-mx[pa[i]];
	}
};
Tsam sam;

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void dfs(int x,int fa,int p)
{
	int t=sam.extend(p,col[x]);
	for(int i=head[x];i;i=e[i].nex)
		if(e[i].v!=fa)
			dfs(e[i].v,x,t);
}

int main()
{
	freopen("BZOJ3926.in","r",stdin);
	freopen("BZOJ3926.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		du[u]++;du[v]++;
	}
	for(int i=1;i<=n;++i)
		if(du[i]==1)
			dfs(i,0,1);
	sam.solve();
	printf("%lld\n",ans);
	
	return 0;
}
