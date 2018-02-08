#include<bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
const int N=3010;
int n,m,q;
ui A,B,C,ans,sum;
ui a[N][N],s[N][N],h[N][N];

inline ui rng61()
{
    A^=A<<16;
    A^=A>>5;
    A^=A<<1;
    ui t=A;
    A=B;
    B=C;
    C^=t^A;
    return C;
}

int main()
{
	freopen("BZOJ4972.in","r",stdin);
	freopen("BZOJ4972.out","w",stdout);
	
    scanf("%d%d%d%u%u%u",&n,&m,&q,&A,&B,&C);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            a[i][j]=rng61();
    for(int i=1;i<=n;++i)
    {
        for(int j=m;j>=1;--j)
        {
            s[i][j]=s[i][j+1]+s[i-1][j+1]-s[i-1][j+2]+a[i][j];
            h[i][j]=h[i][j+1]+h[i-1][j]-h[i-1][j+1]+a[i][j];
        }
    }
    
    for(int i=1;i<=q;++i)
	{
        ui x=rng61()%n+1;
        ui y=rng61()%m+1;
        ui k=rng61()%min(x,y)+1;
        sum=s[x][y-k+1]-s[x-k][y+1]-h[x][y+1]+h[x-k][y+1];
        ans=ans*233+sum;
    }
    printf("%u",ans);
    return 0;
}
