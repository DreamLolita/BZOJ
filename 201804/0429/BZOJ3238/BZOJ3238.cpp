#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;
int n,top;
int rk[N],sa[N],height[N],lp[N],rp[N],stk[N];
int a[N],wx[N],wy[N],wa[N],wb[N];
char s[N];
LL ans;

bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b] && r[a+l]==r[b+l];
}

void get_sa(int *a,int n,int m)
{
	int *x=wa,*y=wb,*t,i,j,p;
	for(i=0;i<m;++i) wx[i]=0;
	for(i=0;i<n;++i) wx[x[i]=a[i]]++;
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

void get_height(int *a)
{
	int i,j,k=0;
	for(i=1;i<=n;++i)
		rk[sa[i]]=i;
	for(i=0;i<n;height[rk[i++]]=k)
		for(k?k--:0,j=sa[rk[i]-1];a[i+k]==a[j+k];k++);
}

int main()
{
	freopen("BZOJ3238.in","r",stdin);
	freopen("BZOJ3238.out","w",stdout);
	
	scanf("%s",s);n=strlen(s);
	for(int i=0;i<n;++i)
		a[i]=s[i]-'a'+1;
	get_sa(a,n+1,30);
//	for(int i=0;i<n;++i)
//		printf("%d\n",sa[i]);
	get_height(a);
	stk[0]=1;
	for(int i=2;i<=n;++i)
	{
		while(top && height[stk[top]]>=height[i]) --top;
		lp[i]=i-stk[top];stk[++top]=i;
	}
	top=0;stk[0]=n+1;
	for(int i=n;i>=2;--i)
	{
		while(top && height[stk[top]]>height[i]) --top;
		rp[i]=stk[top]-i;stk[++top]=i;
	}
	for(int i=2;i<=n;++i)
		ans+=2ll*lp[i]*rp[i]*height[i];
	printf("%lld\n",1ll*n*(n+1)*(n-1)/2ll-ans);
	
	return 0;
}
