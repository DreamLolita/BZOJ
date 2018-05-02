#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1e4+10;
const int M=1e5+10;
int S,T,n,m,tot=1,fs,cst;
int head[N],dis[N],cur[N];
int inq[N],ins[N],from[M];
queue<int>q;

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int u,v,nex,w,c; 
};
Tway e[M];

void add(int u,int v,int w,int c)
{
	e[++tot]=(Tway){u,v,head[u],w,c};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v],0,-c};head[v]=tot;
}

bool spfa()
{
	for(int i=0;i<=n+1;++i)
		dis[i]=INF,inq[i]=false;
	while(!q.empty())
		q.pop();
	dis[S]=0;q.push(S);inq[S]=1;
	while(!q.empty())
	{
		int now=q.front();q.pop();inq[now]=false;
		for(int i=head[now];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && e[i].c+dis[now]<dis[v])
			{
				dis[v]=e[i].c+dis[now];from[v]=i;
				if(!inq[v])
				{
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[T]!=INF;
}

/*void mcfx()
{
	int t=INF;
	for(int i=from[T];i;i=from[e[i].u])
		t=min(t,e[i].w);
	for(int i=from[T];i;i=from[e[i].u])
	{
		cst+=t*e[i].c;
		e[i].w-=t;e[i^1].w+=t;
	}
	fs+=t;
}*/


int dfs(int x,int f) 
{
    if(x==T) 
		return f;
    int ret=0,now=0;ins[x]=1;
    for(int &i=cur[x];i;i=e[i].nex)
    {
    	int v=e[i].v;
    	if(e[i].w && !ins[v] && dis[v]==dis[x]+e[i].c)
    	{
    		now=dfs(v,min(f,e[i].w));
    		ret+=now;f-=now;cst+=e[i].c*now;
    		e[i].w-=now;e[i^1].w+=now;
    		if(!f)
    		{
    			ins[x]=0;
    			return ret;
			}
		}
	}
	if(!ret)
		dis[x]=INF;
	ins[x]=0;
	return ret;
}

int main()
{
	freopen("LGP3381.in","r",stdin);
	freopen("LGP3381.out","w",stdout);
	
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read(),w=read(),c=read();
		add(u,v,w,c);
	}
	while(spfa())
	{
		memcpy(cur,head,sizeof(head));
		fs+=dfs(S,INF);
	}
	printf("%d %d\n",fs,cst);
	
	return 0;
}
