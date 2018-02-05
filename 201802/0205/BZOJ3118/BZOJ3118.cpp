#include<bits/stdc++.h>
using namespace std;

const int INF=1e9+7;
const int N=305;
const int M=1005;
const double eps=1e-7;

int n,m,tot,toe,tail,cnt;
int head[N];
double v;
double A[M][M<<2],B[M],C[M<<2];

struct Tree
{
	int v,nex,w,x,g;
};
Tree e[M<<1],q[M<<1];

struct Tmap
{
	int l,r,w,x,g;
};
Tmap ne[M];

void add_tree(int u,int v,int w,int a,int g)
{
	e[++tot]=(Tree){v,head[u],w,a,g};head[u]=tot;
	e[++tot]=(Tree){u,head[v],w,a,g};head[v]=tot;
}

void add_map(int u,int v,int w,int a,int g)
{
	ne[++toe]=(Tmap){u,v,w,a,g};
}

bool dfs(int l,int r,int x)
{
	if(l==r)	
		return true;
	for(int i=head[l];i;i=e[i].nex)
	{
		if(e[i].v!=x)
		{
			q[++tail]=e[i];
			if(dfs(e[i].v,r,l))
				return true;
			--tail;
		}
	}
	return false;
}

void build(Tmap x)
{
	tail=0;dfs(x.l,x.r,0);
	for(int i=1;i<=tail;++i)
	{
		A[q[i].g][++cnt]=1;
		A[x.g][cnt]=1;
		C[cnt]=q[i].w-x.w;
	}
}

void pivot(int x,int y)
{
	B[x]/=A[x][y];
	for(int i=1;i<=n;++i)
		if(x!=y)
			A[x][i]/=A[x][y];
	A[x][y]=1.0/A[x][y];
	for(int i=1;i<=m;++i)
		if(i!=x && fabs(A[i][y])>eps)
		{
			B[i]-=A[i][y]*B[x];
			for(int j=1;j<=n;++j)
				if(j!=y)
					A[i][j]-=A[i][y]*A[x][j];
			A[i][y]*=-A[x][y];
					
		}
	v+=B[x]*C[y];
	for(int i=1;i<=n;++i)
		if(i!=y)	
			C[i]-=C[y]*A[x][i];
	C[y]*=-A[x][y];
}

int Simplex()
{
	int i,x,y;
	while(true)
	{
		for(i=1;i<=n;++i)
			if(C[i]>eps)
				break;
		if((y=i)>n)
			return (int)v+0.5;
		double tmp=INF;
		for(int i=1;i<=m;++i)
			if(A[i][y]>eps && tmp>B[i]/A[i][y])
				tmp=B[i]/A[i][y],x=i;
		if(tmp==INF)
			return INF;
		pivot(x,y);
	}
}

int main()
{
	freopen("BZOJ3118.in","r",stdin);
	freopen("BZOJ3118.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int x,y,w,f,a,b;
		scanf("%d%d%d%d%d%d",&x,&y,&w,&f,&a,&b);
		if(f)	
			add_tree(x,y,w,b,i),B[i]=b;
		else	
			add_map(x,y,w,a,i),B[i]=a;
	}
	for(int i=1;i<=toe;++i)
		build(ne[i]);
	n=cnt;
	printf("%d\n",Simplex());
	
	return 0;
}
