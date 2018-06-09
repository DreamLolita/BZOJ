#include<bits/stdc++.h>
#define id(x) ((x+1))%n
using namespace std;

typedef long long LL;
typedef long double ldb;
const ldb pi=acos(-1);
const ldb eps=1e-10;
const int N=1e4+10;
int n,q,p1,p2;
ldb gx,gy,angle;
ldb ang[N],dis[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tpoint
{
	ldb x,y;
	Tpoint(){}
	Tpoint(ldb xx,ldb yy){x=xx;y=yy;}
	Tpoint operator -(const Tpoint&A)const{
		return Tpoint(x-A.x,y-A.y);
	}
};
Tpoint a[N],g,top,nex;

ldb cross(Tpoint A,Tpoint B)
{
	return A.x*B.y-A.y*B.x;
}

Tpoint getpoint(int idx)
{
	return Tpoint(g.x+dis[idx]*cos(angle+ang[idx]),g.y+dis[idx]*sin(angle+ang[idx]));
}

ldb sqr(ldb x)
{
	return x*x;
}

ldb getdis(Tpoint A,Tpoint B)
{
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

Tpoint getG()
{
	ldb S=0,tx=0,ty=0;
	for(int i=0;i<n;++i)
	{
		ldb tmp=cross(a[i],a[id(i)]);S+=tmp;
//		printf("%lf\n",(double)tmp);
		tx+=(a[i].x+a[id(i)].x)*tmp;
		ty+=(a[i].y+a[id(i)].y)*tmp;
	}
	S/=2.0;tx/=6.0*S;ty/=6.0*S;
	return Tpoint(tx,ty);
}

void getds()
{
	for(int i=0;i<n;++i)
	{
		dis[i]=getdis(a[i],g);
		ang[i]=atan2(a[i].y-g.y,a[i].x-g.x);
		if(ang[i]<0)
			ang[i]+=2*pi;
	}
}

int main()
{
	freopen("CF975E.in","r",stdin);
	freopen("CF975E.out","w",stdout);

	n=read();q=read();
	for(int i=0;i<n;++i)
	{
		int t1=read(),t2=read();
		a[i]=Tpoint(t1,t2);
	}
	gx=a[0].x;gy=a[0].y;
	for(int i=0;i<n;++i)
		a[i]=a[i]-Tpoint(gx,gy);
	g=getG();getds();
//	printf("%lf %lf\n",(double)g.x,(double)g.y);
	p1=0;p2=1;
	while(q--)
	{
		int opt=read();
		if(opt&1)
		{
			int x=read()-1,y=read()-1;
			if(x==p1)
			{
				p1=y;top=getpoint(p2);
				nex=Tpoint(top.x,top.y-dis[p2]);
			}
			else
			{
				p2=y;top=getpoint(p1);
				nex=Tpoint(top.x,top.y-dis[p1]);
			}

			//printf("c:%lf %lf %lf %lf\n",(double)g.x,(double)g.y,(double)top.x,(double)top.y);
			angle+=-pi/2.0-atan2(g.y-top.y,g.x-top.x);
			while(angle<0)
				angle+=2.0*pi;
			while(angle>=2*pi)
				angle-=2.0*pi;
			g=nex;
			//printf("%lf\n %lf %lf\n",(double)angle,(double)g.x,(double)g.y);
		}
		else
		{
			int x=read()-1;
			Tpoint ans=getpoint(x);
			printf("%.10lf %.10lf\n",(double)(ans.x+gx),(double)(ans.y+gy));
		}
	}

	return 0;
}
