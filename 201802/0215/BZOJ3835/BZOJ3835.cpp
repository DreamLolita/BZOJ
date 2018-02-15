#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int tot,n,m,mx,h,t;
int a[N],to[N],nex[N],head[N];
int dep[N],fa[N],c[N],ans[N],s[N];

void add(int u,int v)
{
	++tot;
	to[tot]=v;nex[tot]=head[u];head[u]=tot;
}

void dfs(int x)
{
	dep[x]=dep[fa[x]]+1;
	mx=max(mx,dep[x]);
	c[dep[x]]++;
	for(int i=head[x];i;i=nex[i])
		dfs(to[i]);
}

int main()
{
	freopen("BZOJ3835.in","r",stdin);
	freopen("BZOJ3835.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
		scanf("%d",&a[i]);
	for(int i=2;i<=n;++i)
	{
		scanf("%d",&fa[i]);
		add(fa[i],i);
	}
	dfs(1);
	for(int i=mx-1;i;--i)
		c[i]+=c[i+1];
	s[1]=1;s[2]=2;t=2;
	for(int i=3;i<=mx;++i)
	{
		while(t>1 && (s[t]-s[t-1])*(c[i]-c[s[t-1]])-(c[s[t]]-c[s[t-1]])*(i-s[t-1])>=0)
			--t;
		s[++t]=i;
	}
	
	h=1;
	for(int i=1;i<=n;++i)
	{
		while(h<t && i*s[h]+c[s[h]]<i*s[h+1]+c[s[h+1]])
			++h;
		ans[i]=s[h];
	}
	
	for(int i=1;i<=m;++i)
	{
		int x=a[i];
		if(x>=n)
			printf("%d",mx);
		else
			printf("%d",max(ans[x]-1+(c[ans[x]]+x-1)/x,mx));
		if(i!=m)
			printf(" ");
	}
	
	return 0;
}
