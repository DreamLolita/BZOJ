#include<bits/stdc++.h>
using namespace std;

const int INF=1061109567;
const int N=1005;
const int M=1e5+10;
int n,m,S,T,tot,cs,ans;
int from[N],head[N],dis[N],t[61][10],cur[N];
bool inq[N],ins[N];
queue<int>q;

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int u,v,nex,w,c;
	Tway(){}
	Tway(int uu,int vv,int nn,int ww,int cc):u(uu),v(vv),nex(nn),w(ww),c(cc){}
};
Tway e[M];

void add(int u,int v,int w,int c)
{
	e[++tot]=Tway(u,v,head[u],w,c);head[u]=tot;
	e[++tot]=Tway(v,u,head[v],0,-c);head[v]=tot;
}

bool spfa()
{
	memset(dis,127/2,sizeof(dis));memset(inq,0,sizeof(inq));
	q.push(S);inq[S]=1;dis[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dis[v]>dis[u]+e[i].c)
			{
				dis[v]=dis[u]+e[i].c;from[v]=i;
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

int dfs(int x,int f)
{
	if(x==T)
		return f;
	int used=0,w=0;ins[x]=1;
	for(int &i=cur[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].w && dis[x]+e[i].c==dis[v] && !ins[v])
		{
			w=dfs(v,min(e[i].w,f-used));
			used+=w;cs+=e[i].c*w;
			e[i].w-=w;e[i^1].w+=w;
			if(used==f)
			{
				ins[x]=0;
				return used;
			}	
		}
	}
	ins[x]=0;
	return used;
}

/*void mcf()
{
    int w=INF;
    for(int i=from[T];i;i=from[e[i].u])
        w=min(w,e[i].w);
    for(int i=from[T];i;i=from[e[i].u])
    	{e[i].w-=w;e[i^1].w+=w;ans+=e[i].c*w;}
}*/

int main()
{
	freopen("BZOJ1070.in","r",stdin);
	freopen("BZOJ1070.out","w",stdout);
	
	n=read();m=read();S=0;T=n*m+m+1;tot=1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			t[i][j]=read();
	for(int i=1;i<=n*m;++i)
		add(S,i,1,0);
	for(int i=n*m+1;i<=n*m+m;++i)
		add(i,T,1,0);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=m;++k)
				add((i-1)*m+j,n*m+k,1,t[k][i]*j);
	while(spfa())
	{
		memcpy(cur,head,sizeof(head));
		ans+=dfs(S,INF);
	}
	printf("%0.2lf",(double)cs/m);
	
/*	while(spfa())
		mcf();
	printf("%0.2lf",(double)ans/m);*/
	
	return 0;
}
