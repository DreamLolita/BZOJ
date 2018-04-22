#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL T,x,y,r,c,ans;

inline LL read()
{
	LL ret=0,opt=1;char ch='.';
	while(ch<'0' || ch>'9')
	{
		ch=getchar();
		if(ch=='-')
			opt=-1;
	}
	while(ch>='0' && ch<='9')
	{
		ret=(ret<<3ll)+(ret<<1ll)+(ch-'0');
		ch=getchar();
	}
	return ret*opt;
}

inline LL solve(LL a,LL b)
{
	if(abs(a-b)%2)
		return 0;
	LL t=min(a,b),p=t%4;
	if(p==1)
		return 1;
	else
	if(p==2)
		return t^1;
	else
	if(p==3)
		return 0;
	else
		return t;
}

int main()
{
	freopen("kongfu.in","r",stdin);
	freopen("kongfu.out","w",stdout);
	
	T=read();
	while(T--)
	{
		x=read();y=read();r=read();c=read();
		ans=(LL)solve(r,c)^solve(r,y-1)^solve(x-1,c)^solve(x-1,y-1);
		printf("%lld\n",ans);
	}
	
	return 0;
}
