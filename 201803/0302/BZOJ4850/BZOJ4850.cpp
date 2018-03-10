#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=17;
int n,qs,lim,ans;
int h[N],id[N],Log[N];
int mx[N][M];

struct Tque
{
	int l,r;
};
Tque s[N];

int sqr(int x)
{
	return x*x;
}

void init()
{
	scanf("%d",&n);double qs=sqrt(n);
	lim=(int)qs;lim+=qs>lim?1:0;
	
	for(int i=1;i<=n;++i)
		scanf("%d",&h[i]);
	
	for(int i=1;i<=lim;++i)
	{
		s[i].l=sqr(i-1)+1;s[i].r=sqr(i);
		for(int j=s[i].l;j<=s[i].r;++j)
			id[j]=i;
	}
}

void get_rmq()
{
	Log[1]=0;
	for(int i=2;i<=n;++i)
		Log[i]=Log[i>>1]+1;
	for(int i=n;i;--i)
	{
		mx[i][0]=h[i];
		for(int j=1;(i-1+(1<<j))<=n;++j)
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
	}
}

int query(int l,int r)
{
	l=max(l,1);r=min(r,n);
	int k=Log[r-l+1];
	return max(mx[l][k],mx[r-(1<<k)+1][k]);
}

void solve()
{
	for(int i=1;i<=n;++i)
	{
		ans=0;
		for(int j=id[i-1];j>=1;--j)
			ans=max(ans,query(i-s[j].r,i-s[j].l)+j);
		for(int j=id[n-i];j>=1;--j)
			ans=max(ans,query(i+s[j].l,i+s[j].r)+j);
		printf("%d\n",max(0,ans-h[i]));
	}
}

int main()
{
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	
	init();
	get_rmq();
	solve();
	
	return 0;
}
