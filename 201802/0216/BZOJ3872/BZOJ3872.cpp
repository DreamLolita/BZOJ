#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=1e6+10;
int n,g,k,tot,su,sv;
int du[N],head[N],m[N];
LL ans,cnt;
LL d[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		ret=(ret<<3)+(ret<<1)+(c-'0');
		c=getchar();
	}
	return ret;
}

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

inline int findl(int x)
{
	if(!x)
		return 0;
	int l=1,r=g,ret=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(m[mid]/x==k)
			ret=mid,r=mid-1;
		else
		if(m[mid]/x<k)
			l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}

inline int findr(int x)
{
	if(!x)
		return 0;
	int l=1,r=g,ret=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(m[mid]/x==k)
			ret=mid,l=mid+1;
		else
		if(m[mid]/x>k)
			r=mid-1;
		else
			l=mid+1;
	}
	return ret;
}

inline void dfs(int u,int fa)
{
	bool flag=false;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		flag=true;
		d[v]=1ll*d[u]*(du[u]-1ll);
		if(d[v]>INF)
			d[v]=0;
		dfs(v,u);
	}
	if(!flag)
	{
		int L=findl(d[u]),R=findr(d[u]);
		if(!L || !R)
			return;
		cnt+=R-L+1;
	}
}

int main()
{
	freopen("BZOJ3872.in","r",stdin);
	freopen("BZOJ3872.out","w",stdout);
	
	n=read();g=read();k=read();
	for(int i=1;i<=g;++i)
		m[i]=read();
	sort(m+1,m+g+1);
	for(int i=1;i<n;++i)
	{
		int u,v;
		u=read();v=read();
		add(u,v);
		++du[u];++du[v];
		if(i==1)
			su=u,sv=v;
	}
	d[su]=d[sv]=1;
	dfs(su,sv);dfs(sv,su);
	ans=1ll*cnt*k;
	printf("%lld\n",ans);
	
	return 0;
}
