#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <ctime>
#include <string>
#define N 200010

using namespace std;

pair<int,int> nq[N];
int n,m,u,v,cnt,g,ng;
struct stp{
  int l,r,g;
}A[N<<2],Q[N<<2],tmp1[N<<2],tmp2[N<<2];
struct edge{
  int t,nx;
}E[N<<2];
int B[N*100],Ans[N],G[N],dis1[N],dis2[N],vis[N],tmp3[N*100],tmp4[N*100];
queue<int> q;

inline void reaD(int &x){
  char c=getchar(); x=0;
  for(;c<48||c>57;c=getchar());for(;c>=48&&c<=57;x=x*10+c-48,c=getchar());
}

inline int check(int l,int r,int x){
  int mid,Ans;
  while(l<r) B[mid=l+r>>1]>=x?r=mid:l=mid+1;
  return r;
}

inline void spfa(int x,int l,int r,int *dis){
  for(int i=l;i<=r;i++) dis[B[i]]=1<<30,vis[B[i]]=0;
  vis[x]=1; dis[x]=0;
  q.push(x); 
  while(!q.empty()){
    int u=q.front(); vis[u]=0; q.pop();
    for(int i=G[u];i;i=E[i].nx)
      if(dis[u]+1<dis[E[i].t]&&B[check(l,r,E[i].t)]==E[i].t){
    dis[E[i].t]=dis[u]+1;
    if(!vis[E[i].t]){
      q.push(E[i].t);
      vis[E[i].t]=1;
      if(dis[q.front()]>dis[q.back()]) swap(q.front(),q.back());
    }
      }
  }
}

inline void Insert(int x,int y){
  E[++cnt].t=y; E[cnt].nx=G[x]; G[x]=cnt;
  E[++cnt].t=x; E[cnt].nx=G[y]; G[y]=cnt;
}

inline int GetAns(int x,int y){
  int Ans1=min(dis1[x]+dis1[y],dis1[x]+dis2[y]+1),
    Ans2=min(dis2[x]+dis1[y]+1,dis2[x]+dis2[y]);
  return min(Ans1,Ans2);
}

void solve(int l,int r,int x,int y,int a,int b){
  if(a>b) return;
  int Min=1<<30,w;
  for(int i=l;i<=r;i++){
    int pp=check(x,y,A[i].l),qq=check(x,y,A[i].r);
    if(pp<qq) swap(qq,pp);
    if(max(pp-qq+1,y-x+1-pp+qq)<Min) Min=max(pp-qq+1,y-x+1-pp+qq),w=i;
  }
  if(A[w].l>A[w].r) swap(A[w].l,A[w].r);
  spfa(A[w].l,x,y,dis1); spfa(A[w].r,x,y,dis2);

  int k1=0,k2=0,k3=0,k4=0,k5=0,k6=0;
  for(int i=a;i<=b;i++){
    if((Q[i].l==A[w].l&&Q[i].r==A[w].r)||(Q[i].r==A[w].l&&Q[i].l==A[w].r)){
      Ans[Q[i].g]=1; continue;
    }
    Ans[Q[i].g]=min(Ans[Q[i].g],GetAns(Q[i].l,Q[i].r));
    if(Q[i].l>A[w].l&&Q[i].l<A[w].r&&Q[i].r>A[w].l&&Q[i].r<A[w].r) tmp1[++k1]=Q[i];
    if((Q[i].r<A[w].l||Q[i].r>A[w].r)&&(Q[i].l<A[w].l||Q[i].l>A[w].r)) tmp2[++k2]=Q[i];
  }
  for(int i=1;i<=k1;i++) Q[a+i-1]=tmp1[i];
  for(int i=1;i<=k2;i++) Q[a+k1+i-1]=tmp2[i];
  for(int i=x;i<=y;i++){
    if(B[i]>=A[w].l&&B[i]<=A[w].r) tmp3[++k3]=B[i];
    if(B[i]<=A[w].l||B[i]>=A[w].r) tmp4[++k4]=B[i];
  }
  for(int i=1;i<=k3;i++) B[x+i-1]=tmp3[i];
  for(int i=1;i<=k4;i++) B[x+k3+i-1]=tmp4[i];
  for(int i=l;i<=r;i++)
    if(i!=w)
      if(A[i].l>=A[w].l&&A[i].r<=A[w].r) tmp1[++k5]=A[i];
      else tmp2[++k6]=A[i];
  for(int i=1;i<=k5;i++) A[l+i-1]=tmp1[i];
  for(int i=1;i<=k6;i++) A[l+k5+i-1]=tmp2[i];

  solve(l+k5,l+k5+k6-1,x+k3,x+k3+k4-1,a+k1,a+k1+k2-1);
  solve(l,l+k5-1,x,x+k3-1,a,a+k1-1);
}

int main(){
	freopen("BZOJ4449.in","r",stdin);
	freopen("BZOJ4449.out","w",stdout);
  reaD(n);
  for(int i=1;i<=n-3;i++){
    reaD(A[i].l),reaD(A[i].r),Insert(A[i].l,A[i].r);
    if(A[i].l>A[i].r) swap(A[i].r,A[i].l);//бнбн
  }
  for(int i=1;i<=n;i++) B[i]=i;
  reaD(m);
  for(int i=1;i<=m;i++){
    reaD(Q[i].l);reaD(Q[i].r); Q[i].g=i;
    nq[i].first=Q[i].l; nq[i].second=Q[i].r;
    if(Q[i].l%n+1==Q[i].r||Q[i].r%n+1==Q[i].l) Ans[i]=1;
    else if(Q[i].l==Q[i].r) Ans[i]=0;
    else Q[++g]=Q[i];
  }
  for(int i=1;i<=n;i++) Insert(i,i%n+1);
  for(int i=1;i<=m;i++) Ans[i]=1<<30;
  solve(1,n-3,1,n,1,g);
  for(int i=1;i<=m;i++)
    if(Ans[i]!=(1<<30)) printf("%d\n",Ans[i]);
    else{
      if(nq[i].first>nq[i].second) swap(nq[i].first,nq[i].second);
      printf("%d\n",min(nq[i].second-nq[i].first,nq[i].first+n-nq[i].second));
    }
  return 0;
}
