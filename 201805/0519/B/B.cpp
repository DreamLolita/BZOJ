#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=5e6+10;
const int M=1005;
int n,m,K,tot,begx,begy;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int head[N],val[N],mp[M][M];
LL f[N];
bool bo[M][M];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
	int v,nex,w;
	LL c;
};
Tway e[N];

void add(int u,int v,LL w,int c)
{
	e[++tot]=(Tway){v,head[u],c,w};
	head[u]=tot;
}

bool inmp(int x,int y)
{
	return x>=1 && x<=n && y>=1 && y<=m;
}

void build(int x,int y,int fa)
{
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i],kx=nx+dx[i],ky=ny+dy[i];
		if(!inmp(kx,ky))
			continue;
		if(mp[nx][ny]^mp[kx][ky])
			continue;
///		printf("%d %d %d %d %d\n",nx,ny,kx,ky,mp[nx][ny]);
		if(mp[nx][ny]==fa)
			continue;
		if(bo[kx][ky])
			add(fa,mp[nx][ny],val[mp[nx][ny]],1);
		else
		{
			add(fa,mp[nx][ny],val[mp[nx][ny]],0);
			build(kx,ky,mp[nx][ny]);
		}
	}
}

int calc(int x,int fa)
{
//	printf("%d %d\n",x,fa);
	int ret=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		int t=calc(v,x);
		if(!t && !e[i].w)
			continue;
		if(e[i].w)
			f[x]+=e[i].c,ret=1;
		else
		if(t)
			f[x]+=min(f[v],e[i].c),ret=1;
	}
	return ret;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);

	n=read();m=read();K=read();
	for(int i=1;i<=n*m/2;++i)
		val[i]=read();
	for(int i=1;i<=K;++i)
	{
		int x=read(),y=read();
		bo[x][y]=1;	
	} 
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			mp[i][j]=read();
			if(mp[i][j]==0)
				begx=i,begy=j;
		}
	if(bo[begx][begy])
	{
		puts("GG");
		return 0;
	}
	build(begx,begy,0);
	calc(0,0);
	printf("%lld\n",f[0]);

	return 0;
}

