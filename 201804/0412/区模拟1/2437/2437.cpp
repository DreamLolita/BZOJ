#include<bits/stdc++.h>
using namespace std;

int n,ans;

int main()
{
	freopen("2437.in","r",stdin);
	freopen("2437.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=n;i>1;i-=3)
	{
		if(i==2)
			ans+=1,i=0;
		else
		if(i==3)
			ans+=7,i=0;
		else
		if(i==4)
			ans+=4,i=0;
		else
			ans+=7;
	}
	printf("%d\n",ans);
	
	return 0;
}
