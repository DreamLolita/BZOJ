#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,q;
char mp[N][N],np[N][N];

int main()
{
	freopen("rotate.in","r",stdin);
	freopen("rotate.out","w",stdout);
	
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%s",mp[i]+1);
	while(q--)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		for(int i=x;i<x+l;++i)
			memcpy(np[i-x+1],mp[i]+y,l);
		for(int i=1;i<=l;++i)
			for(int j=1;j<=l;++j)
				mp[i+x-1][j+y-1]=np[j][l-i];
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			putchar(mp[i][j]);
		puts("");
	}
	return 0;
}
