#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,tot,len[N],ass[N];
char s[N][N];
string st[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s[i]+1);
		len[i]=strlen(s[i]+1);
		for(int j=1;j<=len[i];++j)
			ass[i]|=(1<<(s[i][j]-'a'));
	}
	sort(ass+1,ass+n+1);
	n=unique(ass+1,ass+n+1)-ass-1;
	printf("%d\n",n);

	return 0;
}

