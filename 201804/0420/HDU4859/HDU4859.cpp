#include<bits/stdc++.h>
using namespace std;

const int INF=1e8;
const int K=105;
const int N=3005;
const int M=5e5+10;
int n,m,S,T,tot,ans;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int head[N],dep[N],mp[K][K];
char s[K];
queue<int>q;

int read()
{
	int ret=0,f=1;char c='.';
	while(c<'0' || c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){ret=(ret<<3)+(ret<<1)+c-'0';c=getchar();}
	return ret*f;
}

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

bool inmp(int x,int y)
{
	return x>=0 && x<=n+1 && y>=0 && y<=m+1;
}

void init()
{
	n=read();m=read();memset(mp,0,sizeof(mp));
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;++j)
			if(s[j]=='.') 
				mp[i][j]=1;
			else
			if(s[j]=='E')
				mp[i][j]=2;		
	}
	tot=1;memset(head,0,sizeof(head));
	S=0;T=(n+2)*(m+2)+1;
}

void connect()
{
	for(int i=0;i<=n+1;++i)
	{
		for(int j=0;j<=m+1;++j)
		{
			if((i+j)&1)
			{
				if(!mp[i][j])
					add(i*(m+2)+j+1,T,INF);
				else
				if(mp[i][j]&1)
					add(S,i*(m+2)+j+1,INF);
			}
			else
			{
				if(!mp[i][j])
					add(S,i*(m+2)+j+1,INF);
				else
				if(mp[i][j]&1)
					add(i*(m+2)+j+1,T,INF);
			}
			for(int k=0;k<4;++k)
			{
				int x=i+dx[k],y=j+dy[k];
				if(inmp(x,y))
					add(i*(m+2)+j+1,x*(m+2)+y+1,1);
			}
		}
	}
}

bool bfs()
{
	memset(dep,-1,sizeof(dep));
	q.push(S);dep[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(e[i].w && dep[v]==-1)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return ~dep[T];
}

int dfs(int u,int f)
{
	if(u==T)
		return f;
	int w,used=0;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(dep[v]!=dep[u]+1)
			continue;
		w=dfs(v,min(f-used,e[i].w));
		e[i].w-=w;e[i^1].w+=w;used+=w;
		if(used==f)
			return f;
	}
	if(!used)
		dep[u]=-1;
	return used;
}

void solve(int now)
{
	ans=0;
	while(bfs())
		ans+=dfs(S,INF);
	printf("Case %d: %d\n",now,(n+1)*(m+2)+(n+2)*(m+1)-ans);
}

int main()
{
	freopen("HDU4859.in","r",stdin);
	freopen("HDU4859.out","w",stdout);
	
	int cas=read();
	for(int i=1;i<=cas;++i)
	{
		init();
		connect();
		solve(i);
	}
	
	return 0;
}
