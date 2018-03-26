#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,m,tot,ans1;
int fa[N],h[N],head[N];
bool vis[N];
LL ans2;
queue<int>q;

struct Tway
{
	int u,v,nex,w;
};
Tway e[N*20];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){u,v,head[u],w};
	head[u]=tot;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&h[i]);
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(h[u]>=h[v])
			add(u,v,w);
		if(h[u]<=h[v])
			add(v,u,w);
	}	
}

void bfs()
{
	vis[1]=true;ans1=1;q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(!vis[v])
			{
				vis[v]=true;++ans1;
				q.push(v);
			}
		}
	}
}

bool cmp(Tway x,Tway y)
{
	return h[x.v]>h[y.v] || (h[x.v]==h[y.v] && x.w<y.w);
}

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void MST()
{
	for(int i=1;i<=n;++i)
		fa[i]=i;
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;++i)
	{
		if(!vis[e[i].u] || !vis[e[i].v])
			continue;
		int fx=findf(e[i].u),fy=findf(e[i].v);
		if(fx!=fy)
		{
			fa[fx]=fy;
			ans2+=e[i].w;
		}
	}
}

void print_ans()
{
	printf("%d %lld\n",ans1,ans2);
}

int main()
{
	freopen("BZOJ2753.in","r",stdin);
	freopen("BZOJ2753.out","w",stdout);
	
	init();
	bfs();
	MST();
	print_ans();

	return 0;
}
