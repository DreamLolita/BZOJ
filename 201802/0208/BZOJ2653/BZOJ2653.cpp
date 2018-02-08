#include<bits/stdc++.h>
#define N 20010
#define Q 25010
#define M 401000
#define INF 0x3f3f3f3f
using namespace std;
int n,NO,q;
int root[N],qs[5];;
int size; 

struct Tree
{
    int ls,rs,sum,lmax,rmax;
}tr[M];

struct Tnode
{
    int val,no;
    friend istream& operator >> (istream &_,Tnode &a)
    {scanf("%d",&a.val),a.no=++NO;return _;}
}a[N];

int cmp(Tnode a,Tnode b)
{
    return a.val<b.val;
}

void pushup(int rt)
{
    int l=tr[rt].ls,r=tr[rt].rs;
    tr[rt].sum=tr[l].sum+tr[r].sum;
    tr[rt].lmax=max(tr[l].lmax,tr[l].sum+tr[r].lmax);
    tr[rt].rmax=max(tr[r].rmax,tr[r].sum+tr[l].rmax);
}

void build(int &rt,int l,int r)
{
    if(!rt)
        rt=++size;
    if(l==r)
    {
        tr[rt].lmax=tr[rt].rmax=tr[rt].sum=1;
        return;
    }
    int mid=(l+r)>>1;
    build(tr[rt].ls,l,mid);
    build(tr[rt].rs,mid+1,r);
    pushup(rt);
}

void update(int y,int &x,int l,int r,int v,int val)
{
    x=++size;
    tr[x]=tr[y];
    if(l==r)
    {
        tr[x].lmax=tr[x].rmax=tr[x].sum=val;
        return;
    }
    int mid=(l+r)>>1;
    if(v<=mid)update(tr[y].ls,tr[x].ls,l,mid,v,val);
    else update(tr[y].rs,tr[x].rs,mid+1,r,v,val);
    pushup(x);
}

int query_sum(int rt,int L,int R,int l,int r)
{
    if(L>R)return 0;
    int ret=0;
    if(L<=l&&r<=R)
    {
        return tr[rt].sum;
    }
    int mid=(l+r)>>1;
    if(L<=mid)ret+=query_sum(tr[rt].ls,L,R,l,mid);
    if(R>mid)ret+=query_sum(tr[rt].rs,L,R,mid+1,r);
    return ret;
}

int query_rmax(int rt,int L,int R,int l,int r)
{
    if(L>R)return 0;
    int ret=-INF;
    if(L<=l&&r<=R)
    {
        return tr[rt].rmax;
    }
    int mid=(l+r)>>1;
    if(R<=mid)ret=max(ret,query_rmax(tr[rt].ls,L,R,l,mid));
    else if(L>mid)ret=max(ret,query_rmax(tr[rt].rs,L,R,mid+1,r));
    else
    {
        ret=max(ret,query_rmax(tr[rt].ls,L,mid,l,mid)+query_sum(tr[rt].rs,mid+1,R,mid+1,r));
        ret=max(ret,query_rmax(tr[rt].rs,mid+1,R,mid+1,r));
    }
    return ret;
}

int query_lmax(int rt,int L,int R,int l,int r)
{
    if(L>R)return 0;
    int ret=-INF;
    if(L<=l&&r<=R)
    {
        return tr[rt].lmax;
    }
    int mid=(l+r)>>1;
    if(R<=mid)ret=max(ret,query_lmax(tr[rt].ls,L,R,l,mid));
    else if(L>mid)ret=max(ret,query_lmax(tr[rt].rs,L,R,mid+1,r));
    else
    {
        ret=max(ret,query_sum(tr[rt].ls,L,mid,l,mid)+query_lmax(tr[rt].rs,mid+1,R,mid+1,r));
        ret=max(ret,query_lmax(tr[rt].ls,L,mid,l,mid));
    }
    return ret;
}

bool check(int x)
{
    return query_rmax(root[x],qs[1],qs[2],1,n)+query_sum(root[x],qs[2]+1,qs[3]-1,1,n)+query_lmax(root[x],qs[3],qs[4],1,n)>=0;
}

int main()
{
//	freopen("BZOJ2653.in","r",stdin);
//	freopen("BZOJ2653.out","w",stdout);
	
    scanf("%d",&n);
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1,cmp);
    build(root[1],1,n);
    for(int i=2;i<=n;i++)
        update(root[i-1],root[i],1,n,a[i-1].no,-1);
    int ans=0;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d%d%d",&qs[1],&qs[2],&qs[3],&qs[4]);
        for(int i=1;i<=4;i++)
			qs[i]=(qs[i]+ans)%n+1;
        sort(qs+1,qs+5);
        
        int tmp=0,l=1,r=n;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid))tmp=mid,l=mid+1;
            else r=mid-1;
        }
        ans=a[tmp].val;
        printf("%d\n",ans);
    }
	return 0;
}
