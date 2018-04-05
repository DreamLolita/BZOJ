#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define pb push_back
const int N=100010;
int n,m,u,v,cnt,c2,tp,ans,D,s[N],dfn[N],low[N],vis[N],bel[N];
vector<int> e[N],E[N];
void dfs(int u,int f) {
	dfn[u]=low[u]=++cnt,s[tp++]=u;
	for (int v:e[u]) if (v!=f) {if (!dfn[v]) dfs(v,u);low[u]=min(low[u],low[v]);}
	if (low[u]==dfn[u]) { c2++;do {bel[s[--tp]]=c2;}while (s[tp]!=u);}
}
int dfs2(int u,int f) {
	if (E[u].size()<2) ans--;vis[u]=1;
	int d[3]={0,0,0};
	for (int v:E[u]) if (v!=f) {
		d[0]=dfs2(v,u);sort(d,d+3);
		D=max(D,d[1]+d[2]);
	}
	return d[2]+1;
}
int main() {
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	scanf("%d%d",&n,&m);ans=n-1;
	rep(i,0,m) scanf("%d%d",&u,&v),e[u].pb(v),e[v].pb(u);
	rep(i,1,n+1) if (!dfn[i]) dfs(i,0);
	rep(u,1,n+1) for (int v:e[u]) if (bel[u]!=bel[v]) E[bel[u]].pb(bel[v]);
	rep(i,1,c2+1) if (!vis[i]) D=0,dfs2(i,0),ans-=(D==0)?-1:D-2;
	printf("%d\n",ans);
}
