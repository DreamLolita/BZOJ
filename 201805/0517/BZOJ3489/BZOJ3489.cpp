#include<bits/stdc++.h>
#define id(x) ((x+1)%3)
using namespace std;

const int N=1e5+10;
int n,m,D,ans;
int a[N],nex[N],pre[N];

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct Tnode
{
    int val,ls,rs;
    int d[3];
    friend bool operator <(Tnode A,Tnode B){
        return A.d[D]<B.d[D];
    }
};

struct KDT
{
    int rt,sz,ret;
    int mx[N],lx[N][3],rx[N][3],siz[N];
    Tnode p[N];

    void init(int x)
    {
        rt=0;sz=x;
    }

    void pushup(int x)
    {
        mx[x]=p[x].val;
        int l=p[x].ls,r=p[x].rs;
        for(int i=0;i<3;++i)
        {
            lx[x][i]=rx[x][i]=p[x].d[i];
            if(l)
            {
                mx[x]=max(mx[x],mx[l]);
                lx[x][i]=min(lx[x][i],lx[l][i]);
                rx[x][i]=max(rx[x][i],rx[l][i]);
            }
            if(r)
            {
                mx[x]=max(mx[x],mx[r]);
                lx[x][i]=min(lx[x][i],lx[r][i]);
                rx[x][i]=max(rx[x][i],rx[r][i]);
            }
        }
        siz[x]=siz[l]+siz[r]+1;
    }

    bool inmp(int x,int l,int r)
    {
        return lx[x][2]>r && rx[x][1]<l && lx[x][0]>=l && rx[x][0]<=r;
    }

    bool outmp(int x,int l,int r)
    {
        return lx[x][0]>r || rx[x][0]<l || lx[x][1]>=l || rx[x][2]<=r;
    }

    bool inp(int x,int l,int r)
    {
        return p[x].d[0]>=l && p[x].d[0]<=r && p[x].d[1]<l && p[x].d[2]>r;
    }

    void query(int x,int l,int r)
    {
        if(!x)
            return;
        if(inmp(x,l,r))
        {    
            ret=max(ret,mx[x]);
            return;
        }
        if(outmp(x,l,r))
            return;
        if(inp(x,l,r))
            ret=max(ret,p[x].val);
        int ls=p[x].ls,rs=p[x].rs;
        if(mx[ls]>mx[rs])
        {
            if(mx[ls]>ret)
                query(ls,l,r);
            if(mx[rs]>ret)
                query(rs,l,r);
        }
        else
        {
            if(mx[rs]>ret)
                query(rs,l,r);
            if(mx[ls]>ret)
                query(ls,l,r);
        }
    }
    
    int build(int l,int r,int f)
    {
        int mid=(l+r)>>1;D=f;
        nth_element(p+l,p+mid,p+r+1);
        mx[mid]=p[mid].val;siz[mid]=1;
        for(int i=0;i<3;++i)
            lx[mid][i]=rx[mid][i]=p[mid].d[i];
        if(l<mid)
            p[mid].ls=build(l,mid-1,id(f));
        if(r>mid)
            p[mid].rs=build(mid+1,r,id(f));
        pushup(mid);
        return mid;

    }

    int Query(int l,int r)
    {
        ret=0;
        query(rt,l,r);
        return ret;
    }
}tr;

int main()
{
    freopen("BZOJ3489.in","r",stdin);
    freopen("BZOJ3489.out","w",stdout);

    n=read();m=read();
    for(int i=1;i<=n;++i)
        a[i]=read(),pre[i]=-1,nex[i]=n+1;
    for(int i=1;i<=n;++i)
    {    
        tr.p[i].d[0]=i;tr.p[i].val=a[i];
        tr.p[i].d[1]=pre[a[i]];pre[a[i]]=i;
    }
    for(int i=n;i;--i)
    {
        tr.p[i].d[2]=nex[a[i]];
        nex[a[i]]=i;
    }
    
    tr.init(n);tr.rt=tr.build(1,n,0);
    for(int i=1;i<=m;++i)
    {
        int l=(read()+ans)%n+1,r=(read()+ans)%n+1;
        if(l>r)
            swap(l,r);
        ans=tr.Query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}
