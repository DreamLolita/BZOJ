#include<iostream>
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<cmath>  
#include<vector>  
#include<algorithm>  
using namespace std;

const int N=1e5+10;
int n;
int wa[N],wb[N],wx[N],wy[N];
int sa[N],rk[N],height[N];
int a[N],Log[N],mi[22][N];
char s[N];

bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b] && r[a+l]==r[b+l];
}

void get_sa(int *r,int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i) wx[i]=0;
	for(i=0;i<n;++i) wx[x[i]=r[i]]++;
	for(i=1;i<m;++i) wx[i]+=wx[i-1];
	for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
	for(j=1,p=1;p<n;j<<=1,m=p)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wy[i]=x[y[i]];
		for(i=0;i<m;++i) wx[i]=0;
		for(i=0;i<n;++i) wx[wy[i]]++;
		for(i=0;i<m;++i) wx[i]+=wx[i-1];
		for(i=n-1;~i;--i) sa[--wx[wy[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
		 	x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

void get_height(int *r)
{
	int i,j,k=0;
	for(i=1;i<=n;++i)
		rk[sa[i]]=i;
	for(i=0;i<n;height[rk[i++]]=k)
		for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];k++);	
}

void init()
{
	Log[1]=0;
	for(int i=2;i<=n;++i)
		Log[i]=Log[i>>1]+1;
}

void rmq()
{
	for(int i=1;i<=n;++i)
		mi[0][i]=height[i];
	int t=Log[n];
	for(int j=1;j<=t;++j)
		for(int i=n;i;--i)
		{
			mi[j][i]=mi[j-1][i];
			if(i+(1<<(j-1))<=n)
				mi[j][i]=min(mi[j][i],mi[j-1][i+(1<<(j-1))]);
		}
}

int lcp(int l,int r)
{
	if(l>r)
		swap(l,r);
	++l;
	int t=Log[r-l+1];
	return min(mi[t][l],mi[t][r-(1<<t)+1]);
}

void solve()
{
	int ans=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<n;j+=i)
		{
			int cp=lcp(rk[j],rk[j+i]);
			ans=max(ans,cp/i+1);
			int las=j-(i-cp%i);
			if(las>=0)
				ans=max(ans,1+lcp(rk[las],rk[las+i])/i);
		}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("HIHO1419.in","r",stdin);
	freopen("HIHO1419.out","w",stdout);
	
	scanf("%s",s);n=strlen(s);
	for(int i=0;i<n;++i)
		a[i]=s[i]-'a'+1;
	a[n]=0;
	get_sa(a,n+1,30);
	get_height(a);
	init();rmq();
	solve();
	
	return 0;
}
