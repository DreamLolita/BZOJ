#include<cstdio>
#include<string>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;

const int INF=1e9;
const int N=6e6+10;
int s,n,cnt,tot,Tot,S,T;
int head[N],Head[N],dis[N],du[N];
bool vis[N];
char s1[55],s2[55];
string str;
queue<int>p,tp;
map<string,int>mp;

struct Tway
{
	int v,nex,c,t;
};
Tway e[N<<1],E[N<<1];

void add(int u,int v,int c,int t)
{
	e[++tot]=(Tway){v,head[u],c,t};head[u]=tot;
}

void Add(int u,int v,int c,int t)
{
	E[++Tot]=(Tway){v,Head[u],c,t};Head[u]=Tot;
}

struct Tnode
{
	int id,d;
	Tnode(){}
	Tnode(int dd,int idd){
		d=dd;id=idd;
	}
	friend bool operator > (Tnode A,Tnode B){
		return A.d<B.d;
	}
};
queue<Tnode>q;

void init()
{
	scanf("%d%d",&s,&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s1);str=s1;
		mp[str]=i;
	}
	cnt=n;
	for(int i=1,x;i<=s;++i)
	{
		scanf("%d",&x);
		for(int j=1;j<=x;++j)
		{
			scanf("%s",s1);str=s1;
			int u=mp[str];
			add(cnt+j,u,0,0);add(u,cnt+j,1,0);
			add(cnt+j+x,u,0,0);add(u,cnt+j+x,1,0);
		}
		cnt+=2*x;
		for(int j=2;j<=x;++j)
			add(cnt-j-x+1,cnt-j-x+2,0,1),add(cnt-j+2,cnt-j+1,0,1);
	}
	scanf("%s%s",s1,s2);
	str=s1;S=mp[s1];str=s2;T=mp[s2];
//	printf("%d %d\n",S,T);
	
/*	for(int i=1;i<=cnt;++i)
	{
		printf("%d:\n",i);
		for(int j=head[i];j;j=e[j].nex)
		{
			printf("%d ",e[j].v);
		}
		printf("\n");
	}*/
//	exit(0);
}

void dij()
{
	for(int i=1;i<=cnt;++i)
		dis[i]=INF;
	dis[S]=0;vis[S]=1;
	q.push(Tnode(0,S));
	for(int i=1;i<=cnt;++i)
	{
		Tnode t=q.front();q.pop();
		int u=t.id;
//		printf("%d %d\n",t.id,t.d);
		for(int j=head[u];j;j=e[j].nex)
		{
			int v=e[j].v;
			if(!vis[v] && dis[u]+e[j].c<dis[v])
			{
				dis[v]=dis[u]+e[j].c;vis[v]=1;
				q.push(Tnode(dis[v],v));
			}
		}
	}
	while(!q.empty())
		q.pop();
	if(dis[T]>=INF)
	{
		printf("-1\n0\n");
		exit(0);
	}
	printf("%d\n",dis[T]);
}

void dp()
{
//	printf("\n\ntotally:\n");
//	for(int i=1;i<=cnt;++i)
//		printf("%d\n",dis[i]);
//	printf("\n\n");
	
	for(int i=1;i<=cnt;++i)
	{
		for(int j=head[i];j;j=e[j].nex)
		{
			int v=e[j].v;
			if(dis[i]+e[j].c==dis[v])
			{
				Add(i,v,e[j].c,e[j].t);
				du[v]++;
			}
		}
	}
//	printf("\n\ntotally:\n");
//	for(int i=1;i<=cnt;++i)
//		printf("%d\n",du[i]);
//	printf("\n\n");
//	printf("ways:%d %d\n",tot,Tot);


	for(int i=1;i<=cnt;++i)
		dis[i]=-INF;
	for(int i=1;i<=cnt;++i)
		if(!du[i])
			p.push(i),tp.push(i);
	while(!p.empty())
	{
		int u=p.front();p.pop();
//		printf("%d\n",u);
		for(int i=Head[u];i;i=E[i].nex)
		{
			int v=E[i].v;du[v]--;
			if(du[v]==0)
				p.push(v),tp.push(v);
		}
	}
	dis[S]=0;
	while(!tp.empty())
	{
		int u=tp.front();tp.pop();
		for(int i=Head[u];i;i=E[i].nex)
		{
			int v=E[i].v;
			dis[v]=max(dis[v],dis[u]+E[i].t);
		}
	}
	printf("%d\n",dis[T]);
}

int main()
{
	freopen("BZOJ4489.in","r",stdin);
	freopen("BZOJ4489.out","w",stdout);
	
	init();
	dij();
	dp();
	
	return 0;
}
