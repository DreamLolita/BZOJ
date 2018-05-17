#include<bits/stdc++.h>
using namespace std;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

double getarea(Tnode O,Tnode p1,Tnode p2)
{
	double t1=p1.vx-O.vx,t2=p1.vy-O.vy;
	double t3=p2.vx-O.vx,t4=p2.vy-O.vy;
	return abs((t1*t4)-(t2*t3))/2.0;
}

double sqr(double x)
{
	return (double)x*x;
}

double getdis(Tnode x,Tnode y)
{
	return sqrt(sqr(x.vx-y.vx)+sqr(x.vy-y.vy));
}

void change(int p)
{
	beg.vx=a[p].x;beg.vy=A*a[p].x+B;
	now.vx=beg.vx+a[p].vx;now.vy=beg.vy+a[p].vy;
	double S=getarea(Tnode(0,B),beg,now);
	double h=S/(double)getdis(Tnode(0,B),beg);
	nw[p].t=h;
}

int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);

	n=read();A=read();B=read();
	for(int i=1;i<=n;++i)
	{
		a[i].x=read();a[i].vx=read();a[i].vy=read();
		change(i);
	}

	return 0;
}

