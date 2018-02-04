#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int T,n,m,tot,ans;
int q[N],tr[N];
set<int>mp[N];

struct Tpoint
{
	int x,y,c;
};
Tpoint p[N];

bool cmp(Tpoint A,Tpoint B)
{
	return A.y<B.y;
}

int lowbit(int x)
{
	return x&(-x);
}

void add(int x,int v)
{
	for(;x<=tot;x+=lowbit(x))
		tr[x]+=v;
}

int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x];
	return ret;
}

int main()
{
//	freopen("BZOJ4062.in","r",stdin);
//	freopen("BZOJ4062.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		tot=ans=0;
		memset(tr,0,sizeof(tr));
		
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;++i)
		{
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].c);
			--p[i].c;
			q[tot++]=p[i].x;
		}
		sort(q,q+tot);
		tot=unique(q,q+tot)-q;
		for(int i=0;i<n;++i)
			p[i].x=lower_bound(q,q+tot,p[i].x)-q+1;
		sort(p,p+n,cmp);
		
		for(int i=0;i<m;++i)
		{
			mp[i].clear();
			mp[i].insert(0);
			mp[i].insert(tot+1);
		}
		for(int i=0;i<n;)
		{
			int j;
			for(j=i;j<n && p[i].y==p[j].y;++j)
			{
				set<int>::iterator it=mp[p[j].c].lower_bound(p[j].x);
				int R=*it-1,L=*(--it);
				ans=max(ans,query(R)-query(L));
			}
			for(;i<j;++i)
			{
				add(p[i].x,1);
				mp[p[i].c].insert(p[i].x);
			}
		}
		
		for(int i=0;i<m;++i)
		{
			int las=0,now;
			for(set<int>::iterator it=++mp[i].begin();it!=mp[i].end();++it)
			{
				now=*it;
				ans=max(ans,query(now-1)-query(las));
				las=now;
			}
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
