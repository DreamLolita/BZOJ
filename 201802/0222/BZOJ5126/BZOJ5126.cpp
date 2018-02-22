#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

typedef long long LL;
const int N=2e5+10;;
int n,f[N],p[N],m[N],s[N],w[N];
int t,q[N];
int fa[N],vf[N],vis[N];
LL ans;
set<pii>T[N];

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

void merge(int x,int y)
{
	int fx=findf(x),fy=findf(y);
	if(fx!=fy)
		fa[fx]=fy;
}

LL calc(int x)
{
	int y=f[x];
	LL pre=T[y].rbegin()->first;
	T[y].erase(pii(w[x],x));
	LL now=T[y].rbegin()->first;
	T[y].insert(pii(w[x],x));
	return now-pre;
}

int main()
{
	freopen("BZOJ5126.in","r",stdin);
	freopen("BZOJ5126.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d%d",&f[i],&p[i],&m[i],&s[i]);
	for(int i=1;i<=n;++i)
		T[i].insert(pii(0,0));
	for(int i=1;i<=n;++i)
	{
		w[i]=m[f[i]]-p[i];
		T[f[i]].insert(pii(w[i],i));
	}
	for(int i=1;i<=n;++i)
		ans+=1ll*(T[i].rbegin()->first)*s[i];
		
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		merge(i,f[i]);
		
	for(int i=1;i<=n;++i)
		if(!vf[findf(i)])
		{
			vf[fa[i]]=1;
			int j;
			for(j=i;!vis[j];j=f[j])
				vis[j]=1;
				
			q[t=1]=j;
			for(int k=f[j];k!=j;k=f[k])
				q[++t]=k;
			if(t==1)
				continue;
				
			LL tmp=-(1LL<<60);
			for(j=1;j<=t;j++)
				tmp=max(tmp,calc(q[j]));
			ans+=tmp;
		}
	printf("%lld",ans);
	
	return 0;
}
