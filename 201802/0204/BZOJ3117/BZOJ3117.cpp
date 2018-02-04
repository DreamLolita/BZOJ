#include<bits/stdc++.h>
#define root 1,0,n
#define lch l,mid
#define rch mid+1,r
#define MAXT 0x7ffffffffffffffLL
using namespace std;

typedef long long LL;
const int N=1e4+10;
const int M=4e6+10;
int tot=2,ls[M],rs[M];

struct Q
{
    LL T;
    int M,P;
}q[N];

struct QQ
{
    int M,P;
}qq[N];

struct Tree
{
    int maxn,lm,rm,lr,rl,lazy;
}tree[M];

struct S
{
    LL time;
    int l,r;
    bool operator < (const S a) const{
        return time<a.time;
    }
};
multiset<S> a;

int in()
{
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}

int New(int l,int r,int p)
{
    if (p) tree[tot]=(Tree){r-l+1,r-l+1,r-l+1,r,l,-1};
    else tree[tot]=(Tree){0,0,0,l-1,r+1,-1};
    return tot++;
}

void Open(int rt,int l,int r)
{
    if (!ls[rt])
	{
        int mid=(l+r)>>1;
        ls[rt]=New(lch,tree[rt].maxn);
        rs[rt]=New(rch,tree[rt].maxn);
    }
}

void paint(int rt,int l,int r,int p)
{
    if (p) tree[rt]=(Tree){r-l+1,r-l+1,r-l+1,r,l,1};
    else tree[rt]=(Tree){0,0,0,l-1,r+1,0};
}

void push_down(int rt,int l,int r)
{
    if (tree[rt].lazy!=-1)
	{
        int mid=(l+r)>>1;
        paint(ls[rt],lch,tree[rt].lazy);
        paint(rs[rt],rch,tree[rt].lazy);
        tree[rt].lazy=-1;
    }
}

void change(int rt,int l,int r,int ll,int rr,int k)
{
    if (ll<=l && r<=rr)
	{
        paint(rt,l,r,k);
        return;
    }
    Open(rt,l,r);
    push_down(rt,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) change(ls[rt],lch,ll,rr,k);
    if (rr>mid) change(rs[rt],rch,ll,rr,k);
    //lm
    tree[rt].lm=tree[ls[rt]].lm;
    if (tree[ls[rt]].lm==mid-l+1)
	{
        tree[rt].lm+=tree[rs[rt]].lm;
        tree[rt].lr=tree[rs[rt]].lr;
    }
    else 
		tree[rt].lr=tree[ls[rt]].lr;
    //rm
    tree[rt].rm=tree[rs[rt]].rm;
    if (tree[rs[rt]].rm==r-mid)
	{
        tree[rt].rm+=tree[ls[rt]].rm;
        tree[rt].rl=tree[ls[rt]].rl;
    }
    else 
		tree[rt].rl=tree[rs[rt]].rl;
    //maxn
    tree[rt].maxn=max(max(tree[ls[rt]].maxn,tree[rs[rt]].maxn),tree[ls[rt]].rm+tree[rs[rt]].lm);
}
int query(int rt,int l,int r,int k)
{
    if (l==r) 
		return l;
    Open(rt,l,r);
    push_down(rt,l,r);
    int mid=(l+r)>>1;
    if (tree[ls[rt]].maxn>=k)
        return query(ls[rt],lch,k);
    if (tree[ls[rt]].rm+tree[rs[rt]].lm>=k)
        return tree[ls[rt]].rl;
    return query(rs[rt],rch,k);
}
int main()
{
//	freopen("BZOJ3117.in","r",stdin);
//	freopen("BZOJ3117.out","w",stdout);
	
    int n=in(),num=0;
    while(true)
	{
        q[num].T=(LL)in(),q[num].M=in(),q[num].P=in();
        if (!q[num].T && !q[num].M && !q[num].P) 
			break;
        num++;
    }
    if (!num)
	{
        printf("0\n0\n");
        return 0;
    }
    tree[1]=(Tree){n,n,n,n,0,-1}; n--;
    int h=0,t=0,x=0;
    a.insert((S){MAXT,0,0});
    q[num].T=MAXT;
    LL time=-1,ans;
    while (time!=MAXT)
	{
        for (; a.begin()->time==time; a.erase(a.begin()))
            change(root,a.begin()->l,a.begin()->r,1);
        for (; h<t && qq[h].M<=tree[1].maxn; ++h)
		{
            int l=query(root,qq[h].M);
            int r=l+qq[h].M-1;
            change(root,l,r,0);
            a.insert((S){time+qq[h].P,l,r});
        }
        for (; q[x].T==time; ++x)
            if (q[x].M>tree[1].maxn)
                qq[t++]=(QQ){q[x].M,q[x].P};
            else 
			{
                int l=query(root,q[x].M);
                int r=l+q[x].M-1;
                change(root,l,r,0);
                a.insert((S){time+q[x].P,l,r});
            }
        ans=time;
        time=min(a.begin()->time,q[x].T);
    }
    cout<<ans<<endl<<t<<endl;
    return 0;
}
