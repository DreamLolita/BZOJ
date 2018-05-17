#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=1e5+10;
int n,K,tot=1,mx,len,ans;
int head[N],s1[N],s2[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,w,nex;	
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,1,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,1,head[v]};head[v]=tot;
}

int dfs(int x,int f)
{
	int mx1=0,mx2=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		int w=e[i].w+dfs(v,x);
		if(w>mx1)
			mx2=mx1,mx1=w,s2[x]=s1[x],s1[x]=i;
		else
		if(w>mx2)
			mx2=w,s2[x]=i;
	}
	if(mx1+mx2>len)
		len=mx1+mx2,mx=x;
	return mx1;
}

int main()
{
	freopen("LGP3629.in","r",stdin);
	freopen("LGP3629.out","w",stdout);

	n=read();K=read();ans=2*(n-1);
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	dfs(1,0);ans-=(len-1);
	if(K==2)
	{
		len=0;
		for(int i=s1[mx];i;i=s1[e[i].v]) e[i].w=e[i^1].w=-1;
		for(int i=s2[mx];i;i=s1[e[i].v]) e[i].w=e[i^1].w=-1;
		dfs(1,0);ans-=(len-1);
	}
	printf("%d\n",ans);

	return 0;
}

