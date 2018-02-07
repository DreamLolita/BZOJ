#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=205;
const int M=1e5+5;
int n,m;
int fa[N];

struct Tway
{
	int x,y,c,t;
	LL v;
};
Tway e[M];

struct Tpoint
{
	LL x,y;
};
Tpoint ans,A,B;

bool cmp(Tway X,Tway Y)
{
	return X.v<Y.v;
}

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

Tpoint Better(Tpoint X,Tpoint Y)
{
	if((X.x*X.y==Y.x*Y.y && X.x>Y.x) || X.x*X.y>Y.x*Y.y)
		return Y;
	return X;
}

Tpoint Kruscal()
{
	Tpoint O=(Tpoint){0,0};
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;++i)	
		fa[i]=i;
	int now=1;
	for(int i=1;i<=m;++i)
	{
		int fx=findf(e[i].x),fy=findf(e[i].y);
		if(fx==fy)
			continue;
		fa[fx]=fy;
		O.x+=e[i].c;O.y+=e[i].t;++now;
		if(now==n)
			break;
	}
	ans=Better(ans,O);
	return O;
}

LL cross(Tpoint a,Tpoint b,Tpoint c)
{
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

void solve(Tpoint X,Tpoint Y)
{
	LL tx=Y.x-X.x,ty=X.y-Y.y;
	for(int i=1;i<=m;++i)
		e[i].v=1ll*e[i].c*ty+1ll*e[i].t*tx;
	Tpoint O=Kruscal();
	if(cross(O,X,Y)>=0)
		return;
	solve(X,O);
	solve(O,Y);
}

int main()
{
//	freopen("BZOJ2395.in","r",stdin);
//	freopen("BZOJ2395.out","w",stdout);
	
	ans.x=ans.y=INF;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].c,&e[i].t);
		++e[i].x;++e[i].y;e[i].v=e[i].c;
	}
	A=Kruscal();
	for(int i=1;i<=m;++i)
		e[i].v=e[i].t;
	B=Kruscal();
	solve(A,B);
	printf("%lld %lld\n",ans.x,ans.y);
	
	return 0;
}
