#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50010,M=100010,U=M*20;
int n,m,i,x,y,z,d[N],g[N],v[N<<2],nxt[N<<2],ed,vis[N],h,t,q[N],ans[M];
struct Q{int x,y;}que[M];
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline void add(int x,int y){d[x]++;v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
namespace Graph{
int n,m,i,id[N][3],g[N],v[N<<1],nxt[N<<1],ok[N<<1],ed;
int all,f[N],son[N],now,pos[N],last[N],cur,dis[3][N];
int G[N],V[U],NXT[U],ED,p[N*3],cnt;
struct E{int x,y,p;E(){}E(int _x,int _y,int _p){x=_x,y=_y,p=_p;}}e[N*3];
inline bool cmp(const E&a,const E&b){return a.x==b.x?a.y<b.y:a.x<b.x;}
inline void add(int x,int y){
  v[++ed]=y;ok[ed]=1;nxt[ed]=g[x];g[x]=ed;
  v[++ed]=x;ok[ed]=1;nxt[ed]=g[y];g[y]=ed;
}
inline void ADD(int x,int y){V[++ED]=y;NXT[ED]=G[x];G[x]=ED;}
inline void newedge(int x,int y,int z){
  n++;
  id[n][0]=x,id[n][1]=y,id[n][2]=z;
  e[++m]=E(min(x,y),max(x,y),n);
  e[++m]=E(min(x,z),max(x,z),n);
  e[++m]=E(min(y,z),max(y,z),n);
}
void findroot(int x,int y){
  son[x]=1;f[x]=0;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y){
    findroot(v[i],x);
    son[x]+=son[v[i]];
    if(son[v[i]]>f[x])f[x]=son[v[i]];
  }
  if(all-son[x]>f[x])f[x]=all-son[x];
  if(f[x]<f[now])now=x;
}
void dfs(int x,int y,int z){
  for(int i=0;i<3;i++){
    pos[id[x][i]]=z;
    last[id[x][i]]=cur;
    p[++cnt]=id[x][i];
  }
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs(v[i],x,z);
}
inline void bfs(int S,int*d){
  int i,x,y,h,t;static int q[N];
  for(i=1;i<=cnt;i++)d[p[i]]=U;
  d[q[h=t=1]=S]=0;
  while(h<=t)for(i=::g[x=q[h++]];i;i=::nxt[i]){
    y=::v[i];
    if(d[y]<U||last[y]<cur)continue;
    d[q[++t]=y]=d[x]+1;
  }
}
void solve(int x){
  if(!G[x])return;
  f[0]=all=son[x],findroot(x,now=0);
  int i,j,A,B;
  cur++;
  for(cnt=0,i=g[now];i;i=nxt[i])if(ok[i])dfs(v[i],now,v[i]);
  for(i=0;i<3;i++){
    p[++cnt]=A=id[now][i];
    pos[A]=now,last[A]=cur;
  }
  for(i=0;i<3;i++)bfs(id[now][i],dis[i]);
  for(cnt=0,i=G[x];i;i=NXT[i])p[++cnt]=V[i];G[x]=0;
  for(i=1;i<=cnt;i++){
    A=que[p[i]].x,B=que[p[i]].y;
    if(pos[A]==pos[B])
      if(pos[A]==now)ans[p[i]]=1;
      else ADD(pos[A],p[i]);
    else for(j=0;j<3;j++)ans[p[i]]=min(ans[p[i]],dis[j][A]+dis[j][B]);
  }
  for(i=g[now];i;i=nxt[i])if(ok[i])ok[i^1]=0,solve(v[i]);
}
void Main(){
  sort(e+1,e+m+1,cmp);
  for(ed=i=1;i<m;i++)if(e[i].x==e[i+1].x&&e[i].y==e[i+1].y)add(e[i].p,e[i+1].p);
  son[1]=n;solve(1);
}
}
int main(){
  read(n);
  for(i=1;i<n;i++)add(i,i+1),add(i+1,i);
  add(1,n),add(n,1);
  for(i=1;i<=n-3;i++)read(x),read(y),add(x,y),add(y,x);
  for(h=i=1;i<=n;i++)if(d[i]==2)q[++t]=i;
  while(h<=t){
    x=q[h++];
    if(d[x]!=2)continue;
    vis[x]=1,y=0;
    for(i=g[x];i;i=nxt[i])if(!vis[v[i]]){
      if(y)z=v[i];else y=v[i];
      if((--d[v[i]])==2)q[++t]=v[i];
    }
    Graph::newedge(x,y,z);
  }
  read(m);
  for(i=1;i<=m;i++){
    read(x),read(y);
    if(x!=y)que[i].x=x,que[i].y=y,Graph::ADD(1,i),ans[i]=U;
  }
  Graph::Main();
  for(i=1;i<=m;i++)printf("%d\n",ans[i]);
  return 0;
}
