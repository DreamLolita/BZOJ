#include<bits/stdc++.h>
using namespace std;

const int N=5e5+10;
int n,m,s,tot;
int head[N],dep[N];
int fa[22][N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

int add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void dfs(int x,int f)
{
	dep[x]=dep[f]+1;fa[0][x]=f;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		dfs(v,x);
	}
}

void get_fa()
{
	for(int j=1;j<21;++j)
		for(int i=1;i<=n;++i)
			fa[j][i]=fa[j-1][fa[j-1][i]];
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<21;++i)
		if(t&(1<<i))
			x=fa[i][x];
	for(int i=20;~i;--i)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return x==y?x:fa[0][x];
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	n=read();m=read();s=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	dfs(s,0);get_fa();
	while(m--)
	{
		int u=read(),v=read();
		printf("%d\n",LCA(u,v));
	}
	
	return 0;
}
