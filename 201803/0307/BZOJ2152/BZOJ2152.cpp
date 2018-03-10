#include<bits/stdc++.h>
using namespace std;

const int N=2e4+10;
int n,tot,sum,root,ans;
int head[N],son[N],f[N],d[N],t[5];
bool vis[N];

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1];

int gcd(int x,int y)
{
	if(x%y==0)
		return y;
	return gcd(y,x%y);
}

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

void getroot(int x,int fa)
{
	son[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			getroot(v,x);
			son[x]+=son[v];
			f[x]=max(f[x],son[v]);
		}
	}
	f[x]=max(f[x],sum-son[x]);
	if(f[x]<f[root])
		root=x;
}

void getdeep(int x,int fa)
{
	t[d[x]]++;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			d[v]=(d[x]+e[i].w)%3;
			getdeep(v,x);
		}
	}
}

int calc(int x,int now)
{
	t[0]=t[1]=t[2]=0;
	d[x]=now;
	getdeep(x,0);
	return t[1]*t[2]*2+t[0]*t[0];
}

void solve(int x)
{
	ans+=calc(x,0);
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			ans-=calc(v,e[i].w);
			root=0;sum=son[v];
			getroot(v,0);
			solve(root);
		}
	}
}

int main()
{
	freopen("BZOJ2152.in","r",stdin);
	freopen("BZOJ2152.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);w%=3;
		add(u,v,w);
	}
	f[0]=sum=n;
	getroot(1,0);
	solve(root);
	int tmp=gcd(ans,n*n);
	printf("%d/%d",ans/tmp,n*n/tmp);
	
	return 0;
}
