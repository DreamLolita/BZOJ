#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2e5+10;
int n;
int A[N],B[N],C[N],pos[N],tr[N];
LL ans;

int lowbit(int x)
{
	return x&(-x);
}

void update(int x,int v)
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

void solve(int *x,int *y)
{
	for(int i=1;i<=n;++i)
		pos[x[i]]=i,tr[i]=0;
	for(int i=n;i;--i)
		ans-=query(pos[y[i]]),update(pos[y[i]],1);
}

int main()
{
	freopen("BZOJ4430.in","r",stdin);
	freopen("BZOJ4430.out","w",stdout);
	
	scanf("%d",&n);ans=1ll*n*(n-1);
	
	for(int i=1;i<=n;++i)
		scanf("%d",&A[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&B[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&C[i]);
		
	solve(A,B);solve(B,C);solve(C,A);
	printf("%lld\n",ans/2ll);
	
	return 0;
}
