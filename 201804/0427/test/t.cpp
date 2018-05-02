#include<cstdio>
#include<vector>
using namespace std;
vector<int> G[500005];
int dep[500005],n,m,s,f[500005][22],u,v,x,y; bool vis[500005];
struct point{
    int x,y;
};
void getdep(int root,int deep){
    vis[root]=true;
    dep[root]=deep;
    int sz=G[root].size();
    for(int i=0;i<sz;i++)
        if(!vis[G[root][i]]) getdep(G[root][i],deep+1),f[G[root][i]][0]=root;
    vis[root]=false;
}
point changedep(int p1,int p2){
    if(dep[p1]==dep[p2]) return (point){p1,p2};
    int p11,p22;
    if(dep[p1]>dep[p2]) p11=p1,p22=p2;
    else p11=p2,p22=p1; point ret;
	int t=dep[p11]-dep[p22];
	for(int i=0;i<21;++i)
		if(t&(1<<i))
			p11=f[p11][i];
	return (point){p11,p22};
 //   for(int i=0;;i++)
//        if(dep[f[p11][i]]<=dep[p22]) return changedep(f[p11][max(i-1,0)],p22);
}
int divLCA(int p1,int p2){
    if(p1==p2) return p1;
    for(int jump=1;;jump++)
        if(f[p1][jump]==f[p2][jump]) return divLCA(f[p1][jump-1],f[p2][jump-1]);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
    getdep(s,0);
    for(int j=1;j<=21;j++)
    for(int i=1;i<=n;i++)
        f[i][j]=f[f[i][j-1]][j-1];
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        point tmp;
        tmp=changedep(x,y);
        printf("%d\n",divLCA(tmp.x,tmp.y));
    }
}
