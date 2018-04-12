#include<cstdio>
#include<algorithm>
#define lc x<<1
#define rc x<<1|1
using namespace std;
typedef long long ll;
typedef pair<int,int>P;
const int N=100010,M=262150,E=500010;
const ll inf=1LL<<60;
int n,Q,i,j,a[N],t,q[N],l[N],r[N];
int ga[N],gd[N],gq[N],ed,vl[E],vr[E],nxt[E];ll w[E];
P ans[N];
ll m[M],hm[M],d[M],hd[M];
ll fin;
int pos;
inline void Min(ll&a,ll b){a>b?(a=b):0;}
inline void hdoa(int x,ll v){
    Min(hm[x],m[x]+v);
    Min(hd[x],d[x]+v);
}
inline void doa(int x,ll v){
    Min(hm[x],m[x]+=v);
    Min(hd[x],d[x]+=v);
}
inline void pb(int x){
    if(hd[x])hdoa(lc,hd[x]),hdoa(rc,hd[x]),hd[x]=0;
    if(d[x])doa(lc,d[x]),doa(rc,d[x]),d[x]=0;
}
inline void up(int x){
    m[x]=min(m[lc],m[rc]);
    Min(hm[x],min(hm[lc],hm[rc]));
}
void build(int x,int a,int b){
    if(a==b){
        hm[x]=m[x]=-1LL*a*(n-1);
        return;
    }
    int mid=(a+b)>>1;
    build(x<<1,a,mid);
    build(x<<1|1,mid+1,b);
    up(x);
}
void dfs(int x,int a,int b){
    if(a==b){
        hm[x]=m[x];
        return;
    }
    pb(x);
    int mid=(a+b)>>1;
    dfs(x<<1,a,mid);
    dfs(x<<1|1,mid+1,b);
    m[x]=min(m[lc],m[rc]);
    hm[x]=min(hm[lc],hm[rc]);
}
void add(int x,int f,int t,int qf,int qt,ll v){
    if(qf<=f&&t<=qt){doa(x,v);return;}
    pb(x);
    int mid=(f+t)>>1;
    if(qf<=mid)add(lc,f,mid,qf,qt,v);
    if(qt>mid)add(rc,mid+1,t,qf,qt,v);
    up(x);
}
 
inline void addedge(int&x,int l,int r,ll z){
    vl[++ed]=l;
    vr[ed]=r;
    w[ed]=z;
    nxt[ed]=x;
    x=ed;
}
inline void ext(int xl,int xr,int yl,int yr,ll w){
    //printf("%d %d %d %d %lld\n",xl,xr,yl,yr,w);
    if(w>=0){
        addedge(ga[xl],yl,yr,w);
        addedge(gd[xr+1],yl,yr,-w);
    }else{
        addedge(gd[xl],yl,yr,w);
        addedge(ga[xr+1],yl,yr,-w);
    }
}
 
void ask(int x,int a,int b,int c,int d){
    if(c<=a&&b<=d){
        Min(fin,hm[x]);
        return;
    }
    pb(x);
    int mid=(a+b)>>1;
    if(c<=mid)ask(x<<1,a,mid,c,d);
    if(d>mid)ask(x<<1|1,mid+1,b,c,d);
}
void getpos(int x,int a,int b,int c,int d){
    if(pos)return;
    if(hm[x]>fin)return;
    if(a==b){
        pos=a;
        return;
    }
    pb(x);
    int mid=(a+b)>>1;
    if(c<=mid)getpos(x<<1,a,mid,c,d);
    if(d>mid)getpos(x<<1|1,mid+1,b,c,d);
}
 
inline P query(int l,int r){
    fin=inf;
    ask(1,1,n,r,n);
    //printf("! %d %d %lld\n",l,r,fin);
    pos=0;
    getpos(1,1,n,r,n);
    return P(pos-fin%n,pos);
}
 
int main(){
    //(ma-mi-r+l)*n+r-l
    //ma*n-mi*n-r*(n-1)+l*(n-1)
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    scanf("%d",&Q);
    for(i=1;i<=Q;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(gq[x],i,y,0);
    }
     
    for(q[t=0]=0,i=1;i<=n;i++){
        while(t&&a[i]>a[q[t]])t--;
        l[i]=q[t]+1;
        q[++t]=i;
    }
    for(q[t=0]=n+1,i=n;i;i--){
        while(t&&a[i]>a[q[t]])t--;
        r[i]=q[t]-1;
        q[++t]=i;
    }
    for(i=1;i<=n;i++)ext(l[i],i,i,r[i],1LL*a[i]*n);
     
    for(q[t=0]=0,i=1;i<=n;i++){
        while(t&&a[i]<a[q[t]])t--;
        l[i]=q[t]+1;
        q[++t]=i;
    }
    for(q[t=0]=n+1,i=n;i;i--){
        while(t&&a[i]<a[q[t]])t--;
        r[i]=q[t]-1;
        q[++t]=i;
    }
    for(i=1;i<=n;i++)ext(l[i],i,i,r[i],-1LL*a[i]*n);
     
    build(1,1,n);
    for(i=1;i<=n;i++){
        add(1,1,n,1,n,n-1);
        for(j=ga[i];j;j=nxt[j]){
            add(1,1,n,vl[j],vr[j],w[j]);
        }
        for(j=gd[i];j;j=nxt[j]){
            add(1,1,n,vl[j],vr[j],w[j]);
        }
        if(i==1)dfs(1,1,n);
        for(j=gq[i];j;j=nxt[j]){
            ans[vl[j]]=query(i,vr[j]);
        }
    }
     
    for(i=1;i<=Q;i++)printf("%d %d\n",ans[i].first,ans[i].second);
}
