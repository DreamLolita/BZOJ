#include<bits/stdc++.h>
using namespace std;

const int M=6e5+5;
const int N=505;
const int L=10;
const int INF=1e9+7;
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int n,w,h,top,ans; 
int sum[M];
int f[L][L][N][N],val[N*N],way[N][N][4],tim;
char mp[N][N];
bool bo[N][N];

struct Tnode
{
	int x,y;
};
Tnode p[M+5],q[N*N+5],gol[N][N][4],a[L];

inline bool check(int x,int y)
{
	return (x<=0 || x>h || y<=0 || y>w || mp[x][y]=='x');
}

inline Tnode dfs(int x,int y,int k)
{
	Tnode t;
	if(way[x][y][k]==tim)
	{
		t.x=0;t.y=-1;
		return t;
	}
	way[x][y][k]=tim;
	if(gol[x][y][k].y)
		return gol[x][y][k];
	int w=k;
	if(mp[x][y]=='A')	w=(k+1)%4;
	if(mp[x][y]=='C')	w=(k+3)%4;
	
	int nx=x+dx[w],ny=y+dy[w];
	if(check(nx,ny))
	{
		t.x=x;t.y=y;
		return gol[x][y][k]=t;
	}
	else
		return gol[x][y][k]=dfs(nx,ny,w);
}

inline void spfa(int l,int r)
{
	memset(sum,0,sizeof(sum));
	memset(bo,false,sizeof(bo));
	int mn=INF,mx=-INF;
	for(int i=1;i<=top;++i)
	{
		sum[val[i]]++;
		mn=min(mn,val[i]);mx=max(mx,val[i]);
		bo[q[i].x][q[i].y]=true;
	}
	for(int i=mn+1;i<=mx;++i)
		sum[i]+=sum[i-1];
	for(int i=1;i<=top;++i)
		p[sum[val[i]]--]=q[i];
	for(int i=1;i<=top;++i)
		q[i]=p[top-i+1];
	
	int head=0,tail=0,now;
	Tnode u,v;
	while(top || head!=tail)
	{
		now=head%M+1;
		if(head==tail || (top && f[l][r][q[top].x][q[top].y]<f[l][r][p[now].x][p[now].y]) )
			u=q[top--];
		else
			head=now,u=p[head];
		bo[u.x][u.y]=false;
		for(int i=0;i<4;++i)
		{
			v=gol[u.x][u.y][i];
			if(v.x && f[l][r][u.x][u.y]+1<f[l][r][v.x][v.y])
			{
				f[l][r][v.x][v.y]=f[l][r][u.x][u.y]+1;
				if(!bo[v.x][v.y])
				{
					bo[v.x][v.y]=true;
					tail=tail%M+1;
					p[tail]=v;
				}
			}
		}
	}
}

int main()
{
//	freopen("BZOJ3205.in","r",stdin);
//	freopen("BZOJ3205.out","w",stdout);
	
	memset(f,0x3f,sizeof(f));
	scanf("%d%d%d",&n,&w,&h);
	for(int i=1;i<=h;++i)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=w;++j)
			if(mp[i][j]>='1' && mp[i][j]<='9')
			{
				int t=mp[i][j]-'0';
				a[t].x=i;a[t].y=j;f[t][t][i][j]=0;
			}
	}
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			if(mp[i][j]!='x')
				for(int k=0;k<4;++k)
				{
					++tim;
					gol[i][j][k]=dfs(i,j,k);
				}
	for(int i=1;i<=n;++i)
		q[top=1]=a[i],val[1]=0,spfa(i,i);
	for(int i=n-1;i;--i)
		for(int j=i+1;j<=n;++j)
		{
			for(int k=i;k<j;++k)
				for(int x=1;x<=h;++x)
					for(int y=1;y<=w;++y)
						f[i][j][x][y]=min(f[i][j][x][y],f[i][k][x][y]+f[k+1][j][x][y]);
			top=0;
			for(int x=1;x<=h;++x)
				for(int y=1;y<=w;++y)
					if(f[i][j][x][y]<INF)
					{
						q[++top].x=x;q[top].y=y;
						val[top]=f[i][j][x][y];
					}
			spfa(i,j);
		}
	ans=INF;
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			ans=min(ans,f[1][n][i][j]);
	printf("%d\n",ans<INF?ans:-1);
	return 0;
}
