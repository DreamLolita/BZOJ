#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int P=25;
const int N=1e5+10;
const int M=6e5+10;
int n,m,tot,K,cnt,ps,ns,rway;
int tar[P],fa[N],head[N],bl[N];
int mp[P][P],bo[P][P],Log2[4194306];
vector<int>es[P];
LL tmpans,ans;
LL peo[P],p[N];

struct Tway
{
    int v,nex,w;
};
Tway e[M];

struct Tnode
{
    int x,y,w,op;
};
Tnode a[M],b[P],c[P],rem[P];

void add(int u,int v,int w)
{
    e[++tot]=(Tway){v,head[u],w};head[u]=tot;
    e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

bool cmp(Tnode A,Tnode B)
{
    return A.w<B.w;
}

bool cmpop(Tnode A,Tnode B)
{
    return A.op>B.op;
}

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

int findf(int x)
{
    return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void init()
{
    Log2[1]=0;
    for(int i=2;i<4194305;++i)
        Log2[i]=Log2[i>>1]+1;
    n=read();m=read();K=read();
    for(int i=1;i<=m;++i)
        a[i].x=read(),a[i].y=read(),a[i].w=read();
    for(int i=1;i<=K;++i)
        b[i].x=read(),b[i].y=read();
    for(int i=1;i<=n;++i)
        p[i]=read();
    
    for(int i=1;i<=n;++i)
        fa[i]=i;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=K;++i)
    {
        int fx=findf(b[i].x),fy=findf(b[i].y);
        if(fx!=fy)
            fa[fx]=fy;
    }
    
    for(int i=1;i<=m;++i)
    {
        int fx=findf(a[i].x),fy=findf(a[i].y);
        if(fx!=fy)
            fa[fx]=fy,a[i].op=1;
    }
}

void dfs(int x)
{
    peo[cnt]+=p[x];bl[x]=cnt;
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(!bl[v])
            dfs(v);
    }
}

void getmp()
{
    sort(a+1,a+m+1,cmpop);
    for(int i=1;i<=m && a[i].op;++i)
        add(a[i].x,a[i].y,0);
    for(int i=1;i<=n;++i)
        if(!bl[i])
            ++cnt,dfs(i);

    for(int i=1;i<=cnt;++i)
        for(int j=1;j<=cnt;++j)
            mp[i][j]=mp[j][i]=INF;
    for(int i=1;i<=m;++i)
    {
        int x=bl[a[i].x],y=bl[a[i].y];
        if(x==y)	
            continue;
        mp[x][y]=mp[y][x]=min(mp[x][y],a[i].w);
    }
    
    tot=0;
    for(int i=0;i<N;++i)
        head[i]=0;
    for(int i=1;i<cnt;++i)
        for(int j=i+1;j<=cnt;++j)
            if(mp[i][j]!=INF)
                ++ps,c[ps].x=i,c[ps].y=j,c[ps].w=mp[i][j];
                
    for(int i=0;i<N;++i)	
        fa[i]=i;
    sort(c+1,c+ps+1,cmp);
    for(int i=1;i<=ps;++i)
    {
        int fx=findf(c[i].x),fy=findf(c[i].y);
        if(fx!=fy)
            c[++ns]=c[i],fa[fx]=fy;
    }
}

int lowbit(int x)
{
    return x&(-x);
}

LL dfs2(int x,int f)
{
    LL sum=peo[x];
    for(int i=0;i<(int)es[x].size();++i)
    {
        int v=es[x][i];
        if(v!=f)
            sum+=dfs2(v,x);	
    }
    if(x!=bl[1])
    {
        tar[f]^=tar[x];
        if(bo[x][f])
        {
            int p=Log2[lowbit(tar[x])];
            tmpans+=1ll*sum*c[p+1].w;
        }
    }
    return sum;
}

void solve()
{
    for(int i=1;i<=K;++i)
        b[i].x=bl[b[i].x],b[i].y=bl[b[i].y];
    for(int sta=1;sta<(1<<K);++sta)
    {
        for(int i=0;i<=cnt+1;++i)	
            fa[i]=i,es[i].clear(),tar[i]=0;
        rway=0;
        bool flag=true;
        for(int i=1;i<=K;++i)
        {
            if(!(sta&(1<<(i-1))))
                continue;
            int fx=findf(b[i].x),fy=findf(b[i].y);
			bo[b[i].x][b[i].y]=bo[b[i].y][b[i].x]=i;rem[++rway]=b[i];
            if(fx!=fy)
                fa[fx]=fy,es[b[i].x].push_back(b[i].y),es[b[i].y].push_back(b[i].x);
            else
                flag=false;
        }
        if(!flag)
        {
		 	for(int i=1;i<=rway;++i)
		 		bo[rem[i].x][rem[i].y]=bo[rem[i].y][rem[i].x]=0;
			continue;
    	}
        for(int i=1;i<=ns;++i)
        {
            int fx=findf(c[i].x),fy=findf(c[i].y);
            if(fx!=fy)
            {
                fa[fx]=fy;
                es[c[i].x].push_back(c[i].y),es[c[i].y].push_back(c[i].x);
            }
            else
                tar[c[i].x]|=(1<<(i-1)),tar[c[i].y]|=(1<<(i-1));
        }
        tmpans=0;
        dfs2(bl[1],bl[1]);
        ans=max(ans,tmpans);
        for(int i=1;i<=rway;++i)
		 	bo[rem[i].x][rem[i].y]=bo[rem[i].y][rem[i].x]=0;
    }
   	printf("%lld\n",ans);
}

int main()
{
	freopen("BZOJ3206.in","r",stdin);
	freopen("BZOJ3206.out","w",stdout);

    init();
    getmp();
    solve();
    
    return 0;
}
