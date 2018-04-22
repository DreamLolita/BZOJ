#include <cstdio>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int mod=1e9+7;
ll hash[51000],pow[51000];
char s[51000];
ll base=29;
int n,m,w[51000],tmp[51000];
int Ans=0;
bool maxw(int i,int j)
{
    if(i==j) return 1;
    /*if(i+m-1<=n&&j+m-1<=n)
    {
      ll has1=(hash[i+m-1]-(hash[i-1]*pow[m])%mod)%mod;
      ll has2=(hash[j+m-1]-(hash[j-1]*pow[m])%mod)%mod;
      if(has1==has2) return 1;
    }*/

    int L=0;
    int R=min(m+1,min(n-i+2,n-j+2));
    int ans=0;
    while(L<=R)
    {
        int mid=(L+R)/2;
        ll hash1=(hash[i+mid-1]-(hash[i-1]*pow[mid])%mod)%mod;
        ll hash2=(hash[j+mid-1]-(hash[j-1]*pow[mid])%mod)%mod;
        while(hash1<0) hash1+=mod;
        while(hash2<0) hash2+=mod;
        if(hash1==hash2) L=mid+1,ans=mid;
        else R=mid-1;
    } 
    //if(ans==m) return 1;
    //ll has1=(hash[i+ans-1]-(hash[i-1]*pow[ans])%mod)%mod;
    //ll has2=(hash[j+ans-1]-(hash[j-1]*pow[ans])%mod)%mod;
    //if(has1==has2) return 1;
    if(ans>=m) return 1;
    return s[i+ans]<s[j+ans]; 
}
void sort(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)/2;
    sort(l,mid);
    sort(mid+1,r);
    int i=l,j=mid+1;
    int now=l;
    while(i<=mid||j<=r)
    {
        bool f;
        if(i>mid) f=0;
        if(j>r) f=1;
        if(i<=mid&&j<=r) f=maxw(w[i],w[j]);
        if(f)
         tmp[now++]=w[i++];
        else
        {
            tmp[now++]=w[j++];
            Ans+=(mid-i+1);
        }
    }
    for(i=l;i<=r;i++) w[i]=tmp[i];
    return;
}
int main()
{
    freopen("2464.in","r",stdin);
    freopen("2464.out","w",stdout);
    scanf("%d%d\n",&n,&m);
    scanf("%s",(s+1));
    int len=strlen(s+1);
    hash[0]=0,pow[0]=1;
    for(int i=1;i<=len;i++)
    {
        hash[i]=((hash[i-1]*base)%mod+s[i]-'a'+1)%mod;
        pow[i]=(pow[i-1]*base)%mod;
        //printf("%lld %lld\n",hash[i],pow[i]);
        w[i]=i;
    }

    sort(1,n);

    printf("%d",Ans); 

    return 0;
    //printf("%d",hash1==hash2);
}
