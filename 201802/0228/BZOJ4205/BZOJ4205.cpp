#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=7e4+5;
const int M=4e6+5;
const int P=46;
const int K=205;
int n1,n2,ans,ind,T,prinum,tot=1;
int head[N],dep[N],q[N],pri[K];
int id[P+5][P+5];
bool bo[K];
vector<int>pr[K];

struct Tdata
{
	int x,y,z;
};
Tdata a[N],b[N];

struct Tway
{
	int v,nex,w;
};
Tway e[M];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],0};head[v]=tot;
}

void build(int t,int f)
{
	int x,y,z;
	if(!f)
		x=a[t].x,y=a[t].y,z=a[t].z;
	else 
		x=b[t].x,y=b[t].y,z=b[t].z;
	for(int i=0;i<pr[x].size();i++)
		for(int j=0;j<pr[y].size();j++)
			if(!f)
				add(t,n1+n2+id[pr[x][i]][pr[y][j]],1);
			else 
				add(n1+n2+id[pr[x][i]][pr[y][j]],n1+t,1);
	for(int i=0;i<pr[x].size();i++)
		for(int j=0;j<pr[z].size();j++)
			if(!f)
				add(t,n1+n2+id[pr[x][i]][pr[z][j]]+P*P,1);
			else
				add(n1+n2+id[pr[x][i]][pr[z][j]]+P*P,n1+t,1);
	for(int i=0;i<pr[y].size();i++)
		for(int j=0;j<pr[z].size();j++)
			if(!f)
				add(t,n1+n2+id[pr[y][i]][pr[z][j]]+P*P*2,1);
			else 
				add(n1+n2+id[pr[y][i]][pr[z][j]]+P*P*2,n1+t,1);
}

void init()
{
	for(int i=2;i<=200;++i)
	{
		if(!bo[i])
			pri[++prinum]=i;
		for(int j=1;j<=prinum && pri[j]*i<=200;++j)
		{
			bo[pri[j]*i]=1;
			if(i%pri[j]==0)
				break;
		}
	}
	for(int i=2;i<=200;++i)
		for(int j=1;j<=prinum;++j)
			if(i%pri[j]==0)
				pr[i].push_back(j);
	
	for(int i=1;i<=P;++i)
		for(int j=1;j<=P;++j)
			id[i][j]=++ind;

	scanf("%d%d",&n1,&n2);T=n1+n2+P*P*3+1;
	for(int i=1;i<=n1;++i)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	for(int i=1;i<=n2;++i)
		scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].z);
	for(int i=1;i<=n1;++i)
		add(0,i,1),build(i,0);
	for(int i=1;i<=n2;++i)
		add(n1+i,T,1),build(i,1);
}

bool bfs()
{
	int h=0,t=1;
	memset(dep,-1,sizeof(dep));
	q[h]=dep[h]=0;
	while(h!=t)
	{
		int x=q[h++];
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dep[v]==-1 && e[i].w)
			{
				dep[v]=dep[x]+1;
				q[t++]=v;
			}
		}
	}
	return ~dep[T];
}

int dfs(int x,int res)
{
	if(x==T || !res)
		return res;
	int w,used=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dep[v]==dep[x]+1)
		{
			w=dfs(v,min(e[i].w,res-used));
			e[i].w-=w;e[i^1].w+=w;used+=w;
			if(used==res)
				return res;
		}
	}
	if(!used)
		dep[x]=-1;
	return used;
}

void dinic()
{
	while(bfs())
		ans+=dfs(0,INF);
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ4205.in","r",stdin);
	freopen("BZOJ4205.out","w",stdout);
	
	init();
	dinic();
	
	return 0;
}
