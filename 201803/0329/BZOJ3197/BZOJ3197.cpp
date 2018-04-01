#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=1410;
const int M=4e5+10;

int n,tot,tott,can,root,rtsiz,p,T,mi,ret,IP;
int siz[N],son[N],a[N],b[N],headt[N],head[N];
int dis[N],pre[N],rt[5];
int f[N][N];
bool inq[N];
LL hs[N],r[N];
queue<int>q;

struct Tway
{
	int u,v,nex,w,c;
};
Tway et[N],e[M];

void addtree(int u,int v)
{
	et[++tott]=(Tway){u,v,headt[u],0,0};headt[u]=tott;
	et[++tott]=(Tway){v,u,headt[v],0,0};headt[v]=tott;
}

void getroot(int x,int fa)
{
	siz[x]=1;
	for(int i=headt[x];i;i=et[i].nex)
	{
		int v=et[i].v;
		if(v!=fa)
		{
			getroot(v,x);
			siz[x]+=siz[v];
			son[x]=max(son[x],siz[v]);
		}
	}
	son[x]=max(son[x],n-siz[x]);
	if(son[root]==son[x])
		rt[++rtsiz]=x;
	else
	if(son[root]>son[x])
		root=x,rt[rtsiz=1]=x;
}

void gethash(int x,int fa)
{
	LL sum=0;siz[x]=1;
	for(int i=headt[x];i;i=et[i].nex)
	{
		int v=et[i].v;
		if(v!=fa && can!=i && can!=(i^1))
		{
			gethash(v,x);
			sum+=hs[v];
			siz[x]+=siz[v];
		}
	}
	hs[x]=(1ll*sum*p)^r[siz[x]];
}

void init()
{
	srand(19260817);tot=tott=1;p=233;
	scanf("%d",&n);T=2*n+2;
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addtree(u,v);
	}
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	son[0]=INF;getroot(1,0);
	if(rtsiz==2)
	{
		for(int i=headt[rt[1]];i;i=et[i].nex)
			if(et[i].v==rt[2])
			{
				can=i;
				break;			
			}
		root=++n;
		a[n]=b[n]=0;
		addtree(n,rt[1]);addtree(n,rt[2]);
	}
	for(int i=1;i<=n;++i)
		r[i]=((rand()%32766)<<15ll)+(rand()%32766);
	memset(f,127/3,sizeof(f));IP=f[0][0];
}


void add(int u,int v,int w,int c)
{
	e[++tot]=(Tway){u,v,head[u],w,c};head[u]=tot;
	e[++tot]=(Tway){v,u,head[v],0,-c};head[v]=tot;
}

bool spfa()
{
	memset(dis,127/3,sizeof(dis));
	dis[0]=0;inq[0]=true;q.push(0);
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=false;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dis[u]+e[i].c<dis[v])
			{
				dis[v]=dis[u]+e[i].c;
				pre[v]=i;
				if(!inq[v])
				{
					inq[v]=true;
					q.push(v);
				}
			}
		}
	}
	return dis[T]!=IP;
}

void mcfx()
{
	ret=0;
	while(spfa())
	{
		int t=INF;
		for(int i=pre[T];i;i=pre[e[i].u])
			t=min(t,e[i].w);
		
		for(int i=pre[T];i;i=pre[e[i].u])
		{
			e[i].w-=t;e[i^1].w+=t;
			ret+=t*e[i].c;
		}
	}
}

/*void debug()
{
	for(int i=1;i<=T;++i)
	{
		printf("%d:\n",i);
		for(int j=head[i];j;j=e[j].nex)
			printf("%d %d %d %d\n",e[j].v,e[j].nex,e[j].w,e[j].c);
	}
	printf("\n");
}*/

void dp(int x,int fa)
{
	for(int i=headt[x];i;i=et[i].nex)
	{
		int v=et[i].v;
		if(v!=fa && can!=i && can!=(i^1))
			dp(v,x);
	}
	for(int i=1;i<=n;++i)
	{
		if(hs[i]!=hs[x])
			continue;
		memset(head,0,sizeof(head));tot=1;
		for(int j=headt[i];j;j=et[j].nex)
		{
			int v=et[j].v;
			add(v+n,T,1,0);
		}
		for(int j=headt[x];j;j=et[j].nex)
		{
			int v=et[j].v;
			if(v!=fa && can!=j && can!=(j^1))
			{
				add(0,v,1,0);
				for(int k=headt[i];k;k=et[k].nex)
				{
					int vs=et[k].v;
					if(hs[v]==hs[vs])
						add(v,vs+n,1,f[v][vs]);
				}
			}
		}
		mcfx();
//		debug();
		f[x][i]=ret+(a[x]!=b[i]);
	}
}

void solve()
{
	gethash(root,0);
	dp(root,0);
	printf("%d\n",f[root][root]);
}

int main()
{
	freopen("BZOJ3197.in","r",stdin);
	freopen("BZOJ3197.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
