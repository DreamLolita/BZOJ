#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int M=1005;
int T,n,m,tot,dfn,res;
int s[M],t[M],bin[20];
int head[N],dep[N],pos[N],Log[N<<1];
int mn[20][N<<1],ans[20][N<<1];
LL dis[N],V[M];

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

void dfs(int u,int fa)
{
	ans[0][++dfn]=u;mn[0][dfn]=dep[u];pos[u]=dfn;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		dis[v]=dis[u]+e[i].w;
		dep[v]=dep[u]+1;
		dfs(v,u);
		ans[0][++dfn]=u;mn[0][dfn]=dep[u];
	}
}

int lca(int x,int y)
{
	x=pos[x];y=pos[y];
	if(x>y)
		swap(x,y);
	int t=Log[y-x+1];
	return mn[t][x]<mn[t][y-bin[t]+1]?ans[t][x]:ans[t][y-bin[t]+1];
}

LL get_dis(int x,int y)
{
	return dis[x]+dis[y]-2ll*dis[lca(x,y)];
}

int closest(int a,int b,int c)
{
	int r=lca(a,b),f1,f2;
	if(lca(r,c)!=r)
		return r;
	f1=lca(a,c);
	if(f1!=r)
		return f1;
	return lca(b,c);
}

void get_path(int a,int b,int c,int d,int &x,int &y)
{
	int t1=closest(a,b,c),t2=closest(a,b,d);
	int t3=closest(c,d,a),t4=closest(c,d,b);
	if(t1>t2)	
		swap(t1,t2);
	if(t3>t4)	
		swap(t3,t4);
	if(t1!=t3 || t2!=t4)	
		x=y=0;
	else
		x=t1,y=t2;
}

bool solve(int x,int y)
{
	if(s[x]==s[y])
		return 1;
	int u,v;
	get_path(s[x],t[x],s[y],t[y],u,v);
	if(!u)
		return 0;
	if(u==v)
		return get_dis(s[x],u)*V[y]==get_dis(s[y],u)*V[x];
	else
	{
		if(v==closest(u,v,s[x]))
			swap(u,v);
		if(closest(u,v,s[x])==closest(u,v,s[y]))
		{
			LL d1=get_dis(s[x],u)*V[y],d2=get_dis(s[y],u)*V[x];
			if(d1==d2)
				return 1;
			else
			if(d1>d2)
				swap(x,y);
			return get_dis(s[x],v)*V[y]>=get_dis(s[y],v)*V[x];
		}
		else
			return (get_dis(s[x],u)*V[y]<=get_dis(u,s[y])*V[x] && get_dis(s[y],v)*V[x]<=get_dis(v,s[x])*V[y]);
	}
}


void init()
{
	Log[0]=-1;
	for(int i=1;i<N*2;++i)
		Log[i]=Log[i>>1]+1;
	bin[0]=1;
	for(int i=1;i<20;++i)
		bin[i]=bin[i-1]<<1;
}

void _reset()
{
	memset(head,0,sizeof(head));
	tot=res=dfn=0;
}

int main()
{
//	freopen("BZOJ3700.in","r",stdin);
//	freopen("BZOJ3700.out","w",stdout);
	
	init();
	scanf("%d",&T);
	while(T--)
	{
		_reset();
		scanf("%d",&n);
		for(int i=1;i<n;++i)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			add(u,v,w);
		}
		dfs(1,0);
		for(int i=1;i<=17;++i)
			for(int j=1;j<=dfn;++j)
				if(j+bin[i]-1<=dfn)
				{
					mn[i][j]=mn[i-1][j];
					ans[i][j]=ans[i-1][j];
					if(mn[i-1][j+bin[i-1]]<mn[i][j])
					{
						mn[i][j]=mn[i-1][j+bin[i-1]];
						ans[i][j]=ans[i-1][j+bin[i-1]];
					}
				}
		scanf("%d",&m);
		for(int i=1;i<=m;++i)
			scanf("%d%d%lld",&s[i],&t[i],&V[i]);
		for(int i=1;i<m;++i)
			for(int j=i+1;j<=m;++j)
				res+=solve(i,j);
		printf("%d\n",res);
	}
	
	return 0;
}
