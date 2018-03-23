#include<cstdio>
typedef long long ll;
const int N=20010,M=200010,E=M*30;
int n,m,i,x,y,g[N],v[N<<1],nxt[N<<1],ok[N<<1],ed;
int all,f[N],son[N],now,pos[N];
int G[N],V[E],NXT[E],ED,p[M],cnt;
ll a[N],ans[M];
struct Q{int x,y;}q[M];
struct B{
  ll a[60];
  B(){for(int i=0;i<60;i++)a[i]=0;}
  inline void ins(ll x){for(int i=59;~i;i--)if(x>>i&1){if(a[i])x^=a[i];else{a[i]=x;break;}}}
  inline ll ask(){
    ll t=0;
    for(int i=59;~i;i--)if((t^a[i])>t)t^=a[i];
    return t;
  }
}h[N],b;
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline void read(ll&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];ok[ed]=1;g[x]=ed;}
inline void ADD(int x,int y){V[++ED]=y;NXT[ED]=G[x];G[x]=ED;}
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
  pos[x]=z;
  h[x]=h[y];
  h[x].ins(a[x]);
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs(v[i],x,z);
}
void solve(int x){
  if(!G[x])return;
  f[0]=all=son[x],findroot(x,now=0);
  int i;
  pos[now]=now;
  h[now]=B();
  h[now].ins(a[now]);
  for(i=g[now];i;i=nxt[i])if(ok[i])dfs(v[i],now,v[i]);
  for(cnt=0,i=G[x];i;i=NXT[i])p[++cnt]=V[i];G[x]=0;
  for(i=1;i<=cnt;i++)if(pos[q[p[i]].x]==pos[q[p[i]].y])ADD(pos[q[p[i]].x],p[i]);
  else{
    b=h[q[p[i]].x];
    B*y=h+q[p[i]].y;
    for(int j=59;~j;j--)if(y->a[j])b.ins(y->a[j]);
    ans[p[i]]=b.ask();
  }
  for(i=g[now];i;i=nxt[i])if(ok[i])ok[i^1]=0,solve(v[i]);
}
int main(){
  read(n),read(m);
  for(ed=i=1;i<=n;i++)read(a[i]);
  for(i=1;i<n;i++)read(x),read(y),add(x,y),add(y,x);
  for(i=1;i<=m;i++){
    read(q[i].x),read(q[i].y);
    if(q[i].x==q[i].y)ans[i]=a[q[i].x];else ADD(1,i);
  }
  son[1]=n;solve(1);
  for(i=1;i<=m;i++)printf("%lld\n",ans[i]);
  return 0;
}
