    #include<cmath>  
    #include<cstdio>  
    #include<cstdlib>  
    #include<cstring>  
    #include<iostream>  
    #include<algorithm>  
    #define F(i,j,n) for(int i=j;i<=n;i++)  
    #define D(i,j,n) for(int i=j;i>=n;i--)  
    #define ll long long  
    #define N 20005  
    using namespace std;  
    int n,m,cnt,fa[N][16],head[N],dep[N];  
    ll f[N][16][65],a[65];  
    struct edge{int next,to;}e[N*2];  
    inline int read()  
    {  
        int x=0,f=1;char ch=getchar();  
        while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}  
        while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}  
        return x*f;  
    }  
    void add_edge(int x,int y)  
    {  
        e[++cnt]=(edge){head[x],y};head[x]=cnt;  
        e[++cnt]=(edge){head[y],x};head[y]=cnt;  
    }  
    void add(ll *a,ll x)  
    {  
        D(i,60,0) if ((x>>i)&1ll)  
        {  
            if (!a[i]){a[i]=x;return;}  
            else x^=a[i];  
        }  
    }  
    void merge(ll *a,ll *b)  
    {  
        D(i,60,0) if (b[i]) add(a,b[i]);  
    }  
    void dfs(int x)  
    {  
        dep[x]=dep[fa[x][0]]+1;  
        F(i,1,15) if (fa[x][i-1])  
        {  
            fa[x][i]=fa[fa[x][i-1]][i-1];  
            memcpy(f[x][i],f[x][i-1],sizeof(f[x][i-1]));  
            merge(f[x][i],f[fa[x][i-1]][i-1]);  
        }  
        for(int i=head[x];i;i=e[i].next) if (e[i].to!=fa[x][0])  
        {  
            fa[e[i].to][0]=x;  
            dfs(e[i].to);  
        }  
    }  
    int lca(int x,int y)  
    {  
        if (dep[x]<dep[y]) swap(x,y);  
        int tmp=dep[x]-dep[y];  
        D(i,15,0) if ((tmp>>i)&1) merge(a,f[x][i]),x=fa[x][i];  
        if (x==y) return x;  
        D(i,15,0) if (fa[x][i]!=fa[y][i])  
        {  
            merge(a,f[x][i]);merge(a,f[y][i]);  
            x=fa[x][i];y=fa[y][i];  
        }  
        merge(a,f[x][0]);merge(a,f[y][0]);  
        return fa[x][0];  
    }  
    int main()  
    {  
        n=read();m=read();  
        F(i,1,n){ll x;scanf("%lld",&x);add(f[i][0],x);}  
        F(i,1,n-1){int x=read(),y=read();add_edge(x,y);}  
        dfs(1);  
        while (m--)  
        {  
            memset(a,0,sizeof(a));  
            int x=read(),y=read(),z=lca(x,y);  
            merge(a,f[z][0]);  
            ll ans=0;  
            D(i,60,0) ans=max(ans,ans^a[i]);  
            printf("%lld\n",ans);  
        }  
    }  
