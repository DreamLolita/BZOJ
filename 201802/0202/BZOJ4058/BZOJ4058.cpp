#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,T;
int q[N],s[N];
char a[N];

bool solve(int l,int r)
{
//	printf("%d %d\n",l,r);
	bool flag=0;
    for(int i=l;i<=r;++i)  
		if (s[i]) 
		{
	        flag=1;
	        break;
    	}
    if (!flag) 
		return false;
	if((r-l)&1)
		return true;
	
	int t=0;
	for(int i=l+1;i<=r;i+=2)
		q[++t]=s[i];
	int mid=(l+t-1);
	for(int i=l+1;i<=r;i+=2)
		q[++t]=s[i+1]^s[i-1];
	for(int i=1;i<=t;++i)
		s[i+l-1]=q[i];
	r=l+t-1;
	return solve(l,mid) || solve(mid+1,r);
}

int main()
{
//	freopen("BZOJ4058.in","r",stdin);
//	freopen("BZOJ4058.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",a+1);n=strlen(a+1);
		for(int i=1;i<=n;++i)
			s[i]=a[i]-'0';
		s[0]=s[n+1]=0;
		if(solve(1,n))
			puts("LIVES");
		else
			puts("DIES");
	}
	
	return 0;
}
