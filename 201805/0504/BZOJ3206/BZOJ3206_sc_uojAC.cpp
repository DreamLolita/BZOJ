#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 6e+5 + 10;
const int maxk = 20 + 5;
const int INF = 0x3fffffff;

int n,m,k,ta[maxn];ll a[maxk];
int lab[maxn],labn;
int llg2[maxn];

struct edge{
	int u,v,d;
}e[maxn],ek[maxk];

struct DSU{
	int f[maxn];
	
	void init(int x){memset(f,0,x<<2);}
	
	int fa(int x)
	{
		if(!f[x]) return x;
		return f[x]=fa(f[x]);
	}
	
	bool merge(int x,int y)
	{
		x=fa(x);y=fa(y);
		if(x==y) return false;
		if(x<y) swap(x,y);
		f[x]=y;return true;
	}
	
	void relable()
	{
		int i;
		labn=1;memset(a,0,sizeof(a));
		for(i=1;i<=n;i++) if(!f[i]) lab[i]=labn++;
		for(i=1;i<=n;i++) lab[i]=lab[fa(i)],a[lab[i]]+=ta[i];//,printf("%d in lab:%d\n",i,lab[i]);
	}
}L,K;

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	return x;
}

bool cmpd(edge a,edge b){return a.d<b.d;}
void input()
{
	int i;
	
	n=read();m=read();k=read();
	for(i=0;i<m;i++)
	{
		e[i].u=read();e[i].v=read();e[i].d=read();
	}
	for(i=m;i<m+k;i++)
	{
		e[i].u=ek[i-m].u=read();e[i].v=ek[i-m].v=read();e[i].d=-1;
	}
	for(i=1;i<=n;i++) ta[i]=read();
	for(i=0;i<20;i++) llg2[1<<i]=i;
}

void build()
{
	int i,j;
	
	sort(e,e+m+k,cmpd);
	for(i=0;i<m+k;i++)
	{
		if(K.merge(e[i].u,e[i].v)) if(~e[i].d)
		{
			L.merge(e[i].u,e[i].v);
			e[i].d=INF;
		}
		if(!~e[i].d) e[i].d=INF;
	}
	L.relable();
	
	sort(e,e+m+k,cmpd);K.init(n+1);
	
	j=0;
	for(i=0;i<m+k;i++)
	{
		//printf("visit: %d-%d d=%d\n",e[i].u,e[i].v,e[i].d);
		if(K.merge(lab[e[i].u],lab[e[i].v])) e[j++]=e[i];//,printf("select: %d-%d d=%d\n",e[i].u,e[i].v,e[i].d);
	}
	m=j;n=labn;
}

int tag[maxk];ll ans,siz[maxk];
vector<pair<int,bool> > nxt[maxk];
inline void addedge(int u,int v,bool type)
{//printf("addedge %d-%d tp=%d\n",u,v,type);
	nxt[u].push_back(make_pair(v,type));
	nxt[v].push_back(make_pair(u,type));
}

void dfs(int x,int f)
{
	int i,v,j,d;
	
	siz[x]=a[x];
	for(i=0;i<nxt[x].size();i++) if((v=nxt[x][i].first)!=f)
	{
		dfs(v,x);tag[x]^=tag[v];siz[x]+=siz[v];
		if(nxt[x][i].second)
		{
			j=llg2[tag[v]&-tag[v]];//cerr<<j<<endl;
			d=e[j].d;
			ans+=siz[v]*d;
		}
	}
}

void solve()
{
	int S,i;ll fans=0;
	
	//printf("n=%d\n",n);
	//for(i=0;i<k;i++) printf("k type edge : %d-%d\n",e[i].u,e[i].v);
	//for(i=0;i<m;i++) printf("m type edge : %d-%d d=%d\n",e[i].u,e[i].v,e[i].d);
	
	for(S=0;S<(1<<k);S++)
	{
		K.init(n);memset(tag,0,sizeof(tag));
		for(i=1;i<n;i++) nxt[i].clear();
		for(i=0;i<k;i++) if(S>>i&1)
		{
			if(!K.merge(lab[ek[i].u],lab[ek[i].v])) goto Fail;
			addedge(lab[ek[i].u],lab[ek[i].v],true);
		}
		for(i=0;i<m;i++) 
		{
			if(!K.merge(lab[e[i].u],lab[e[i].v])) tag[lab[e[i].u]]|=1<<i,tag[lab[e[i].v]]|=1<<i;
			else addedge(lab[e[i].u],lab[e[i].v],false);
		}
		
		ans=0;
		dfs(1,-1);//printf("S=%d ans=%lld\n",S,ans);
		fans=max(fans,ans);
		
		Fail:;
	}
	cout<<fans<<endl;
}

int main()
{
	freopen("lg3639.in","r",stdin);
	freopen("lg3639.out","w",stdout);
	
	input();
	build();
	solve();
	
	return 0;
}

