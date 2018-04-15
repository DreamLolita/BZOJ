#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int N=1e4+10;
int T,n,m,lim;
int a[N],pos[N];
LL ans;
vector<pii>vl[N],vr[N];

struct Tnode
{
	int l,r,id;
	LL ans;
};
Tnode q[N];

bool cmp1(Tnode A,Tnode B)
{
	if(pos[A.l]^pos[B.l])
		return A.l<B.l;
	return A.r<B.r;
}

bool cmp2(Tnode A,Tnode B)
{
	return A.id<B.id;
}

int gcd(int a,int b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}

void init()
{
	scanf("%d",&n);lim=(int)sqrt(n);
	for(int i=1;i<=n;++i)
		pos[i]=(i-1)/lim+1;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		vl[i].clear();vr[i].clear();
	}
	vr[0].clear();vl[n+1].clear();
	for(int i=1;i<=n;++i)
	{
		int x=a[i],y=i;
		for(int j=0;j<vr[i-1].size();++j)
		{
			int t=gcd(vr[i-1][j].first,a[i]);
			if(t!=x)
			{
				vr[i].push_back(mkp(x,y));
				x=t;
			}
			y=vr[i-1][j].second;
		}
		vr[i].push_back(mkp(x,y));
	}
	for(int i=n;i;--i)
	{
		int x=a[i],y=i;
		for(int j=0;j<vl[i+1].size();++j)
		{
			int t=gcd(vl[i+1][j].first,a[i]);
			if(t!=x)
			{
				vl[i].push_back(mkp(x,y));
				x=t;
			}
			y=vl[i+1][j].second;
		}
		vl[i].push_back(mkp(x,y));
	}
}

void updatel(int x,int y,int v)
{
	int t=x;LL tmp=0;
	for(int i=0;i<vl[x].size();++i)
	{
		int w=vl[x][i].first,p=vl[x][i].second;
		if(p<=y)
			tmp+=1ll*(p-t+1)*w,t=p+1;
		else
		{
			tmp+=1ll*(y-t+1)*w;
			break;
		}
	}
	ans+=1ll*tmp*v;
}

void updater(int x,int y,int v)
{
	int t=x;LL tmp=0;
	for(int i=0;i<vr[x].size();++i)
	{
		int w=vr[x][i].first,p=vr[x][i].second;
		if(p>=y)
			tmp+=1ll*(t-p+1)*w,t=p-1;
		else
		{
			tmp+=1ll*(t-y+1)*w;
			break;
		}
	}
	ans+=1ll*tmp*v;
}

void solve()
{
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp1);
	int l=1,r=0;ans=0;
	for(int i=1;i<=m;++i)
	{
		for(;r<q[i].r;++r)	updater(r+1,l,1);
		for(;r>q[i].r;--r)	updater(r,l,-1);
		for(;l<q[i].l;++l)	updatel(l,r,-1);
		for(;l>q[i].l;--l)	updatel(l-1,r,1);
		q[i].ans=ans;
	}
	sort(q+1,q+m+1,cmp2);
	for(int i=1;i<=m;++i)
		printf("%I64d\n",q[i].ans);
}

int main()
{
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		init();
		solve();
	}
	
	return 0;
}
