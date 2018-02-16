#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int MAX=1e6+1;
int n,now,ans;
int sum[N],L[N],tr[N],pos[N<<1];
char s[N];

struct Tnode
{
	int R,id;
	bool operator <(const Tnode&A)const{
		return R<A.R;
	}
};
Tnode a[N];

int lowbit(int x)
{
	return x&(-x);
}

void add(int x,int v)
{
	for(;x<=n;x+=lowbit(x))
		tr[x]=max(tr[x],v);
}

int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret=max(ret,tr[x]);
	return ret;
}

int main()
{
	freopen("BZOJ3521.in","r",stdin);
	freopen("BZOJ3521.out","w",stdout);
	
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i)
	{
		sum[i]=(s[i]=='p')?1:-1;
		sum[i]+=sum[i-1];
	}
	for(int i=0;i<=(MAX<<1);++i)
		pos[i]=n;
	for(int i=n-1;i>=0;--i)
	{
		a[i].R=pos[sum[i]+MAX-1];
		a[i].id=i+1;
		pos[sum[i]+MAX]=i;
	}
	for(int i=0;i<=(MAX<<1);++i)
		pos[i]=1;
	pos[MAX]=0;
	for(int i=1;i<=n;++i)
	{
		L[i]=pos[sum[i]+MAX+1];
		pos[sum[i]+MAX]=i;
	}
	sort(a,a+n);
	
	now=1;ans=0;
	for(int i=0;i<n;++i)
	{
		while(now<=a[i].R)
		{
			add(L[now]+1,now);
			++now;
		}
		int res=query(a[i].id+1);
		ans=max(ans,res-a[i].id+1);
	}
	printf("%d\n",ans);
	
	return 0;
}
