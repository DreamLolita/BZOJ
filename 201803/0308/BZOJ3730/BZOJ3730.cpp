#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1e5+10;

int n,m,rt,ans,cnt,tot,sum;
int head[N],siz[N],f[N],dep[N],val[N];
int fa[N][20],dis[N][20];
bool vis[N];
vector<int>tr[N],bit[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void getroot(int x,int ff)
{
	siz[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=ff)
		{
			getroot(v,x);
			siz[x]+=siz[v];
			f[x]=max(f[x],siz[v]);
		}
	}
	f[x]=max(f[x],sum-f[x]);
	if(f[x]<f[rt])
		rt=x;
}

void get_tree(int x,int anc,int ff,int d)
{
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=ff)
		{
			fa[v][++dep[v]]=anc;dis[v][dep[v]]=d;
			get_tree(v,anc,x,d+1);
		}
	}
}

void build_tree(int x)
{
	vis[x]=1;
	get_tree(x,x,0,1);
	int t=sum;
	tr[x].resize(t+1);bit[x].resize(t+1);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			sum=siz[v];
			if(sum>siz[x])
				sum=t-siz[x];
			rt=0;getroot(v,x);
			build_tree(rt);
		}
	}
}

int lowbit(int x)
{
	return x&(-x);
}

int qsum(int x,int k)
{
	int ret=val[x],lim=tr[x].size()-1;k=min(k,lim);
	for(int i=k;i;i-=lowbit(i))
		ret+=tr[x][i];
	return ret;
}

int qsum2(int x,int k)
{
	int ret=0,lim=bit[x].size()-1;k=min(k,lim);
	for(int i=k;i;i-=lowbit(i))
		ret+=bit[x][i];
	return ret;
}

void update(int x,int v)
{
	int d,lim;
	d=dis[x][dep[x]];lim=tr[x].size()-1;
	for(int i=d;i<=lim && i;i+=lowbit(i))
		bit[x][i]+=v;
	for(int i=dep[x];i;--i)
	{
		d=dis[x][i];lim=tr[fa[x][i]].size()-1;
		for(int j=d;j<=lim;j+=lowbit(j))
			tr[fa[x][i]][j]+=v;
		d=dis[x][i-1];
		for(int j=d;j<=lim && j;j+=lowbit(j))
			bit[fa[x][i]][j]+=v;
	}
}

int query(int x,int k)
{
	int ret=qsum(x,k);
	for(int i=dep[x];i;--i)
		if(dis[x][i]<=k)
			ret+=qsum(fa[x][i],k-dis[x][i])-qsum2(fa[x][i+1],k-dis[x][i]);
	return ret;
}

int main()
{
	freopen("BZOJ3730.in","r",stdin);
	freopen("BZOJ3730.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&val[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}	
	f[0]=INF;sum=n;
	getroot(1,0);build_tree(rt);
	for(int i=1;i<=n;++i)
		fa[i][dep[i]+1]=i;
	for(int i=1;i<=n;++i)
		update(i,val[i]);
	while(m--)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);y^=ans;z^=ans;
		if(x)
			update(y,z-val[y]),val[y]=z;
		else
			ans=query(y,z),printf("%d\n",ans);
	}
	
	return 0;
}
