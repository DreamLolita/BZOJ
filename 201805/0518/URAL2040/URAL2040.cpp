#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=5e6+10;
int n;
char s[N],ans[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct PAM
{
	int ch[N][2],fail[N],len[N];
	int las,sz;
	
	void build()
	{
		sz=1;
		len[0]=0;fail[0]=1;
		len[1]=-1;
	}
	
	int getfail(int n,int x)
	{
		while(s[n-len[x]-1]!=s[n])
			x=fail[x];
		return x; 
	}
	
	int add(int n,int x)
	{
		int now=getfail(n,las),ret=0;
		if(!ch[now][x])
		{
			len[++sz]=len[now]+2;
			fail[sz]=ch[getfail(n,fail[now])][x];
			ch[now][x]=sz;
			ret=1;
		}
		las=ch[now][x];
		return ret;
	}
}tr;

int main()
{
	freopen("URAL2040.in","r",stdin);
	freopen("URAL2040.out","w",stdout);

	scanf("%s",s);n=strlen(s);
	tr.build();
	for(int i=0;i<n;++i)
		ans[i]=tr.add(i,s[i]-'a')^48;
	ans[n]='\0';
	puts(ans);

	return 0;
}

