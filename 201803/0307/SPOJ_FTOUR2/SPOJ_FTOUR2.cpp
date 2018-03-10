#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef pair<int,int> pii;
const int N=2e5+10;
int T,n,m,k,tot,rt,sum,mxdep,ans;
int head[N],siz[N],f[N],dep[N],dis[N];
int tmp[N],mx[N];
bool col[N],vis[N];
vector<pii>mp;

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}

inline void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

inline void getroot(int x,int fa)
{
	siz[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			getroot(v,x);
			f[x]=max(f[x],siz[v]);
			siz[x]+=siz[v];
		}
	}
	f[x]=max(f[x],sum-siz[x]);
	if(f[x]<f[rt])
		rt=x;
}

inline void getdis(int x,int fa)
{
	mxdep=max(mxdep,dep[x]);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			dep[v]=dep[x]+col[v];
			dis[v]=dis[x]+e[i].w;
			getdis(v,x);
		}
	}
}

inline void getmx(int x,int fa)
{
	tmp[dep[x]]=max(tmp[dep[x]],dis[x]);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
			getmx(v,x);
	}
}

inline void solve(int x)
{
	vis[x]=1;mp.clear();
	if(col[x])
		--k;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			mxdep=0;
			dep[v]=col[v];dis[v]=e[i].w;
			getdis(v,x);
			mp.push_back(mkp(mxdep,v));	
		}
	}
	sort(mp.begin(),mp.end());
	for(int i=0;i<mp.size();++i)
	{
		getmx(mp[i].second,x);
		int now=0;
		if(i!=0)
		{
			for(int j=mp[i].first;j>=0;--j)
			{
				while(now+j<k && now<mp[i-1].first)
					mx[++now]=max(mx[now],mx[now-1]);
				if(now+j<=k)
					ans=max(ans,mx[now]+tmp[j]);
			}
		}
		if(i!=mp.size()-1)
		{
			for(int j=0;j<=mp[i].first;++j)
				mx[j]=max(mx[j],tmp[j]),tmp[j]=0;
		}
		else
		{
			for(int j=0;j<=mp[i].first;++j)
			{
				if(j<=k)
					ans=max(ans,max(tmp[j],mx[j]));
				tmp[j]=mx[j]=0;
			}
		}
	}
	if(col[x])
		++k;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			rt=0;sum=siz[v];
			getroot(v,x);
			solve(rt);
		}
	}
}

int main()
{
	freopen("SPOJ_FTOUR2.in","r",stdin);
	freopen("SPOJ_FTOUR2.out","w",stdout);
	
	n=read();k=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int x;x=read();
		col[x]=1;
	}
	for(int i=1;i<n;++i)
	{
		int u,v,w;
		u=read();v=read();w=read();
		add(u,v,w);
	}
	f[0]=n;sum=n;
	getroot(1,0);
	solve(rt);
	printf("%d\n",ans);

	return 0;
}
