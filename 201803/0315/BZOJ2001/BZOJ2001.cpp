#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int M=5e4+10;
const int L=16;
int n,m,q;
int fa[M],siz[M],mp[M],ww[M];
LL ans[M];

struct Tway
{
	int u,v,w,id;
	bool operator < (Tway const &A)const{
		return w<A.w;
	}
};
Tway e[L][M],d[M],t[M];

struct Tquery
{
	int x,y;
};
Tquery qs[M];

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void merge(int x,int y)
{
	x=findf(x);y=findf(y);
	if(siz[x]>siz[y])
		swap(x,y);
	siz[y]+=siz[x];fa[x]=y;
}

void map_reset(int x,Tway *e)
{
	for(int i=0;i<x;++i)
	{
		fa[e[i].u]=e[i].u;fa[e[i].v]=e[i].v;
		siz[e[i].u]=siz[e[i].v]=1;
	}
}

LL calc(int &x)
{
	int len=0;
	sort(d,d+x);
	for(int i=0;i<x;++i)
	{
		if(findf(d[i].u)!=findf(d[i].v))
		{
			merge(d[i].u,d[i].v);
			t[len++]=d[i];
		}
	}
	map_reset(len,t);
	LL ret=0;
	for(int i=0;i<len;++i)
	{
		if(t[i].w!=-INF && findf(t[i].u)!=findf(t[i].v))
		{
			merge(t[i].u,t[i].v);
			ret+=t[i].w;
		}
	}
	
	len=0;
	for(int i=0;i<x;++i)
	{
		if(findf(d[i].u)!=findf(d[i].v))
		{
			t[len]=d[i];
			t[len].u=fa[d[i].u];t[len].v=fa[d[i].v];
			mp[d[i].id]=len++;
		}
	}
	
	map_reset(x,d);
	x=len;
	for(int i=0;i<len;++i)
		d[i]=t[i];
	return ret;
}

void reduction(int &x)
{
	int len=0;
	sort(d,d+x);
	for(int i=0;i<x;++i)
	{
		if(findf(d[i].u)!=findf(d[i].v))
		{
			merge(d[i].u,d[i].v);
			t[len]=d[i];
			mp[d[i].id]=len++;
		}
		else
		{
			if(d[i].w==INF)
			{
				t[len]=d[i];
				mp[d[i].id]=len++;
			}
		}
	}
	map_reset(x,d);x=len;
	for(int i=0;i<len;++i)
		d[i]=t[i];
}

void solve(int now,int x,int l,int r,LL ret)
{
	if(l==r)
		ww[qs[l].x]=qs[l].y;
	for(int i=0;i<x;++i)
	{
		e[now][i].w=ww[e[now][i].id];
		d[i]=e[now][i];
		mp[d[i].id]=i;
	}
	if(l==r)
	{
		ans[l]=ret;
		sort(d,d+x);
		for(int i=0;i<x;++i)
		{
			if(findf(d[i].u)!=findf(d[i].v))
			{
				merge(d[i].u,d[i].v);
				ans[l]+=d[i].w;
			}
		}
		map_reset(x,d);
		return;
	}

	for(int i=l;i<=r;++i)
		d[mp[qs[i].x]].w=-INF;
	ret+=calc(x);
	for(int i=l;i<=r;++i)
		d[mp[qs[i].x]].w=INF;
	reduction(x);
	for(int i=0;i<x;++i)
		e[now+1][i]=d[i];
		
	int mid=(l+r)>>1;
	solve(now+1,x,l,mid,ret);
	solve(now+1,x,mid+1,r,ret);
}

int main()
{
	freopen("BZOJ2001.in","r",stdin);
	freopen("BZOJ2001.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<=n;++i)
		fa[i]=i,siz[i]=1;
	for(int i=0;i<m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[0][i].u=u;e[0][i].v=v;
		e[0][i].w=w;e[0][i].id=i;
		ww[i]=w;
	}
	
	for(int i=1;i<=q;++i)
		scanf("%d%d",&qs[i].x,&qs[i].y),--qs[i].x;
	solve(0,m,1,q,0);
	for(int i=1;i<=q;++i)
		printf("%lld\n",ans[i]);
	
	return 0;
}
