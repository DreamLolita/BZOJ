#include<iostream>
#include<cstdio>
using namespace std;
void doit()
{
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    a--;c--;
    int i,j,x,y,ans;
    int aa,bb,cc,dd;
    if(d>b) swap(b,d),swap(a,c);
    for(i=1;i<=d;i=j+1)
    {
        j=min(b/(b/i),d/(d/i));
        if(i<=a) j=min(j,a/(a/i));
        if(i<=c) j=min(j,c/(c/i));
        if(b/i>a/i&&d/i>c/i) ans=j;
    }
    printf("%d\n",ans);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) doit();
}
