#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=998244353;
LL n;

struct Tdata
{
	LL x,y;
	Tdata operator +(const Tdata &A)const{
		return (Tdata){x+A.x,y*A.y%mod};
	}
	Tdata operator *(const Tdata &A)const{
		if(x>A.x)	return *this;
		if(x<A.x)	return A;
		return (Tdata){x,(y+A.y)%mod};
	}
}ans;

struct Tnode
{
	Tdata f,g;
}t;

map<LL,Tnode>mp;

Tnode dfs(LL x)
{
	if(mp.find(x)!=mp.end())
		return mp[x];
	Tnode l=dfs(x-(x>>1)),r=dfs(x>>1);
	return mp[x]=(Tnode){ ((l.f+r.g)+(Tdata){1,1})*((l.g+r.f)+(Tdata){1,1})*((l.g+r.g)+(Tdata){1,2}) , (l.f+r.f)*(l.f+r.g)*(l.g+r.f)*(l.g+r.g)};
}

int main()
{
	freopen("BZOJ5123.in","r",stdin);
	freopen("BZOJ5123.out","w",stdout);
	
	mp[1]=(Tnode){(Tdata){-1,0},(Tdata){0,1}};
	scanf("%lld",&n);
	t=dfs(n);
	ans=t.f*t.g;
	printf("%lld %lld\n",ans.x,ans.y);
	
	return 0;
}
