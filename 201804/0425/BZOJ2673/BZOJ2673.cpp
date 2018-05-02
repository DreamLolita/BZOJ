#include<bits/stdc++.h>
#define id(x,y) (x*2+y-1)
using namespace std;

const int INF=1e9;
const int N=105;
const int M=N*N*8;
int n,A,B,ans,fs,cst,sum,ini,tot,S,T;
int sx[N],sy[N],head[N];
int dis[N],inq[N],ins[N],from[M];
char mp[N][N];
queue<int>q;

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
	for(int i=0;i<=T;++i)
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
				dis[v]=e[i].c+dis[now];
//				from[v]=i;
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

/*
void mcfx()
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
    for(int i=head[x];i;i=e[i].nex)
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

void mcfx()
{
	int tmp;
	while(tmp=dfs(S,INF))
		fs+=tmp;
}

void init()
{
	memset(sx,0,sizeof(sx));memset(sy,0,sizeof(sy));
	ans=-1;tot=1;ini=sum=0;

	for(int i=1;i<=n;++i)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=n;++j)
		{
			if(mp[i][j]!='/')
				++sx[i],++sy[j],++sum;
			ini+=mp[i][j]=='C';
		}
	}
}

void rebuild(int now)
{
	memset(head,0,sizeof(head));tot=1;S=n*2+1;T=S+1;
	for(int i=1;i<=n;++i)
	{
		add(S,id(i,0),sx[i],0);
		add(id(i,0),id(i,1),now,0);
		add(id(i,1),T,sy[i],0);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(mp[i][j]=='.')
				add(id(i,0),id(j,1),1,1);
}

int calc(int now)
{
	rebuild(now);
//printf("edges:%d\n",tot);
	fs=0;cst=0;
	while(spfa())
		mcfx();
//	printf("%d %d\n",fs,cst);
	if(fs!=sum)
		return -1;
	int used=sum-cst;
	return used*A>=now*B?used-ini:-1;
}

void solve(int cas)
{
	for(int i=0;i<=n;++i)
		ans=max(ans,calc(i));
	printf("Case %d: ",cas);
	if(!~ans)
		puts("impossible");
	else
		printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ2673.in","r",stdin);
	freopen("BZOJ2673.out","w",stdout);
	
	for(int cas=1;;++cas)
	{
		scanf("%d%d%d",&n,&A,&B);
		if(!n && !A && !B)
			break;
		init();
		solve(cas);
	}
	
	
	return 0;
}
