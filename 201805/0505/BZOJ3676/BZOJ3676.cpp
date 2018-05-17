#include<bits/stdc++.h>
using namespace std;

using namespace std;
typedef long long LL;
const int N=300010,K=20;

int n,man,san;
int s[N],mas[N<<1],rd[N<<1],cnt[26];
char str[N];
LL ans=1;

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

namespace SA
{
    int sa[N],rk[N],height[N];
    int wa[N],wb[N],wx[N],wy[N];
    int minv[N][K],Log2[N];
    
    bool cmp(int *r,int a,int b,int l)
    {
        return r[a]==r[b] && r[a+l]==r[b+l];
    }
    
    void solve(int *r,int n,int m)
    {
        int *x=wa,*y=wb,*t,i,j,p,k;
        for(i=0;i<m;++i) wx[i]=0;
        for(i=0;i<n;++i) wx[x[i]=r[i]]++;
        for(i=1;i<m;++i) wx[i]+=wx[i-1];
        for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
        for(j=1,p=1;p<n;j<<=1,m=p)
        {
            for(p=0,i=n-j;i<n;++i) y[p++]=i;
            for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
            for(i=0;i<n;++i) wy[i]=x[y[i]];
            for(i=0;i<m;++i) wx[i]=0;
            for(i=0;i<n;++i) wx[x[i]]++;
            for(i=0;i<m;++i) wx[i]+=wx[i-1];
            for(i=n-1;~i;--i) sa[--wx[x[y[i]]]]=y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
             	x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
                
       	for(i=0;i<n;++i) rk[sa[i]]=i;
    	for(i=0,k=0;i<n;height[rk[i++]]=k)
            for(k?k--:0,j=sa[rk[i]-1];r[j+k]==r[i+k];k++);
        for(i=0;i<=n;++i)
            minv[i][0]=height[i];
        for(j=1;(1<<j)<=n;++j)
            for(i=0;i+(1<<j)<=n;++i)
                minv[i][j]=min(minv[i][j-1],minv[i+(1<<j-1)][j-1]);
        Log2[1]=0;
        for(i=2;i<=n;++i)
            Log2[i]=Log2[i>>1]+1;
    }
    
    int qmin(int l,int r)
    {
        int k=Log2[r-l+1];
        return min(minv[l][k],minv[r+1-(1<<k)][k]);
    }
}

void init()
{
    scanf("%s",str);n=strlen(str);
    man=0;
    for(int i=0;i<n;++i)
    {
        s[i]=str[i];
        mas[man++]='#';mas[man++]=str[i];
    }
    s[n]=0;mas[man++]='#';san=n+1;
    SA::solve(s,n+1,128);
}

void update(int p,int k) 
{
    using namespace SA;
    p=rk[p];
    int L=0,R=p;
    while(L<R) 
    {
        int mid=(L+R)>>1;
        if(qmin(mid+1,p)>=k) R=mid;
        	else L=mid+1;
    }
    int RL=p,RR=san-1;
    while(RL<RR) 
    {
        int mid=(RL+RR+1)>>1;
        if(qmin(p+1,mid)>=k) RL=mid;
        	else RR=mid-1;
    }
    ans=max(ans,1ll*k*(RL-L+1));
}

void manacher() 
{
    int mx=0,p=0;
    for(int i=0;i<man;++i) 
    {
        if(i<mx) 
            rd[i]=min(rd[2*p-i],mx-i);
        else 
            rd[i]=1;
        while(i+rd[i]<man && i-rd[i]>=0 && mas[i+rd[i]]==mas[i-rd[i]] ) 
        {
            if(islower(mas[i-rd[i]])) 
                update((i-rd[i])/2, rd[i]+1);
            ++rd[i];
        }
        if(i+rd[i]>mx) 
            mx=i+rd[i],p=i;
    }
    for(int i=0;i<n;++i)
        ans=max(ans,(LL)++cnt[str[i]-'a']);
    printf("%lld\n",ans);
}

int main()
{
	freopen("BZOJ3676.in","r",stdin);
	freopen("BZOJ3676.out","w",stdout);

    init();
    manacher();

    return 0;
}

