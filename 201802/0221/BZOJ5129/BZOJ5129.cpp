#include<bits/stdc++.h>
#define P pair<LL,int>
using namespace std;

typedef long long LL;
const int N=3e5+10;
const int M=5e6+10;
int n,S,all,now,cur,tot=1,TOT;
int f[N],son[N],cost[N],lim[N];
int st[N],en[N],vis[N],head[N],ok[N<<1];
int HEAD[N],q[M][2];
LL dis[N];
priority_queue<P,vector<P>,greater<P> >Q;

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1],E[M];

inline int read()
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

inline void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u],0};
	head[u]=tot;ok[tot]=1;
}

inline void ADD(int u,int v,int w)
{
	E[++TOT]=(Tway){v,HEAD[u],w};
	HEAD[u]=TOT;
}

inline void findroot(int x,int y)
{
	son[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!ok[i] || v==y)
			continue;
		findroot(v,x);
		son[x]+=son[v];
		if(son[v]>f[x])
			f[x]=son[v];
	}
	if(all-son[x]>f[x])
		f[x]=all-son[x];
	if(f[x]<f[now])
		now=x;
}

inline void bfs(int s)
{
	vis[s]=s;
	q[++cur][0]=s;q[cur][1]=0;
	int h=cur;
	while(h<=cur)
	{
		int x=q[h][0],y=q[h++][1]+1;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(!ok[i] || vis[v]==s)
				continue;
			vis[v]=s;
			q[++cur][0]=v;q[cur][1]=y;
		}
	}
}

inline void solve(int x)
{
	st[x]=cur+1;
	bfs(x);
	en[x]=cur;
	for(int i=st[x];i<=cur;++i)
		ADD(q[i][0],x,q[i][1]);
	for(int i=head[x];i;i=e[i].nex)
		if(ok[i])
		{
			int v=e[i].v;
			ok[i^1]=0;
			f[0]=all=son[v];
			findroot(v,now=0);
			solve(now);
		}
}

inline void ext(int x,LL y)
{
	if(vis[x])
		return;
	vis[x]=1;dis[x]=y;
	Q.push((P){y+cost[x],x});
}

inline void gooo(int x,int limit,LL y)
{
	int &h=st[x],t=en[x];
	while(h<=t)
	{
		if(q[h][1]>limit)
			break;
		ext(q[h++][0],y);
	}
}

int main()
{
	freopen("BZOJ5129.in","r",stdin);
	freopen("BZOJ5129.out","w",stdout);
	
	n=read();S=read();
	for(int i=1;i<n;++i)
	{
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;++i)
		lim[i]=read(),cost[i]=read();
	f[0]=all=n;
	findroot(1,now=0);solve(now);
	
	for(int i=1;i<=n;++i)
		vis[i]=0;
	ext(S,0);
	while(!Q.empty())
	{
		P t=Q.top();Q.pop();
		for(int i=HEAD[t.second];i;i=E[i].nex)
			gooo(E[i].v,lim[t.second]-E[i].w,t.first);
	}
	for(int i=1;i<=n;++i)
		printf("%lld\n",dis[i]);
	
	return 0;
}
