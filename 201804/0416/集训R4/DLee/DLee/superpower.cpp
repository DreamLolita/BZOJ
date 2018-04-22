#include<bits/stdc++.h>
#define id(x) (x+1)>now?1:(x+1)
using namespace std;

typedef long double ldb;
const ldb eps=1e-8;
const ldb pi=acos(-1);
const int INF=1e6;
const int N=10;
int n,a[N];
double tmp;
ldb ans,len[N];
bool vis[N];

inline bool check(ldb S,int now)
{
	if(clock()>1980)
	{
		tmp=ans;
		printf("%0.8lf\n",(double)tmp);
		exit(0);
	}
	ldb ret=0.0;
	for(int i=1;i<=now;++i)
	{
		ldb phi=S/len[a[i]]/len[a[id(i)]];
//printf("ang:%lf %lf %lf %lf\n",ang,len[a[i]],len[a[id(i)]],phi);
		if(phi>1)
			return true;
		if(phi<-1)
			return  false;
		ret+=acos(phi);
	}
	return ret<=(2.0*pi);
}

inline void dfs(int now)
{
	if(clock()>1980)
	{
		tmp=ans;
		printf("%0.8lf\n",(double)tmp);
		exit(0);
	}
	if(now>=3)
	{
		ldb lim=0.0;
		for(int i=1;i<=now;++i)
			lim=max(lim,len[a[i]]*len[a[id(i)]]);
		ldb S=0.0,l=(ldb)-lim,r=(ldb)lim;
		while(l+eps<r)
		{
			ldb mid=(l+r)/2.0;
			if(check(mid,now))
				S=mid,r=mid;
			else
				l=mid;
//printf("%lf\n",mid);
		}
		S-=eps;
		ldb ret=0.0;
		for(int i=1;i<=now;++i)
		{
			ldb phi=acos(S/len[a[i]]/len[a[id(i)]]);
//printf("l1:%lf l2:%lf\n",(double)len[a[i]],(double)len[a[id(i)]]);
//printf("S:%lf acos:%lf\n",(double)S,(double)acos(S/len[a[i]]/len[a[id(i)]]));
			ret+=len[a[i]]*len[a[id(i)]]*sin(phi)/2.0;
			tmp=phi;//printf("%lf\n",tmp);
		}
//printf("now:%d ",now);tmp=ans;printf("%lf ",tmp);tmp=ret;printf("%lf\n",tmp);
		ans=max(ans,ret);
		if(now==n)
			return;
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			a[now+1]=i;vis[i]=true;
			dfs(now+1);
			vis[i]=false;
		}
}

bool cmp(ldb A,ldb B)
{
	return A>B;
}

int main()
{
	freopen("superpower.in","r",stdin);
	freopen("superpower.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lf",&tmp),len[i]=tmp;
	sort(len+1,len+n+1,cmp);vis[1]=true;a[1]=1;
	dfs(1);tmp=ans;
	printf("%0.8lf\n",(double)tmp);
	
	return 0;
}
