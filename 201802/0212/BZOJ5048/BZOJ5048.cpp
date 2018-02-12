#include<bits/stdc++.h>
using namespace std;

const int N=2005;
int n,m,q,e,ans;
int fa[4][N][N];
bool bo[N][N];

struct Tpoint
{
	int x,y;
};
Tpoint a[N<<3];

int find1(int opt,int x,int y)
{
	return fa[opt][x][y]==x?x:fa[opt][x][y]=find1(opt,fa[opt][x][y],y);
}

int find2(int opt,int x,int y)
{
	return fa[opt][x][y]==y?y:fa[opt][x][y]=find2(opt,x,fa[opt][x][y]);
}

void dele(int x,int y)
{
	if(bo[x][y])
		return;
	++ans;
	bo[x][y]=false;
	fa[0][x][y]--;fa[1][x][y]++;
	fa[2][x][y]--;fa[3][x][y]++;
}

void UP(int k)
{
	for(int i=1;i<=e;++i)
	{
		int x=a[i].x,y=a[i].y;
		a[i].x-=k;
		if(y<1 || y>m || x<1)
			continue;
		x=min(x,n);
		while(true)
		{
			x=find1(0,x,y);
			if(x<1 || x<a[i].x)
				break;
			dele(x,y);
		}
	}
}

void DOWN(int k)
{
	for(int i=1;i<=e;++i)
	{
		int x=a[i].x,y=a[i].y;
		a[i].x+=k;
		if(y<1 || y>m || x>n)
			continue;
		x=max(x,1);
		while(true)
		{
			x=find1(1,x,y);
			if(x>n || x>a[i].x)
				break;
			dele(x,y);
		}
	}
}

void LEFT(int k)
{
	for(int i=1;i<=e;++i)
	{
		int x=a[i].x,y=a[i].y;
		a[i].y-=k;
		if(x<1 || x>n || y<1)
			continue;
		y=min(y,m);
		while(true)
		{
			y=find2(2,x,y);
			if(y<1 || y<a[i].y)
				break;
			dele(x,y);
		}
	}
}

void RIGHT(int k)
{
	for(int i=1;i<=e;++i)
	{
		int x=a[i].x,y=a[i].y;
		a[i].y+=k;
		if(x<1 || x>n || y>m)
			continue;
		y=max(y,1);
		while(true)
		{
			y=find2(3,x,y);
			if(y>m || y>a[i].y)
				break;
			dele(x,y);
		}
	}
}

int main()
{
	freopen("BZOJ5048.in","r",stdin);
	freopen("BZOJ5048.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&e,&q);
	for(int i=0;i<=n+1;++i)
		for(int j=0;j<=m+1;++j)
			fa[0][i][j]=fa[1][i][j]=i,fa[2][i][j]=fa[3][i][j]=j;
			
	for(int i=1;i<=e;++i)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		dele(a[i].x,a[i].y);
	}
	
	for(int i=1;i<=n;++i)
		a[++e]={i,0},a[++e]={i,m+1};
	for(int i=1;i<=m;++i)
		a[++e]={0,i},a[++e]={n+1,i};

	char opt[5];int k;
	while(q--)
	{
		scanf("%s%d",opt,&k);
		ans=0;
		if(opt[0]=='U')	
			DOWN(k);
		else
		if(opt[0]=='D')
			UP(k);
		else
		if(opt[0]=='L')
			RIGHT(k);
		else
			LEFT(k);
		printf("%d\n",ans);
	}
	
	return 0;
}
