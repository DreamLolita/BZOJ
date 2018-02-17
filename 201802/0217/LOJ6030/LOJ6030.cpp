#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1005;
int n,ans,tmp;
bool flag,hav[N];
char mp[N][N];

int main()
{
	freopen("LOJ6030.in","r",stdin);
	freopen("LOJ6030.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",mp[i]+1);
		
	flag=false;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(mp[i][j]=='#')
			{
				flag=true;
				break;
			}
	if(!flag)
	{
		puts("-1");
		return 0;
	}

	for(int i=1;i<=n;++i)
	{
		flag=false;
		for(int j=1;j<=n;++j)
			if(mp[i][j]=='.')
			{
				flag=true;
				break;
			}
		ans+=(flag?1:0);
		for(int j=1;j<=n;++j)
			if(mp[j][i]=='#')
			{
				hav[i]=1;
				break;
			}
	}
	
	tmp=INF;
	for(int i=1;i<=n;++i)
	{
		int res=0;
		for(int j=1;j<=n;++j)
			res+=(mp[i][j]=='.');
		if(!res || hav[i])
			tmp=min(tmp,res);
		else
			tmp=min(tmp,res+1);
	}
	ans+=tmp;
	printf("%d\n",ans);
	
	return 0;
}
