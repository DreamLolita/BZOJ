#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N=1e6+5;
int n,s,d,minn,nn;
int nex[N<<1],dep[N<<1],l[N];

int calc(int x)
{
    int now=x,fa=x,k;
    while(fa-x<n)
        fa=nex[fa];
    while(now-x<n)
    {
        k=nex[now];
        nex[now]=fa;
        now=k;
    }
    return dep[x]-dep[now];
}

int main()
{
	freopen("BZOJ3827.in","r",stdin);
	freopen("BZOJ3827.out","w",stdout);
	
    scanf("%d%d",&n,&s);nn=n*2;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&l[i]);
        minn=max(minn,l[i]);
    }
    
    while(s--)
    {
        scanf("%d",&d);
        if(d<minn)
        {
            puts("NIE");
            continue;
        }
        int sum=0,j=1;
        for(int i=1;i<=nn;i++)
        {
            while(j<nn && sum+l[(j>n)?j-n:j]<=d)
            {
                sum=sum+l[(j>n)?j-n:j];
                j++;
            }
            nex[i]=j;
            sum-=l[(i>n)?i-n:i];
        }
        int ans=99999999;
        dep[nn]=0;
        for(int i=nn;i>=1;i--)
            dep[i]=dep[nex[i]]+1;
            
        for(int i=1;i<=n;i++)
            ans=min(ans,calc(i));
        printf("%d\n",ans);
    }
    return 0;
}
