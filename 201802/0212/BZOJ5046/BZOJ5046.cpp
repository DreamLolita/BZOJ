#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1ll<<62;
const int N=200;
int n,A,B,ap;
int r[N],s[N];
LL f[N][N];

int main()
{
	freopen("BZOJ5046.in","r",stdin);
	freopen("BZOJ5046.out","w",stdout);
	
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&r[i],&s[i]);
	for(int i=n;i;--i)
		s[i]+=s[i+1];
	f[n+1][0]=-INF;
	for(int i=n;i;--i)
		for(int j=0;j<=s[i];++j)
		{
			f[i][j]=-INF;
			if(s[i]-j+1<=s[i+1])
				f[i][j]=-f[i+1][s[i]-j+1]-r[i]+1;
			if(j<=s[i+1])
				f[i][j]=min(f[i][j],max(1ll,f[i+1][j]+r[i]+1));
		}
	for(ap=s[1];f[1][ap]>A-B;--ap);
	
	printf("%d %d\n",ap,s[1]-ap);
	return 0;
}
