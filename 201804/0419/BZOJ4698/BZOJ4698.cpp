#include<bits/stdc++.h>
using namespace std;

const int INF=1e6+100;
const int N=1e6+10;
int tn,n,m,M;
int hs[N],card[N];
char ch[N];
map<int,int>mp;

struct SA
{
	bool vis[N];
	int top,t[N],wa[N],wb[N];
	int s[N],ws[N],wv[N],rank[N],sa[N],height[N];
	
	void init(int *x)
	{
		for(int i=0;i<n;++i)
			s[i]=x[i];
	}
	
	bool cmp(int *x,int a,int b,int l)
	{
		return x[a]==x[b] && x[a+l]==x[b+l];
	}
	
	void get_sa(int n,int m)
	{
		int i,j,p,*x=wa,*y=wb,*t;
		for(i=0;i<m;++i) ws[i]=0;
		for(i=0;i<n;++i) ws[x[i]=s[i]]++;
		for(i=1;i<m;++i) ws[i]+=ws[i-1];
		for(i=n-1;~i;--i) sa[--ws[x[i]]]=i;
		for(j=1,p=1;p<n;j<<=1,m=p)
		{
			for(p=0,i=n-j;i<n;++i) y[p++]=i;
			for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
			for(i=0;i<n;++i) wv[i]=x[y[i]];
			for(i=0;i<m;++i) ws[i]=0;
			for(i=0;i<n;++i) ws[wv[i]]++;
			for(i=1;i<m;++i) ws[i]+=ws[i-1];
			for(i=n-1;~i;--i) sa[--ws[wv[i]]]=y[i];
			for(t=x,x=y,y=t,i=1,p=1,x[sa[0]]=0;i<n;++i)
				x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
	}
	
	void call_height()
	{
		int i,j,k=0;
		for(i=1;i<=n;++i) 
			rank[sa[i]]=i;
		for(i=0;i<n;height[rank[i++]]=k)
			for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];++k);
	}
	
	bool check(int x)
	{
		for(;top;vis[t[top--]]=0);
		for(int i=1;i<=n;++i)
		{
			if(height[i]>=x)
			{
				if(!top)
				{
					vis[hs[sa[i-1]]]=1;
					t[++top]=hs[sa[i-1]];
				}
				if(!vis[hs[sa[i]]])
				{
					vis[hs[sa[i]]]=1;
					t[++top]=hs[sa[i]];
				}
			}
			else
			{
				if(top==tn)
					return 1;
				for(;top;vis[t[top--]]=0);
			}
		}
		return 0;
	}
}S;


void init()
{
	scanf("%d",&tn);
	for(int i=1;i<=tn;++i)
	{
		scanf("%d",&m);
		for(int j=0;j<m;++j)
			scanf("%d",&card[n+j]),hs[n+j]=i;
		card[n+m]=INF+i;n+=m+1;
	}
	for(int i=n-1;i;--i)
		card[i]=card[i]-card[i-1];
		
	int cnt=0;m=0;
	for(int i=0;i<n;++i)
		if(mp.find(card[i])==mp.end())
			mp[card[i]]=++cnt;
	for(int i=0;i<n;++i)
		card[i]=mp[card[i]],m=max(m,card[i]);
	
	S.init(card);
}

void solve()
{
	S.get_sa(n+1,m+1);S.call_height();
	
	int l=1,r=n,ans=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(S.check(mid))
			ans=mid,l=mid+1;
		else
			r=mid-1;
	}
	printf("%d\n",ans+1);
}

int main()
{
	freopen("BZOJ4698.in","r",stdin);
	freopen("BZOJ4698.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
