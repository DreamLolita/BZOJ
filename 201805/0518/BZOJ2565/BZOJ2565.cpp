#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=1e5+10; 
int n,ans,mx[N];
char s[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct PAM
{
	int sz,las;
	int len[N],fail[N],ch[N][27];
	
	void init()
	{
		len[0]=0;fail[0]=1;
		len[sz=1]=-1;
	}
	
	int getfail(int n,int x)
	{
		while(s[n-len[x]-1]!=s[n])
			x=fail[x];
		return x;
	}
	
	int add(int n,int x)
	{
		int now=getfail(n,las);
		if(!ch[now][x])
		{
			len[++sz]=len[now]+2;
			fail[sz]=ch[getfail(n,fail[now])][x];
			ch[now][x]=sz;
		}
		las=ch[now][x];
		return len[las];
	}
}tr;

int main()
{
	freopen("BZOJ2565.in","r",stdin);
	freopen("BZOJ2565.out","w",stdout);

	scanf("%s",s);n=strlen(s);
	tr.init();reverse(s,s+n);
	for(int i=0;i<n;++i)
		mx[n-i-1]=tr.add(i,s[i]-'a');
	tr.init();reverse(s,s+n);
	for(int i=0;i<n-1;++i)
		ans=max(ans,mx[i+1]+tr.add(i,s[i]-'a'));
	printf("%d\n",ans);

	return 0;
}

