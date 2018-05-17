//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

const double INF=1e20;
const double eps=1e-8;
const double bas=0.98;
int n;

struct Tpoint
{
    double x,y,z;
};
Tpoint now,p[50];

double sqr(double x)
{
    return x*x;
}

double getdis(Tpoint A,Tpoint B)
{
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y)+sqr(A.z-B.z));
}

double SA()
{
    int id;
    double ret=INF,temp=1000.0;
    double mxdis,tmpdis;
    while(temp>eps)
    {
        id=0;
        mxdis=getdis(now,p[id]);
        for(int i=1;i<n;++i)
        {
            tmpdis=getdis(now,p[i]);
            if(tmpdis>mxdis)
                mxdis=tmpdis,id=i;
        }
        if(ret>mxdis)
            ret=mxdis;
        now.x+=(p[id].x-now.x)/mxdis*temp;
        now.y+=(p[id].y-now.y)/mxdis*temp;
        now.z+=(p[id].z-now.z)/mxdis*temp; 
        temp*=bas;
    }
    return ret;
}

int main()
{
    freopen("POJ2069.in","r",stdin);
    freopen("POJ2069.out","w",stdout);

    while(scanf("%d",&n)!=EOF)
    {
//        printf("%d\n",n);
        if(n==0)
            break;
        for(int i=0;i<n;++i)
            scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
        now.x=now.y=now.z=0.0;
        printf("%0.5lf\n",SA()+eps);
    }

    return 0;
}
