#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,m,ans;
bitset<N>a[N<<1];
char ch[N];

void gauss()
{
	int now=0;
	for(int i=1;i<=n;++i)
	{
		int j=now+1;
		while(!a[j][i] && j<=m)
			++j;
		if(j==m+1)
		{
			ans=-1;
			return;
		}
		else
			ans=max(ans,j);
		++now;swap(a[j],a[now]);
		for(int k=1;k<=m;++k)
			if(k!=now && a[k][i])
				a[k]^=a[now];
	}
}

int main()
{
	freopen("BZOJ1923.in","r",stdin);
	freopen("BZOJ1923.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=n;++j)
			a[i][j]=ch[j]-'0';
		scanf("%s",ch+1);
		a[i][n+1]=ch[1]-'0';
	}
	gauss();
	if(ans==-1)
		puts("Cannot Determine");
	else
	{
		printf("%d\n",ans);
		for(int i=1;i<=n;++i)
			if(a[i][n+1])
				puts("?y7M#");
			else
				puts("Earth");
	}
	
	return 0;
}
