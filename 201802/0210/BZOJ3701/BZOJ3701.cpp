#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
LL n,m,l,r,lsq,rsq,mod,ans,x,y,tmp,p,flag;
int num[N],fac[N][8];

LL calc(LL x,LL t) 
{
    x=min(x,m);
    LL tmp=x/t;
    LL ans=tmp*(m+1)-(1+tmp)*tmp/2*t;
    return ans%mod;
}

int main()
{
//	freopen("BZOJ3701.in","r",stdin);
//	freopen("BZOJ3701.out","w",stdout);
	
    scanf("%lld%lld",&n,&m);
    scanf("%lld%lld%lld",&l,&r,&mod);
    
    for(LL i=2;i<=n;i++) 
		if (!num[i]) 
        	for(LL j=i;j<=n;j+=i) 
				fac[j][++num[j]]=i;
    lsq=l*l; rsq=r*r;
    if (l<=1) 
		ans=(LL)(n+1)*m%mod+(LL)n*(m+1)%mod;
    //如果l<=1则相邻的两个结点都是符合要求的
    //对于所有结点来说，往右的符合要求的结点有(n+1)*m个，往下的符合要求的结点有n*(m+1)个 
    for (LL i=1;i<=n;i++) 
	{
        if(i>=r) 
			break;
        x=(LL)sqrt(max(lsq-i*i-1,0LL));
        y=(LL)sqrt(rsq-i*i);//确定范围的左右边界
        if(x==y) 
			continue;
        LL tx=0,ty=0;
        for(LL j=0;j<(1<<num[i]);j++)
		{
            p=flag=1;
            for(LL k=0;k<num[i];k++) if (j&(1<<k)) 
			{
                p*=fac[i][k+1];
                flag=-flag;
            }
            tx=(tx+calc(x,p)*flag+mod)%mod;
            ty=(ty+calc(y,p)*flag+mod)%mod;
        }
        tmp=((ty-tx+mod)<<1)%mod;
        (ans+=tmp*(n-i+1))%=mod;
    }
	printf("%lld\n",ans);
	
    return 0;
}
