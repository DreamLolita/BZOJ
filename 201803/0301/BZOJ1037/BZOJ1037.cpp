#include<bits/stdc++.h>
using namespace std;

const int mod=12345678;
const int N=305;
const int K=25;
int n,m,k,ans;
int f[N][N>>1][K][K];

int main()
{
	freopen("BZOJ1037.in","r",stdin);
	freopen("BZOJ1037.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
    f[0][0][0][0]=1;
    for(int i=0;i<n+m;++i)
        for(int j=0;j<=n;++j)
            for(int x=0;x<=k;++x)
                for(int y=0;y<=k;++y)
                    if(f[i][j][x][y])
                    {
                        if(x+1<=k && j+1<=n)
                        {
                            f[i+1][j+1][x+1][max(y-1,0)]+=f[i][j][x][y];
                            f[i+1][j+1][x+1][max(y-1,0)]%=mod;
                        }
                        if(y+1<=k && i+1-j<=m)
                        {
                            f[i+1][j][max(x-1,0)][y+1]+=f[i][j][x][y];
                            f[i+1][j][max(x-1,0)][y+1]%=mod;
                        }
                    }

    for(int i=0;i<=n;++i)
        for(int x=0;x<=k;++x)
            for(int y=0;y<=k;++y)
            {
                ans+=f[n+m][i][x][y];
                ans%=mod;
            }
    printf("%d\n",ans);
	
	return 0;
}
