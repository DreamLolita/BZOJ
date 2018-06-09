#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef double db;
typedef long double ldb;
typedef pair<int,int> pii;
const ldb eps=1e-7;
const int MX=4e6+10;
int n,L;
ldb R;

struct Tnode
{
	ldb x,y;
};
Tnode a[15];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

ldb sqr(ldb x)
{
	return (ldb)x*x;
}

ldb dis(ldb lx,ldb ly,ldb rx,ldb ry)
{
	return (ldb)sqrt(sqr(lx-rx)+sqr(ly-ry));
}

void check(ldb x,ldb y)
{
	bool flag=0;
	for(int i=1;i<=n;++i)
	{
		double tmp=(double)dis(x,y,a[i].x,a[i].y);
//printf("%lf %lf\n",(double)(tmp+eps),(double)R);
		if(dis(x,y,a[i].x,a[i].y)<R+eps)
		{
			flag=1;
			break;
		}
	}
	if(!flag)
	{
		printf("%0.6lf %0.6lf\n",(double)x,(double)y);
		exit(0);
	}
}

ldb rnd()
{
	ldb x=rand()%(L*1000);x=x*1.0/1000;
	return x;
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);

	srand(998244353);
	n=read();L=read();R=(ldb)L/(ldb)n;
	for(int i=1;i<=n;++i) 
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		a[i].x=x;a[i].y=y;
	}

	if(n==1)
	{
		check(0,0);check(L,0);
		check(0,L);check(L,L);
		puts("GG");
		return 0;
	}
	while(true)
	{
		ldb x=rnd(),y=rnd();
		check(x,y);
	}

	return 0;
}

