#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=1e6+5;
const int K=26;
const int mod=1000000007;
int m;
LL ans;
char s[N];

LL read()
{
    LL ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct PAM
{
    int las,sz,n;
    int ch[N][K],fail[N],len[N];
    int sum[N],num[N],suf[N],S[N];
    
    int newnode(int x)
    {
        memset(ch[sz],0,sizeof(ch[sz]));
        num[sz]=sum[sz]=0;len[sz]=x;
        return sz++;
    }
    
    void init()
    {
        sz=las=n=0;
        newnode(0);newnode(-1);
        fail[0]=1;S[n]=-1;
    }
    
    int getfail(int x)
    {
        while(S[n-len[x]-1]!=S[n])
            x=fail[x];
        return x;
    }
    
    void insert(int x)
    {
        S[++n]=x;
        int now=getfail(las);
        if(!ch[now][x])
        {
            int p=newnode(len[now]+2);
            fail[p]=ch[getfail(fail[now])][x];
            num[p]=num[fail[p]]+1;
            sum[p]=(sum[fail[p]]+len[p])%mod;
            ch[now][x]=p;
        }
        las=ch[now][x];
    }
    
    void solve()
    {
        init();
        for(LL i=0;i<m;++i)
        {
            insert(s[i]-'a');
            suf[i+1]=(num[las]*(i+2)%mod-sum[las]+mod)%mod;
        }
        init();ans=0;
        for(LL i=m-1;i>=0;--i)
        {
            insert(s[i]-'a');
            ans+=suf[i]*(num[las]*i%mod+sum[las]);
            ans%=mod;
        }
    }
}tr;

int main()
{
    //freopen("HDU5785.in","r",stdin);
    //freopen("HDU5785.out","w",stdout);

    while(~scanf("%s",s))
    {
        m=strlen(s);
        tr.solve();
        printf("%I64d\n",ans);
    }

    return 0;
}
