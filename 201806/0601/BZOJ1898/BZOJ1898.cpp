#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=55;
const int M=1e4+10;
const int mod=10000;

int n,m,fish,st,en,tim,tot;
int head[N],ans[N];
int f[N][5],t[N],tp[N];

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct Tway
{
    int v,nex;
    Tway(){}
    Tway(int vv,int nexx){v=vv;nex=nexx;}
};
Tway e[M];

void add(int u,int v)
{
    e[++tot]=Tway(v,head[u]);head[u]=tot;
    e[++tot]=Tway(u,head[v]);head[v]=tot;
}

struct Matrix
{
    int a[N][N];
    Matrix(){}

    void clear(){
        memset(a,0,sizeof(a));
    }

    Matrix operator *(const Matrix&A)const
    {
        Matrix ret;ret.clear();
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                for(int k=0;k<n;++k)
                    (ret.a[i][j]+=a[i][k]*A.a[k][j])%=mod;
        return ret;
    }
};
Matrix b,mp[15];

void build1(int x)
{
    for(int i=head[x];i;i=e[i].nex)
        for(int j=1;j<=12;++j)
            mp[j].a[x][e[i].v]=1;
}

void build2(int x)
{
    for(int i=1;i<=12;++i)
    {
        int tmp=f[x][i%t[x]];
        for(int j=0;j<n;++j)
            mp[i].a[j][tmp]=0;
    }
}

int main()
{
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);
    
    n=read();m=read();st=read();en=read();tim=read();
    for(int i=0;i<m;++i)
    {
        int u=read(),v=read();
        add(u,v);
    }
    fish=read();
    for(int i=1;i<=fish;++i)
    {
        t[i]=read();
        for(int j=0;j<t[i];++j)
            f[i][j]=read();
    }
    for(int i=0;i<n;++i)
        build1(i);
    for(int i=1;i<=fish;++i)
        build2(i);
    for(int i=0;i<n;++i)
        b.a[i][i]=mp[13].a[i][i]=1;
    
    for(int i=1;i<=12;++i)
        mp[13]=mp[13]*mp[i];
    for(int i=tim/12;i;i>>=1)
    {
        if(i&1)
            b=b*mp[13];
        mp[13]=mp[13]*mp[13];
    }
    for(int i=1;i<=tim%12;++i)
        b=b*mp[i];
    tp[st]=1;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
            (ans[i]+=tp[j]*b.a[j][i])%=mod;
    }
    
    printf("%d\n",ans[en]);

    return 0;
}
