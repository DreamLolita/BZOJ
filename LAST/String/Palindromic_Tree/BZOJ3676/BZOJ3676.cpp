#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAXN=300007;
int n;
char s[MAXN];

struct Palindromic
{
	int len[MAXN],nex[MAXN][26],fail[MAXN],cnt[MAXN];
	int siz,suff;
	
	void add(int p)
	{
		int cur=suff,curlen=0;
		int ch=s[p]-'a';
		
		while(true)
		{
			curlen=len[cur];
			if(p-curlen-1>=0 && s[p-curlen-1]==s[p])
				break;
			cur=fail[cur];
		}
		
		if(nex[cur][ch])
		{
			suff=nex[cur][ch];
			cnt[suff]++;
			return;
		}
		
		suff=++siz;
		len[siz]=len[cur]+2;
		nex[cur][ch]=siz;
		cnt[siz]=1;
		
		if(len[siz]==1)
		{
			fail[siz]=2;
			return;
		}
		
		cur=fail[cur];
		while(true)
		{
			curlen=len[cur];
			if(p-curlen-1>=0 && s[p-curlen-1]==s[p])
				break;
			cur=fail[cur];
		}
		fail[siz]=nex[cur][ch];
	}
	
	void init()
	{
		siz=2;suff=2;
		len[1]=-1;fail[1]=1;
		len[2]=0;fail[2]=1;
	}
	
	LL getans()
	{
		for(int i=siz;i>=2;--i)
			cnt[fail[i]]+=cnt[i];
		LL ret=0;
		for(int i=3;i<=siz;++i)
		{
			LL tmp=(LL)len[i]*(LL)cnt[i];
			ret=max(ret,tmp);
		}
		return ret;
	}
};
Palindromic tree;

int main()
{
///	freopen("2115.in","r",stdin);
//	freopen("2115.out","w",stdout);
	
	tree.init();
	scanf("%s",s);
	n=strlen(s);
	
	for(int i=0;i<n;++i)
		tree.add(i);
	
	printf("%lld\n",tree.getans());
		
	return 0;
}
