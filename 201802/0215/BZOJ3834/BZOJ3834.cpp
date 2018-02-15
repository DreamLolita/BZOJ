#include<bits/stdc++.h>
using namespace std;

int a,b,c,d,ans,i,j,T;

void solve()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	a--;c--;
	if(b<d)
		swap(b,d),swap(a,c);
	for(i=1;i<=d;i=j+1)
	{
		j=min(b/(b/i),d/(d/i));
		if(i<=a)
			j=min(j,a/(a/i));
		if(i<=c)
			j=min(j,c/(c/i));
		if(b/i>a/i && d/i>c/i)
			ans=j;
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ3834.in","r",stdin);
	freopen("BZOJ3834.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
		solve();
	
	return 0;
}
