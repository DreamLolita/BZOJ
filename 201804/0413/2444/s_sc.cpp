#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e+5 + 10;
const int INF = 0x3fffffff;

int n,en,head[maxn],fans;
int siz[maxn],h[maxn];
vector<int> ow[maxn],os[maxn],*w[maxn],*s[maxn];
int wn,sn;

struct edge{
	int v,n;
}e[maxn<<1];

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	return x;
}

void input()
{
	int i,u,v;
	
	n=read();en=1;
	for(i=1;i<=n;i++) h[i]=read();
	for(i=1;i<n;i++)
	{
		u=read();v=read();
		e[en].v=v;e[en].n=head[u];head[u]=en++;
		e[en].v=u;e[en].n=head[v];head[v]=en++;
	}
}

int findl(vector<int> *a,int x)
{
	int l=0,r=a->size(),mid;
	
	while(l+1<r)
	{
		mid=l+r>>1;
		if((*a)[mid]<x) l=mid;
		else r=mid;
	}
	return ((*a)[0]>=x)?0:r;
}

int findr(vector<int> *a,int x)
{
	int l=0,r=a->size(),mid;
	
	while(l+1<r)
	{
		mid=l+r>>1;
		if((*a)[mid]>x) l=mid;
		else r=mid;
	}
	return ((*a)[0]<=x)?0:r;
}

void dfs(int x,int f)
{
	int i,j,k,v,son=0;
	
	siz[x]=1;
	for(i=head[x];i;i=e[i].n) if(e[i].v!=f)
	{
		dfs(e[i].v,x);
		siz[x]+=siz[e[i].v];
		if(siz[e[i].v]>siz[son]) son=e[i].v;
	}
	
	for(i=head[x];i;i=e[i].n) if(e[i].v!=f)
	{
		v=e[i].v;
		j=findl(w[v],h[x]);
		if(j==w[v]->size()) w[v]->push_back(h[x]);
		else (*w[v])[j]=h[x];
		j=findr(s[v],h[x]);
		if(j==s[v]->size()) s[v]->push_back(h[x]);
		else (*s[v])[j]=h[x];
	}
	
	if(!son) 
	{
		w[x]=&ow[wn++],s[x]=&os[sn++];
		w[x]->push_back(h[x]);
		s[x]->push_back(h[x]);
		return;
	}
	w[x]=w[son];s[x]=s[son];
	
	for(i=head[x];i;i=e[i].n) if(e[i].v!=f && e[i].v!=son)
	{
		v=e[i].v;
		for(j=0;j<s[v]->size();j++)
		{
			k=findl(w[x],(*s[v])[j]);
			if(k<w[x]->size()) fans=max(fans,k+j+1);
		}
		for(j=0;j<w[v]->size();j++)
		{
			k=findr(s[x],(*w[v])[j]);
			if(k<s[x]->size()) fans=max(fans,k+j+1);
		}
		
		for(j=0;j<w[v]->size();j++) 
		{
			if(w[x]->size()<=j) w[x]->push_back((*w[v])[j]);
			(*w[x])[j]=min((*w[x])[j],(*w[v])[j]);
		}
		for(j=0;j<s[v]->size();j++) 
		{
			if(s[x]->size()<=j) s[x]->push_back((*s[v])[j]);
			(*s[x])[j]=max((*s[x])[j],(*s[v])[j]);
		}
	}
	
}

int main()
{
	freopen("2444.in","r",stdin);
	freopen("2444.out","w",stdout);
	
	input();
	dfs(1,-1);
	cout<<fans<<endl;

	return 0;
}
