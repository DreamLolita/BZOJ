#include<bits/stdc++.h>
using namespace std;

const int N=4005;
int n,t;
int len[N],b[N],q[N];
int cnt[2],f[2][N];
char a[N][N];

bool cmp(int x,int y)
{
	return len[x]<len[y];
}

bool check(int x,int y)
{
	if(len[x]>len[y])
		return 0;
	for(int i=0,j=0;i<len[x];++i,++j)
	{
		while(j<len[y] && a[x][i]!=a[y][j])
			++j;
		if(j==len[y])
			return 0;
	}
	return 1;
}

int main()
{
	freopen("BZOJ4110.in","r",stdin);
	freopen("BZOJ4110.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=0;i<=n;++i)
	{
		scanf("%s",a[i]);
		len[i]=strlen(a[i]);b[i]=i;
		if(!check(i,0))
		{
			puts("impossible");
			return 0;
		}
	}
	len[0]=0;
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		int x=check(f[0][cnt[0]],b[i]);
		int y=check(f[1][cnt[1]],b[i]);
//		printf("%d %d %d %d %d %d\n",i,x,y,f[0][cnt[0]],f[1][cnt[1]],b[i]);
//		puts(a[f[0][cnt[0]]]);puts(a[b[i]]);
		if(!x && !y)
		{
			puts("impossible");
			return 0;
		}
		else
		if(x && !y)
		{
			f[0][++cnt[0]]=b[i];
			for(int j=1;j<=t;++j)
				f[1][++cnt[1]]=q[j];
			t=0;
		}
		else
		if(!x && y)
		{
			f[1][++cnt[1]]=b[i];
			for(int j=1;j<=t;++j)
				f[0][++cnt[0]]=q[j];
			t=0;
		}
		else
		{
			if(check(q[t],b[i]))
				q[++t]=b[i];
			else
			{
				f[0][++cnt[0]]=b[i];
				for(int j=1;j<=t;++j)
					f[1][++cnt[1]]=q[j];
				t=0;
			}
		}
	}
	for(int j=1;j<=t;++j)
		f[1][++cnt[1]]=q[j];
	printf("%d %d\n",cnt[0],cnt[1]);
	for(int i=1;i<=cnt[0];++i)
		puts(a[f[0][i]]);
	for(int i=1;i<=cnt[1];++i)
		puts(a[f[1][i]]);
	
	return 0;
}
