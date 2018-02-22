#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

const int N=4e4+10;
int n,m,L,R,now;
int a[N],tr[N],f[N],g[N];

inline void _reset()
{
	memcpy(g,f,sizeof(g));
	memset(f,0x3f,sizeof(f));
	memset(tr,0,sizeof(tr));
	L=1;R=now=0;
}

inline int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x];
	return ret;	
}

inline void update(int x,int v)
{
	for(;x<=n;x+=lowbit(x))
		tr[x]+=v;
}

inline void change(int l,int r)
{
	while(R<r)
		now+=(R-L+1-query(a[R+1])),update(a[++R],1);
	while(L<l)
		now-=query(a[L]-1),update(a[L++],-1);
	while(L>l)
		now+=query(a[L-1]-1),update(a[--L],1);
	while(R>r)
		now-=(R-L+1-query(a[R])),update(a[R--],-1);
}

inline void solve(int l,int r,int dl,int dr)
{
	int mid=(l+r)>>1,dm=dl;
	for(int i=dl;i<=min(dr,mid-1);++i)
	{
		change(i+1,mid);
		int t=g[i]+now;
		if(t<f[mid])
			f[mid]=t,dm=i;
	}
	if(l<mid)
		solve(l,mid-1,dl,dm);
	if(r>mid)
		solve(mid+1,r,dm,dr);
}

int main()
{
	freopen("BZOJ5125.in","r",stdin);
	freopen("BZOJ5125.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		update(a[i],1);
		f[i]=f[i-1]+i-query(a[i]);
	}
	for(int i=2;i<=m;++i)
	{
		_reset();
		solve(i,n,i-1,n);
	}
	printf("%d\n",f[n]);
	
	return 0;
}
