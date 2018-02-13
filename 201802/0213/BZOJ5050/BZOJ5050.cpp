#include<bits/stdc++.h>
#define lson (o<<1)
#define rson (o<<1|1)
using namespace std;

typedef long long LL;
const int N=1e5+5;
const int INF=2e9;

int n,m,a[N],exis[N],exl[N],exr[N],cnt,q[N];
LL sumv[N<<2];int addv[N<<2],minl[N<<2],minr[N<<2],size[N<<2];

inline void pushup(int o)
{
    minr[o]=min(minr[lson],minr[rson]);
    minl[o]=min(minl[lson],minl[rson]);
}

inline void puttag(int o,int v)
{
    sumv[o]+=v*size[o];
	addv[o]+=v;minl[o]-=v;minr[o]-=v;
}

inline void pushdown(int o)
{
    if(!addv[o])
		return;
    puttag(lson,addv[o]);puttag(rson,addv[o]);
    addv[o]=0;
}

inline void build(int o,int l,int r)
{
    if(l==r)
	{
        sumv[o]=a[l];size[o]=exis[l];
		minl[o]=exl[l];minr[o]=exr[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(o);
    sumv[o]=sumv[lson]+sumv[rson];
    size[o]=size[lson]+size[rson];
}

inline void recalc(int o,int l,int r,int q)
{
    if(l==r)
	{
        if(exis[l])
			a[l]+=addv[o];
        addv[o]=0;
		return;
    }
    pushdown(o);
    int mid=(l+r)>>1;
    if(q<=mid)
		recalc(lson,l,mid,q);
	else 
		recalc(rson,mid+1,r,q);
}

inline LL querysum(int o,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)
		return sumv[o];
    pushdown(o);
    int mid=(l+r)>>1;
	LL ans=0;
    if(ql<=mid)
		ans+=querysum(lson,l,mid,ql,qr);
    if(qr>mid)
		ans+=querysum(rson,mid+1,r,ql,qr);
    return ans;
}

inline void change(int o,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)
	{
		puttag(o,1);
		return;
	}
	pushdown(o);
	int mid=(l+r)>>1;
    if(ql<=mid)
		change(lson,l,mid,ql,qr);
    if(qr>mid)
		change(rson,mid+1,r,ql,qr);
    pushup(o);
    sumv[o]=sumv[lson]+sumv[rson];
}

inline void recexi(int o,int l,int r,int q)
{
    if(l==r)
	{
        size[o]=exis[l];
		minl[o]=exl[l];minr[o]=exr[l];
        return;
    }
    pushdown(o);
	int mid=(l+r)>>1;
    if(q<=mid)
		recexi(lson,l,mid,q);
	else 
		recexi(rson,mid+1,r,q);
    pushup(o);
    size[o]=size[lson]+size[rson];
}

inline void recml(int o,int l,int r,int q,int v)
{
    if(l==r)
	{
		minl[o]=v;
		return;
	}
    pushdown(o);
	int mid=(l+r)>>1;
    if(q<=mid)
		recml(lson,l,mid,q,v);
	else 
		recml(rson,mid+1,r,q,v);
    minl[o]=min(minl[lson],minl[rson]);
}

inline void recmr(int o,int l,int r,int q,int v)
{
    if(l==r)
	{
		minr[o]=v;
		return;
	}
    pushdown(o);
	int mid=(l+r)>>1;
    if(q<=mid)
		recmr(lson,l,mid,q,v);
	else 
		recmr(rson,mid+1,r,q,v);
    minr[o]=min(minr[lson],minr[rson]);
}

inline void dfs(int o,int l,int r)
{
    if(minl[o]>0&&minr[o]>=0)
		return;
    if(l==r)
	{
        if(minl[o]<=0 && q[cnt]!=l)
			q[++cnt]=l;
        if(minr[o]<0)
			q[++cnt]=l+1;
        return;
    }
    pushdown(o);
	int mid=(l+r)>>1;
    dfs(lson,l,mid);dfs(rson,mid+1,r);
}
inline bool flag(int i){return a[i-1]>a[i];}
inline int calcl(int i){return exis[i]&&!exis[i-1]?a[i-1]-a[i]:INF;}
inline int calcr(int i){return exis[i]&&!exis[i+1]?a[i+1]-a[i]:INF;}
inline void calcexl(int i){if(i<1||i>n)return;recml(1,0,n+1,i,calcl(i));}
inline void calcexr(int i){if(i<1||i>n)return;recmr(1,0,n+1,i,calcr(i));}
inline void get(int i){if(i<1||i>n)return;recalc(1,0,n+1,i);}

inline void solve(int i)
{
    if(i<1||i>n)
		return;
	get(i);get(i-1);get(i+1);
	exis[i]=flag(i);
	exl[i]=calcl(i);exr[i]=calcr(i);
    recexi(1,0,n+1,i);
	calcexl(i+1);calcexr(i-1);
}

int main()
{
    freopen("BZOJ5050.in","r",stdin);
    freopen("BZOJ5050.out","w",stdout);
    
    scanf("%d%d",&n,&m);
    a[0]=exl[0]=exr[0]=INF;a[n+1]=exl[n+1]=exr[n+1]=INF;
    for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),exis[i]=flag(i);
    for(int i=1;i<=n;i++)
		exl[i]=calcl(i),exr[i]=calcr(i);
    build(1,0,n+1);
    while(m--)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
        if(opt&1)
		{
            cnt=0;change(1,0,n+1,x,y);dfs(1,0,n+1);
            for(int i=1;i<=cnt;i++)
				solve(q[i]);
            solve(x);solve(y+1);
        }
        else
            printf("%lld\n",querysum(1,0,n+1,x,y));

    }
}
