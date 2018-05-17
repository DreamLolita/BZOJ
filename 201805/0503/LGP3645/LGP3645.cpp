#include<bits/stdc++.h>
#define id(x,y) (x*n+y)
using namespace std;

const int INF=1061109567;
const int N=3e4+10;
const int M=N*505;
int n,m,tot,S,T,lim;
int head[M],dis[M];
bool vis[M];
queue<int>q;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,nex,w;
};
Tway e[M<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};
	head[u]=tot;
}

void spfa()
{
	memset(vis,0,sizeof(vis));memset(dis,127/2,sizeof(dis));
	q.push(S);dis[S]=0;vis[S]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[u]+e[i].w<dis[v])
			{
				dis[v]=dis[u]+e[i].w;
				if(!vis[v])
					vis[v]=1,q.push(v);
			}
		}
	}
	if(dis[T]==INF)
		dis[T]=-1;
	printf("%d\n",dis[T]);
}

int main()
{
	freopen("LGP3645.in","r",stdin);
	freopen("LGP3645.out","w",stdout);

	n=read();m=read();lim=min((int)sqrt(n),100);
	for(int i=1;i<=lim;++i)
		for(int j=1;j<=n;++j)
			add(id(i,j),j,0);
	for(int i=1;i<=lim;++i)
		for(int j=1;j<=n-i;++j)
			add(id(i,j),id(i,i+j),1),add(id(i,i+j),id(i,j),1);
	for(int i=1;i<=m;++i)
	{
		int bi=read()+1,pi=read();
		if(i==1) S=bi;
		if(i==2) T=bi;
		if(pi<=lim)
			add(bi,id(pi,bi),0);
		else
		{
			for(int j=1;bi+j*pi<=n;++j)
				add(bi,bi+j*pi,j);
			for(int j=1;bi-j*pi>=1;++j)
				add(bi,bi-j*pi,j);
		}
	}
	spfa();

	return 0;
}

