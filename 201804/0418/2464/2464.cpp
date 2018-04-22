#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;
const LL base=29;
const LL p=1e9+7;
const LL base2=233;
const LL p2=998244353;
const LL base3=666;
const LL p3=19260817;
LL n,m;
LL a[N],f[N],hs[N],fac[N],tmp[N];
LL hx[N],fac2[N],hk[N],fac3[N];
char s[N];
LL ans;

bool cmp(int l,int r)
{
    if(l==r) 
		return 1;
    int L=0,R=min(m+1,min(n-l+2,n-r+2)),ret=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        LL hs1=(hs[l+mid-1]-1ll*hs[l-1]*fac[mid]%p+p)%p;
    	LL hs2=(hs[r+mid-1]-1ll*hs[r-1]*fac[mid]%p+p)%p;
    	LL hs3=(hx[l+mid-1]-1ll*hx[l-1]*fac2[mid]%p2+p2)%p2;
    	LL hs4=(hx[r+mid-1]-1ll*hx[r-1]*fac2[mid]%p2+p2)%p2;
    	LL hs5=(hk[l+mid-1]-1ll*hk[l-1]*fac3[mid]%p3+p3)%p3;
    	LL hs6=(hk[r+mid-1]-1ll*hk[r-1]*fac3[mid]%p3+p3)%p3;
        if(hs1==hs2 && hs3==hs4 && hs5==hs6) 
			L=mid+1,ret=mid;
        else 
			R=mid-1;
    }
    if(ret>=m) 
		return 1;
    return a[l+ret]<=a[r+ret];
}

void solve(int l,int r)
{
    if(l==r) 
		return;
    int mid=(l+r)>>1;
    solve(l,mid);solve(mid+1,r);
    
    int i=l,j=mid+1;
    int now=l;
    while(i<=mid||j<=r)
    {
        bool flag;
        if(i>mid) 
			flag=0;
        if(j>r) 
			flag=1;
        if(i<=mid && j<=r) 
			flag=cmp(f[i],f[j]);
        if(flag)
        	tmp[now++]=f[i++];
        else
        {
            tmp[now++]=f[j++];
            ans+=(mid-i+1);
        }
    }
    for(int i=l;i<=r;i++)
    	f[i]=tmp[i];
    return;
}

int main()
{
    freopen("2464.in","r",stdin);
    freopen("2464.out","w",stdout);
    
    scanf("%d%d",&n,&m);
    fac[0]=1;fac2[0]=1;fac3[0]=1;
    scanf("%s",s+1);
    for(int i=1;i<=n;++i)
    {
    	a[i]=s[i]-'a'+1;f[i]=i;
		hs[i]=(1ll*hs[i-1]*base+a[i])%p;
    	fac[i]=1ll*fac[i-1]*base%p;
    	hx[i]=(1ll*hx[i-1]*base2+a[i])%p2;
    	fac2[i]=1ll*fac2[i-1]*base2%p2;
    	hk[i]=(1ll*hk[i-1]*base3+a[i])%p3;
    	fac3[i]=1ll*fac3[i-1]*base3%p3;
  //  	printf("%lld %lld\n",hs[i],fac[i]);
	}
	solve(1,n);
	printf("%lld\n",ans);
} 
