#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef double ldb;
int n,w,u,v,t1,t2,m,len,pos,tmp;
ldb ans;
char opt[5];
vector<pair<ldb,int> >mp;

int main()
{
	freopen("BZOJ4114.in","r",stdin);
	freopen("BZOJ4114.out","w",stdout);
	
	scanf("%d%d%d%d%d%d",&n,&w,&u,&v,&t1,&t2);
	for(int i=1;i<=n;++i)
	{
		scanf("%s%d",opt,&m);
		while(m--)
		{
			scanf("%d%d",&len,&pos);
			if(opt[0]=='E')
				pos=-pos;
			ldb l=(ldb)pos/u;
			l-=(ldb)w*i/v;
			mp.push_back(mkp(l,1));
			ldb r=(ldb)(pos+len)/u;
			r-=(ldb)w*(i-1)/v;
			mp.push_back(mkp(r,-1));
//			printf("%d %d %.8f %.8f\n",len,pos,l,r);
		}
//		printf("\n");
	}
	mp.push_back(mkp(1e15,1));
	mp.push_back(mkp(t1,0));
	sort(mp.begin(),mp.end());
	
	for(int i=0;i<mp.size()-1;++i)
	{
//		printf("%d %.8f\n",mp[i].second,mp[i].first);
		tmp+=mp[i].second;
		if(tmp==0 && mp[i].first>=t1)
			ans=max(ans,min((ldb)t2,mp[i+1].first)-mp[i].first);
	}
	printf("%0.8f\n",ans);
	
	return 0;
}
