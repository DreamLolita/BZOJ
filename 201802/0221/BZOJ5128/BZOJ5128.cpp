#include<bits/stdc++.h>
using namespace std;

const int N=205;
int n,cnt;
bool f[N][N];
char s[N],a[N],b[N],c[N];
string ans;

bool check(int len,string cur)
{
	for(int i=1;i<=len;++i)
		b[i]=cur[i-1];
	int tot=0;
	for(int i=1;i*len<=n;++i)
		for(int j=1;j<=len;++j)
			c[++tot]=b[j];
	sort(c+1,c+n+1);
	for(int i=1;i<=n;++i)
		if(c[i]!=a[i])
			return 0;
	for(int i=0;i<=n+1;++i)
		for(int j=0;j<=n+1;++j)
			f[i][j]=0;
	for(int i=n;i;--i)
	{
		f[i][i-1]=1;
		for(int j=i;j<=n;++j)
		{
			for(int k=j-len;k>=i-1;k-=len)
			{
				if(f[i][k] && f[k+1][j])
				{
					f[i][j]=1;
					break;
				}
			}
			int l=j-i+1;
			l%=len;
			if(!l)
				l+=len;
			if(f[i][j-1] && s[j]==b[l])
				f[i][j]=1;
		}
	}
	return f[1][n];
}

void solve(int len)
{
	if(n%len)
		return;
	for(int i=1;i+len-1<=n;++i)
	{
		string now="";
		for(int j=0;j<len;++j)
			now.push_back(s[i+j]);
		if(cnt && ans<=now)
			continue;
		if(check(len,now))
		{
			++cnt;
			ans=now;
		}
	}
	if(cnt)
	{
		cout<<ans<<endl;
		exit(0);
	}
}

int main()
{
//	freopen("BZOJ5128.in","r",stdin);
//	freopen("BZOJ5128.out","w",stdout);
	
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i)
		a[i]=s[i];
	sort(a+1,a+n+1);
	for(int i=1;i<n;++i)
		solve(i);
	puts(s+1);
	
	return 0;
}
