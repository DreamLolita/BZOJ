#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef pair<int,int> pii;
const int N=2e5+10;
int n,w[N];
char ch[N];

struct SA
{
	int s[N],sa[N],rank[N],height[N];
	int wv[N],ws[N],wa[N],wb[N];
	
	void init(int len,char *a)
	{
		for(int i=0;i<len;++i)
			s[i]=a[i]-'a';
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
}S;

struct Trie
{
	pii t[N];
	int ind,siz[N],rt[N],lef[N],c[N*18][2];
	
	void init()
	{
		for(int i=1;i<=n;++i)
			siz[i]=1,lef[i]=i,rt[i]=build(w[S.sa[i]+1]);
		for(int i=2;i<=n;++i)
			t[i-1]=mkp(n-S.height[i],i);
		sort(t+1,t+n);
	}
	
	int build(int x)
	{
		int root=++ind,now=root;
		for(int i=18;~i;--i)
			c[now][(x>>i)&1]=++ind,now=ind;
		return root;
	}
	
	int query(int x,int y,int z=0)
	{
		int ret=z;
		if(c[x][0])
		{
			if(c[y][1]) ret=query(c[x][0],c[y][1],z<<1|1);
				else ret=query(c[x][0],c[y][0],z<<1);
		}
		if(c[x][1])
		{
			if(c[y][0]) ret=max(ret,query(c[x][1],c[y][0],z<<1|1));
				else ret=max(ret,query(c[x][1],c[y][1],z<<1));
		}
		return ret;
	}
	
	void merge(int x,int y)
	{
		if(c[x][0])
		{
			if(c[y][0]) merge(c[x][0],c[y][0]);
				else c[y][0]=c[x][0];
		}
		if(c[x][1])
		{
			if(c[y][1])	merge(c[x][1],c[y][1]);
				else c[y][1]=c[x][1];
		}
	}
	
	int findf(int x)
	{
		return lef[x]==x?x:lef[x]=findf(lef[x]);
	}
	
	void solve()
	{
		int ans=0;
		for(int i=1;i<n;++i)
		{
			int x=t[i].second,y=x-1,z=n-t[i].first;
			x=findf(x);y=findf(y);
			if(siz[x]<siz[y])
				swap(x,y);
			int tmp=query(rt[y],rt[x])+z;
			ans=max(ans,tmp);
			merge(rt[y],rt[x]);siz[x]+=siz[y];lef[y]=x;
		}
		printf("%d\n",ans);
	}
}tr;

int main()
{
	freopen("LOJ6198.in","r",stdin);
	freopen("LOJ6198.out","w",stdout);
	
	scanf("%d%s",&n,ch);
	S.init(n,ch);
	for(int i=1;i<=n;++i)
		scanf("%d",&w[i]);
	S.get_sa(n+1,27);S.call_height();
	tr.init();tr.solve();
	
	return 0;
}
