#include<bits/stdc++.h>
#define mkp make_pair
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pii;
const LL N=2e+5+10;
LL n,a,ans;
map<pii,int> mp;

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tline
{
	LL x,y,tim; 
};
Tline p[N];

bool cmp(Tline a,Tline b)
{
	return a.tim<b.tim;
}

int main()
{
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	
	int i,j;pii tmp;
	n=read();a=read();read();
	for(int i=1;i<=n;i++)
	{
		LL t=read();p[i].x=read();p[i].y=read();
		p[i].tim=p[i].x*a-p[i].y;
	}
	sort(p+1,p+n+1,cmp);
	
	ans=0;
	for(i=1;i<=n;i=j)
	{
		mp.clear();
		for(j=i;p[i].tim==p[j].tim && j<=n;j++)
		{
			tmp=mkp(p[j].x,p[j].y);
			ans-=mp[tmp];mp[tmp]++;
		}
		ans+=(LL)(j-i)*(j-i-1)/2;
	}
	printf("%lld\n",ans*2);
	
	return 0;
}

