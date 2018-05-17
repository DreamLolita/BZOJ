#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const double eps=1e-7;
const double INF=1e9;
int n,m,S,T,tot,cnt;
int head[N],dep[N],cur[N];
double L,R,sum;
double p[N],r[N],d[N],sr[N],v[N];
queue<int>q;

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct Tway
{
    int v,nex;
    double w;
};
Tway e[N];

bool cmp(double A,double B)
{
    return A>B;
}

void add(int u,int v,double w)
{
//printf("%d %d %lf\n",u,v,w);
    e[++tot]=(Tway){v,head[u],w};head[u]=tot;
    e[++tot]=(Tway){u,head[v],0};head[v]=tot;
}

void init()
{
    n=read();m=read();sum=0;
    for(int i=1;i<=n;++i)
    {
        p[i]=read();r[i]=read();d[i]=read();
        sum+=p[i];
    }
    for(int i=1;i<=m;++i)
        v[i]=read();
    sort(v+1,v+m+1,cmp);
    R=1.0*sum/v[1]+1.0;L=0;
    for(int i=1;i<m;++i)
         v[i]-=v[i+1];
}

bool bfs()
{
    memset(dep,-1,sizeof(dep));
    q.push(S);dep[S]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nex)
        {
            int v=e[i].v;
            if(dep[v]==-1 && e[i].w>eps)
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return ~dep[T];
}

double dfs(int x,double flow)
{
    if(x==T || flow<eps)
        return flow;
    double used=0,w;
    for(int &i=cur[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(e[i].w>eps && dep[v]==dep[x]+1)
        {
            w=dfs(v,min(flow-used,e[i].w));
            e[i].w-=w;e[i^1].w+=w;used+=w;
            if(fabs(flow-used)<eps)
                return flow;
        }
    }
    return used;
}

double dinic()
{
    double ret=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(head));
        ret+=dfs(S,INF);
    }
    return ret;
}

void rebuild(double x)
{
    tot=1;memset(head,0,sizeof(head));
    for(int i=1;i<=n;++i)
    {
        add(S,i,p[i]);
        sr[i*2-1]=r[i],sr[i*2]=d[i]+x;
    }
    sort(sr+1,sr+2*n+1);cnt=n;
    for(int i=1;i<=m;++i)
    {
        for(int j=2;j<=2*n;++j)
        {
            if(sr[j]-sr[j-1]<eps)
                continue;
            ++cnt;add(cnt,T,i*v[i]*(sr[j]-sr[j-1]));
            for(int k=1;k<=n;++k)
            {
                if(r[k]-sr[j-1]<eps && (d[k]+x-sr[j]>-eps))
                    add(k,cnt,v[i]*(sr[j]-sr[j-1]));
            }
        }
    }
}

void solve()
{
    double tsum=sum;S=0;T=2*m*n+n+1;cnt=0;
    while(L+eps<R)
    {
        double mid=(L+R)/2.0;
        rebuild(mid);
        double mx=dinic();
//printf("tsum:%lf mx:%lf\n",tsum,mx); 
        if(tsum-mx<eps)
            R=mid;
        else
            L=mid;
    }
    printf("%lf\n",L);
}

int main()
{
    freopen("LGP2570.in","r",stdin);
    freopen("LGP2570.out","w",stdout);

    int cas=read();
    while(cas--)
    {
        init();
        solve();
    }
    
    return 0;
}
