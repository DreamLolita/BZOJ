#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=2e9;
const int N=2e5+10;
int n,tx,ty,txx,tyy;
LL X[N],Y[N],dat[N];

struct Tnode
{
	int x,y,k,ans,id;
	bool operator < (const Tnode &A)const
	{
		if(x==A.x)
			return y<A.y;
		return x<A.x;
	}
};
Tnode a[N];

struct Tbit
{
	int tr[N];
	int lowbit(int x){
		return x&(-x);
	}
	
	void add(int x,int v)
	{
		for(;x<=n;x+=lowbit(x))
			tr[x]+=v;
	}
	
	int query(int x)
	{
		int ret=0;
		for(;x;x-=lowbit(x))
			ret+=tr[x];
		return ret;	
	}
};
Tbit BIT;

bool cmp(Tnode A,Tnode B)
{
	return A.id<B.id;
}

void update(int &x,int &y)
{
	int mx=max(abs(x),abs(y));
	int d=((LL)INF+mx-1)/mx;
	x*=d;y*=d;
	++x;
}

void init()
{
	for(int i=1;i<=n;++i)
		dat[i]=X[i];
	sort(dat+1,dat+n+1);
	int sz=unique(dat+1,dat+n+1)-dat;
	for(int i=1;i<=n;++i)
		a[i].x=lower_bound(dat+1,dat+sz+1,X[i])-dat;
		
	for(int i=1;i<=n;++i)
		dat[i]=Y[i];
	sort(dat+1,dat+n+1);
	sz=unique(dat+1,dat+n+1)-dat;
	for(int i=1;i<=n;++i)
		a[i].y=lower_bound(dat+1,dat+sz+1,Y[i])-dat;
}

void solve(int L,int R,int l,int r)
{
	if(L==R)
	{
		for(int i=l;i<=r;++i)
			a[i].ans=L;
		return;
	}
	int Mid=(L+R)>>1,mid=l-1;
	sort(a+l,a+r+1);
	
	for(int i=l;i<=r;++i)
	{
		int res=BIT.query(a[i].y);
		if(a[i].id<=Mid || res>=a[i].k)
		{
			BIT.add(a[i].y,1);
			++mid;swap(a[mid],a[i]);
		}
		else
			a[i].k-=res;
	}
	
	for(int i=l;i<=mid;++i)
		BIT.add(a[i].y,-1);
	
	if(l<=mid)
		solve(L,Mid,l,mid);
	if(r>mid)
		solve(Mid+1,R,mid+1,r);
}

int main()
{
//	freopen("BZOJ3833.in","r",stdin);
//	freopen("BZOJ3833.out","w",stdout);
	
	scanf("%d%d%d%d%d",&n,&tx,&ty,&txx,&tyy);
	if(1ll*tx*tyy==1ll*ty*txx)
		update(tx,ty);
	if(1ll*tx*tyy<1ll*ty*txx)
		swap(tx,txx),swap(ty,tyy);
	for(int i=1;i<=n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i].id=i;
		X[i]=1ll*x*tyy-1ll*txx*y;
		Y[i]=1ll*tx*y-1ll*x*ty;
	}	
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i].k);
	init();
	solve(1,n,1,n);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		printf("%d%c",a[i].ans,i==n?'\n':' ');
	
	return 0;
}
