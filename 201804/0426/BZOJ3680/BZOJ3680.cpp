#include<bits/stdc++.h>
using namespace std;

const double eps=1e-3;
const double bas=0.991;
const int N=1e4+10;
int n;
double mians=(double)1e100;

struct Tnode
{
	double x,y,g;
};
Tnode ansp,p[N];

double sqr(double x)
{
	return (double)x*x;
}

double getdis(Tnode A,Tnode B)
{
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

double check(Tnode now)
{
	double ret=0;
	for(int i=1;i<=n;++i)
		ret+=p[i].g*getdis(now,p[i]);
	if(ret<mians)
	{
		ansp=now;
		mians=ret;
	}
	return ret;
}

double rnd()
{
	return rand()%1000/1000.0;
}

void solve(double tem)
{
	Tnode t1=ansp,t2;
	while(tem>eps)
	{
		t2.x=t1.x+tem*(rnd()*2-1);
		t2.y=t1.y+tem*(rnd()*2-1);
		double tmp=check(t1)-check(t2);
		if(tmp>0 || exp(tmp/tem)>rnd())
			t1=t2;
		tem*=bas;
//printf("%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n",ansp.x,ansp.y,t1.x,t1.y,mians,t2.x,t2.y);
	}
	for(int i=1;i<=1000;++i)
	{
		t2.x=ansp.x+tem*(rnd()*2-1);
		t2.y=ansp.y+tem*(rnd()*2-1);
		check(t2);
	}
}

int main()
{
	freopen("BZOJ3680.in","r",stdin);
	freopen("BZOJ3680.out","w",stdout);
	
	srand(20011006);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].g);
		ansp.x+=p[i].x;ansp.y+=p[i].y;
	}
	ansp.x/=n;ansp.y/=n;
	solve(1e6);
	printf("%.3lf %.3lf\n",ansp.x,ansp.y);
	
	return 0;
}
