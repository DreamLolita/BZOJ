#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
int n;
LL sum;

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)
		sum+=read();
	puts((sum%2ll)?"Alice":"Bob");	 

	return 0;
}

