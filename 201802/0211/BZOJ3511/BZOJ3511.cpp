#include<bits/stdc++.h> 
#define build_edge(u,v,c) add_edge(u,v,c),add_edge(v,u,0)  
using namespace std;  

const int INF=1e9;
const int N=1e5+10;
const int M=1e6+10;
int n,m,S,T,totans;
int etop,h[N],lev[N],cur[N];  
bool vis[N];
queue<int> q;  

struct edges
{  
    int to,pre,resf;  
}e[M];  


int add_edge(int u,int v,int c)  
{  
    etop++;  
	e[etop].to=v;  
    e[etop].pre=h[u];  
    h[u]=etop;  
    e[etop].resf=c;  
    return 0;  
}  

bool bfs(int s,int t)  
{  
    memset(vis,false,sizeof(vis));  
    memset(lev,0,sizeof(lev));  
    while(!q.empty()) q.pop();  
    q.push(s);lev[s]=0;vis[s]=true;  
    while(!q.empty())  
    {  
        int x=q.front();q.pop();  
        for(int i=h[x];i;i=e[i].pre)  
            if(!vis[e[i].to]&&e[i].resf)  
            {  
                vis[e[i].to]=true;  
                lev[e[i].to]=lev[x]+1;  
                q.push(e[i].to);  
            }  
    }  
    return vis[t];  
}  

int dfs(int s,int t,int a)  
{  
    if(s==t||!a) return a;  
    int flow=0,f;  
    for(int &i=cur[s];i;i=e[i].pre)  
        if(lev[e[i].to]==lev[s]+1&&(f=dfs(e[i].to,t,min(a,e[i].resf)))>0)  
        {  
            a-=f;flow+=f;e[i].resf-=f;  
            e[((i-1)^1)+1].resf+=f;  
            if(!a) break;  
        }  
    return flow;  
}  

int main()  
{  
	freopen("BZOJ3511.in","r",stdin);
	freopen("BZOJ3511.out","w",stdout);
	
	scanf("%d%d",&n,&m);  
    S=0;T=n+2*m+1;totans=0;  
    build_edge(S,1,INF);  
    build_edge(n,T,INF);  
    
    for(int i=2;i<n;i++)  
    {  
        int va;scanf("%d",&va);  
        build_edge(S,i,va);totans+=va;  
    }  
    
    for(int i=2;i<n;i++)  
    {  
        int vb;scanf("%d",&vb);  
        build_edge(i,T,vb);totans+=vb;  
    }  
    
    for(int i=1;i<=m;i++)  
    {  
        int x,y,a,b,c;
		scanf("%d%d%d%d%d",&x,&y,&a,&b,&c);  
        int A=i+n,B=i+n+m;totans+=a+b;  
        add_edge(x,y,c);add_edge(y,x,c);  
        build_edge(S,A,a);build_edge(B,T,b);  
        build_edge(A,x,INF);build_edge(A,y,INF);  
        build_edge(x,B,INF);build_edge(y,B,INF);  
    }  
    
    int flow=0;  
    while(bfs(S,T))  
    {  
        for(int i=S;i<=T;i++)  
            cur[i]=h[i];  
        flow+=dfs(S,T,INF);  
    }  
    printf("%d\n",totans-flow); 
	 
    return 0;  
}  
