#include<bits/stdc++.h>
#define LL long long  
#define mod 1000000007  
#define MAXN 2000005
using namespace std;  
  
int n,m,f[MAXN],inv[MAXN];  

int solve(int x,int y)
{  
    if (x<0) return 0; 
	x>>=1;y--;  
    return (LL)f[x+y]*inv[x]%mod*inv[y]%mod;  
}  

int main()
{  
//	freopen("BZOJ4402.in","r",stdin);
//	freopen("BZOJ4402.out","w",stdout);
	
    scanf("%d%d",&n,&m); 
    f[0]=f[1]=inv[0]=inv[1]=1;  
    for(int i=2;i<=n;++i)
	{  
        f[i]=(LL)f[i-1]*i%mod; 
		inv[i]=(LL)inv[mod%i]*(mod-mod/i)%mod;  
    }  
    for(int i=2;i<=n;++i) 
		inv[i]=(LL)inv[i]*inv[i-1]%mod;  
		
    int ans=0; 
	if(m&&n) 
		ans=1; 
		
	m=min(n,m);  
    for (int i=2;i<=m;++i)
        ans=((ans+solve(n-i,i))%mod+solve(n-i-1,i))%mod;  
 
    printf("%d\n",ans);  
    return 0;  
}
