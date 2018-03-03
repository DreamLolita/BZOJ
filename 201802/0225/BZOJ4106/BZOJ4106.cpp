#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define eps 1e-9
 
using namespace std;
 
const int MAXN=1e6+10;
int p,a,b,c,d,n;
double price[MAXN],pre_max[MAXN],pre_min[MAXN];
double ans,maxn;
 
int main()
{
  //  freopen("BZOJ4106.in","r",stdin);
 //   freopen("BZOJ4106.out","w",stdout);
     
    while(~scanf("%d%d%d%d%d%d",&p,&a,&b,&c,&d,&n))
    {
        ans=0;
        for (int i=1;i<=n;i++)  price[i]=p*(sin(a*i+b)+cos(c*i+d)+2);
        maxn=price[1];
        for (int i=2;i<=n;i++)
        {
            if (price[i]>maxn)  maxn=price[i];
            else    ans=max(ans,maxn-price[i]);
        }
        printf("%.6lf\n",ans);
    }
 
    return 0;
}
