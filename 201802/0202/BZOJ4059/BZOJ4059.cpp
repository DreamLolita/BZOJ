#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,T;
int a[N],pre[N],nex[N];
map<int,int>mp;

bool check(int l,int r)
{
	if(l>=r)
		return true;
	int L=l,R=r;
	for(int i=l;i<=r;++i)
	{
		if(i&1)
		{
			if(pre[L]<l && nex[L]>r)
				return (check(l,L-1) && check(L+1,r));
			++L;
		}
		else
		{
			if(pre[R]<l && nex[R]>r)
				return (check(l,R-1) && check(R+1,r));
			--R;
		}
	}
	return false;
}

int main()
{
//	freopen("BZOJ4059.in","r",stdin);
//	freopen("BZOJ4059.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		mp.clear();
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			nex[mp[a[i]]]=i;pre[i]=mp[a[i]];
			mp[a[i]]=i;
		}
		for(int i=1;i<=n;++i)
			nex[mp[a[i]]]=n+1;
		if(check(1,n))
			puts("non-boring");
		else
			puts("boring");
	}
	
	return 0;
}
