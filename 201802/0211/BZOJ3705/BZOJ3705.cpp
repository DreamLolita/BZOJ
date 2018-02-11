#include<bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
const int N=2003;
const int base1=1e9+7;
const int base2=1e9+9;

ui sum[N][N][4],p1[N],p2[N];
int m,n,x,ans;

inline bool check(int x,int y,int l)
{
    ui hash,tmp;
    hash=sum[x+l-1][y+l-1][0]-sum[x-l][y+l-1][0]*p1[l+l-1]
        -sum[x+l-1][y-l][0]*p2[l+l-1]+sum[x-l][y-l][0]*p1[l+l-1]*p2[l+l-1];
    tmp=sum[x+l-1][y-l+1][1]-sum[x-l][y-l+1][1]*p1[l+l-1]
        -sum[x+l-1][y+l][1]*p2[l+l-1]+sum[x-l][y+l][1]*p1[l+l-1]*p2[l+l-1];
    if (hash!=tmp) 
		return false;
    tmp=sum[x-l+1][y+l-1][2]-sum[x+l][y+l-1][2]*p1[l+l-1]
        -sum[x-l+1][y-l][2]*p2[l+l-1]+sum[x+l][y-l][2]*p1[l+l-1]*p2[l+l-1];
    if (hash!=tmp) 
		return false;
    tmp=sum[x-l+1][y-l+1][3]-sum[x+l][y-l+1][3]*p1[l+l-1]
        -sum[x-l+1][y+l][3]*p2[l+l-1]+sum[x+l][y+l][3]*p1[l+l-1]*p2[l+l-1];
    return hash==tmp;
}

inline int solve(int x,int y)
{
    int l=1,r=min(min(x,n-x+1),min(y,m-y+1));
    while(l<=r)
	{
        int mid=(l+r)>>1;
        if(check(x,y,mid)) 
			l=mid+1; 
		else 
			r=mid-1;
    }
    return l-1;
}

int main()
{
//	freopen("BZOJ3705.in","r",stdin);
//	freopen("BZOJ3705.out","w",stdout);
	
	int i,j,k; 
    scanf("%d%d",&n,&m);
    n=n*2+1;m=m*2+1;
    for(i=2;i<n;i+=2)
        for(j=2;j<m;j+=2)
		{
            scanf("%d",&x);
            for (k=0;k<4;k++) 
				sum[i][j][k]=x;
        }
        
    p1[0]=p2[0]=1;
    for(i=1;i<N;++i)
        p1[i]=p1[i-1]*base1,p2[i]=p2[i-1]*base2;
        
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j) 
			sum[i][j][0]+=sum[i-1][j][0]*base1;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j) 
			sum[i][j][0]+=sum[i][j-1][0]*base2;
    for(i=1;i<=n;++i)
        for (j=m;j>=1;--j) 
			sum[i][j][1]+=sum[i-1][j][1]*base1;
    for(i=1;i<=n;++i)
        for (j=m;j>=1;--j) 
			sum[i][j][1]+=sum[i][j+1][1]*base2;
    for(i=n;i>=1;--i)
        for (j=1;j<=m;++j) 
			sum[i][j][2]+=sum[i+1][j][2]*base1;
    for(i=n;i>=1;--i)
        for (j=1;j<=m;++j) 
			sum[i][j][2]+=sum[i][j-1][2]*base2;
    for(i=n;i>=1;--i)
        for (j=m;j>=1;--j) 
			sum[i][j][3]+=sum[i+1][j][3]*base1;
    for(i=n;i>=1;--i)
        for(j=m;j>=1;--j) 
			sum[i][j][3]+=sum[i][j+1][3]*base2;
        
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
            if((i^j^1)&1) 
				ans+=solve(i,j)/2;
            
    printf("%d",ans);
} 
