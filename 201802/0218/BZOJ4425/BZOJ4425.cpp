#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10;
int n,m,ans;

struct Tnode
{
	int l,r;
};
Tnode a[N];
priority_queue<int>q;

bool cmp(Tnode A,Tnode B)
{
	return A.l<B.l;
}

int main()
{
	freopen("BZOJ4425.in","r",stdin);
	freopen("BZOJ4425.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].l,&a[i].r),a[i].r+=a[i].l;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		while(!q.empty() && m-q.top()<a[i].l)
			q.pop();
		if(!q.empty() && -q.top()<=a[i].l)
			++ans,q.pop();
		q.push(-a[i].r);
	}
	printf("%d\n",ans);
	
	return 0;
} 
