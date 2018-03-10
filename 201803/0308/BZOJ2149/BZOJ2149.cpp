#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef pair<int,LL> pii;
const LL INF=(LL)1e18;
const int N=1e5+10;
int n,mx;
int a[N],b[N],d[N],f[N],id[N];
LL ans,c[N],g[N];
vector<pii>vc;

bool cmp(int x,int y)
{
	if(d[x]==d[y])
		return x<y;
	return d[x]<d[y];
}

pii operator -(pii A,pii B){
	return mkp(A.first-B.first,A.second-B.second);
}

LL operator *(pii A,pii B){
	return A.first*B.second-A.second*B.first;
}

void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1,cnt=0;
	solve(l,mid);
	for(int i=l;i<=r;++i)
		id[++cnt]=i;
	sort(id+1,id+cnt+1,cmp);
	pii now;
	int mx=-1,L,R,m1,m2;
	for(int i=1;i<=cnt;++i)
		if(id[i]<=mid)
		{
			if(f[id[i]]<mx)
				continue;
			if(id[i]!=0 && !f[id[i]])
				continue;
			if(f[id[i]]>mx)
				vc.clear(),mx=f[id[i]];
			now=mkp(2*d[id[i]],c[id[i]]+2*g[id[i]]);
			while(vc.size()>1 && (vc[vc.size()-1]-vc[vc.size()-2])*(now-vc[vc.size()-1])<=0)
				vc.pop_back();
			vc.push_back(now);
		}
		else
		{
			if(f[id[i]]>mx+1)
				continue;
			if(f[id[i]]<mx+1)
				g[id[i]]=INF;
			f[id[i]]=mx+1;
			L=0,R=vc.size()-1;
			while(L+2<R)
			{
				m1=(R-L)/3+L;m2=(R-L)/3*2+L;
				if(1ll*vc[m1].first*id[i]+vc[m1].second>1ll*vc[m2].first*id[i]+vc[m2].second)
					L=m1+1;
				else
					R=m2-1;
			}
			for(int j=L;j<=R;++j)
				g[id[i]]=min(g[id[i]],(1ll*vc[j].first*id[i]+1ll*id[i]*(id[i]-1)+vc[j].second)/2+a[id[i]]+b[id[i]]);
		}
	solve(mid+1,r);
}

int main()
{
	freopen("BZOJ2149.in","r",stdin);
	freopen("BZOJ2149.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
	{
		g[i]=INF;d[i]=a[i]-i;
		c[i]=1ll*i*(i+1)-2ll*i*a[i]-2ll*a[i];
	}
	solve(0,n);
	for(int i=1;i<=n;++i)
	{
		g[i]+=1ll*(n-i)*(a[i]+1)+1ll*(n-i)*(n-i-1)/2;
		if(mx<f[i])
			mx=f[i],ans=g[i];
		else
		if(mx==f[i])
			ans=min(ans,g[i]);
	}
	printf("%d %lld\n",mx,ans);
	
	return 0;
}
