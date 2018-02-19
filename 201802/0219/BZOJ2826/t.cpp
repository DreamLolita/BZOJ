#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define C (c=getchar())
using namespace std;
const int N=3005;
int M,k;
int f[N][N];
int n,t,c;
int a[N],b[N],g[N],d[N];
int he,ta,ans;
pair<int,int> q[N];
inline void read(int &a)
{
	a=0;int f=1;static char c;
	C;
	while (c<'0'||'9'<c) {if (c=='-') f=-1;C;}
	while ('0'<=c&&c<='9') a=a*10+c-48,C;
	a*=f;
}
int main()
{
	register int i,j,l;
	read(M);
	for (l=1;l<=M;l++)
	{
		ans=-0x3f3f3f3f;
		read(n),read(t),read(c);
		for (i=1;i<=n;i++) read(a[i]);
		for (i=1;i<=n;i++) read(b[i]);
		for (i=1;i<=n;i++) read(g[i]);
		for (i=1;i<=n;i++) read(d[i]);
		memset(f,-0x3f3f3f3f,sizeof(f));
		for (i=1;i<=n;i++)
		{
			for (j=0;j<=g[i];j++) f[i][j]=-a[i]*j;
			for (j=0;j<=c;j++) f[i][j]=max(f[i][j],f[i-1][j]);
			k=i-t-1;
			if(k>=0)
			{
				he=0,ta=0;
				for (j=0;j<=c;j++)//Âò
				{
					while (he<ta&&q[he].first<j-g[i]) he++;
					while (he<ta&&q[ta-1].second<=f[k][j]+a[i]*j) ta--;
					q[ta++]=make_pair(j,f[k][j]+a[i]*j);
					if (he<ta) f[i][j]=max(f[i][j],q[he].second-a[i]*j);
				}
				he=0,ta=0;
				for (j=c;j>=0;j--)//Âô
				{
					while (he<ta&&q[he].first>j+d[i]) he++;
					while (he<ta&&q[ta-1].second<=f[k][j]+b[i]*j) ta--;
					q[ta++]=make_pair(j,f[k][j]+b[i]*j);
					if (he<ta) f[i][j]=max(f[i][j],q[he].second-b[i]*j);
				}
			}
			ans=max(ans,f[i][0]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
