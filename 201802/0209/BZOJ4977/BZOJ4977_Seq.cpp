#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=1e5+10;

struct Tnode
{
    int w,f;
};
Tnode g[N<<1],d[N];
LL ans;
int i,j,k,n,m,a[N],x,y,h,w[N<<1],c[N<<3],p[N<<3];

inline bool Cmp(Tnode a,Tnode b)
{
    if(a.w==b.w)
		return a.f<b.f;
    return a.w<b.w;
}

inline void pushdown(int x)
{
    if(p[x])
	{
        c[x<<1]+=p[x];p[x<<1]+=p[x];
        c[x<<1|1]+=p[x];p[x<<1|1]+=p[x];
        p[x]=0;
    }
}

inline void update(int x,int l,int r,int L,int R,int y)
{
	if(l>R || r<L)
		return;
    if(l>=L && r<=R)
	{
        c[x]+=y;p[x]+=y;
        return;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if(L<=mid)
    	update(x<<1,l,mid,L,R,y);
    if(R>mid)
    	update(x<<1|1,mid+1,r,L,R,y);
    c[x]=min(c[x<<1],c[x<<1|1]);
}

inline int query(int x,int l,int r,int L,int R)
{
	if(l>R || r<L)
	 	return INF;
    if(l>=L&&r<=R)
		return c[x];
    pushdown(x);
    int mid=(l+r)>>1,ret=INF;
    if(L<=mid)
    	ret=min(ret,query(x<<1,l,mid,L,R));
    if(R>mid)
    	ret=min(ret,query(x<<1|1,mid+1,r,L,R));
    return ret;
}

int main()
{
	freopen("BZOJ4977.in","r",stdin);
	freopen("BZOJ4977.out","w",stdout);
	
    scanf("%d%d",&n,&m);
    h=n+m;
    for(i=1;i<=n;++i)
		scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    
    for(i=1;i<=n;++i)
		g[i].w=a[i],g[i].f=i;
    for(i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		g[i+n].w=x;g[i+n].f=i+n;
		d[i].w=y-x;d[i].f=i;
	}
	sort(g+1,g+h+1,Cmp);sort(d+1,d+m+1,Cmp);
    
    for(i=1;i<=h;++i)
		w[g[i].f]=i;
    for(i=n,j=m;i;--i,--j)
	{
        update(1,1,h,w[i],h,-1);
        for(;j;--j)
		{
            k=w[d[j].f+n];
            if(query(1,1,h,1,k-1)>=0 && query(1,1,h,k,h)>=-1&&a[i]+d[j].w>0)
			{
                ans+=a[i]+d[j].w;
				update(1,1,h,k,h,1);
                break;
            }
        }
        if(!j)
			break;
    }
    printf("%lld\n",ans);
    
    return 0;
}
