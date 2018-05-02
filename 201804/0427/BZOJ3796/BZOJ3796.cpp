#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N=2e5+10;
const ull bas=2000001001LL;
int l1,l2,l3,n,m,ans;
int height[N],sa[N],rank[N],f[N];
int wa[N],wb[N],wx[N],wy[N];
ull fac[N],hs,hs3;
char s1[N],s2[N],s3[N];
int s[N];

void init_hash()
{
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=fac[i-1]*bas;
	hs3=0;
	for(int i=0;i<l3;++i)
		hs3+=(ull)s3[i]*fac[l3-i-1];
	if(l3<=n)
	{
		hs=0;
		for(int i=0;i<l3;++i)
			hs+=(ull)s[i]*fac[l3-i-1];
		if(hs==hs3)
			++f[0];
		for(int i=1;i<n-l3+1;++i)
		{
			hs=(hs-(ull)s[i-1]*fac[l3-1])*bas+(ull)s[i+l3-1];
			if(hs==hs3)
				++f[i];
		}
		for(int i=1;i<=n;++i)
			f[i]+=f[i-1];
	}
}

bool cmp(int *s,int a,int b,int l)
{
	return s[a]==s[b] && s[a+l]==s[b+l];
}

void get_sa(int *s,int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i) wx[i]=0;
	for(i=0;i<n;++i) wx[x[i]=s[i]]++;
	for(i=1;i<m;++i) wx[i]+=wx[i-1];
	for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
	for(j=1,p=1;p<n;j<<=1,m=p)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wy[i]=x[y[i]];
		for(i=0;i<m;++i) wx[i]=0;
		for(i=0;i<n;++i) wx[wy[i]]++;
		for(i=1;i<m;++i) wx[i]+=wx[i-1];
		for(i=n-1;~i;--i) sa[--wx[wy[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

void get_height()
{
/*	int i,j,k=0;
	for(int i=1;i<=n;++i) rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];++k);*/
	
	for (int i=0;i<n;++i) rank[sa[i]]=i;
    int k=0;
    for (int i=0;i<n;++i)
    {
        if (!rank[i]) continue;
        int j=sa[rank[i]-1];
        if (k) --k;
        while (i+k<n&&j+k<n&&s[i+k]==s[j+k]) ++k;
        height[rank[i]]=k;
    }
}

int query(int id)
{
	if(sa[id]<=l1)
		return 1;
	return 2;
}

bool check(int id,int jd,int len)
{
	if(len<l3) 	return 1;
	len-=l3;
	return (!(f[id+len]-(id?f[id-1]:0)) && !(f[jd+len]-(jd?f[jd-1]:0)));
}

int main()
{
	freopen("BZOJ3796.in","r",stdin);
	freopen("BZOJ3796.out","w",stdout);
	
	scanf("%s%s%s",s1,s2,s3);
	l1=strlen(s1);l2=strlen(s2);l3=strlen(s3);
	for(int i=0;i<l1;++i)
		s[n++]=s1[i];
	s[n++]='$';l1=n-2;
	for(int i=0;i<l2;++i)
		s[n++]=s2[i];
	l2=n-1;
	init_hash();get_sa(s,n,256);get_height();
	
//	for(int i=0;i<n;++i)
//		printf("%d %d\n",sa[i],height[i]);
	
	for(int i=0;i<n;++i)
	{
		int t=query(i);t=(t==1?l1:l2);
		height[i]=min(height[i],t-sa[i]+1);
	}
//	for(int i=0;i<n;++i)
//		printf("%d %d\n",sa[i],height[i]);
//	for(int i=0;i<n;++i)
//		printf("%d ",f[i]);
//	puts("");
	
	for(int i=1;i<n;++i)
	{
		if(s[sa[i]]=='$' || query(i)==query(i-1))
			continue;
		int l=0,r=height[i];
		while(l<=r)
		{
//			printf("%d %d\n",l,r);
			int mid=(l+r)>>1;
			if(check(sa[i-1],sa[i],mid))
				ans=max(ans,mid),l=mid+1;
			else
				r=mid-1;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
