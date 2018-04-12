#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int cnt;
	Node *l,*r;
	Node()
	{
		l=r=0;
		cnt=0;
	}
}	arr[20000050],*root[200050];
int n,vs,arr1[200050],arr2[200050],rk[200050],sa[200050],height[200050],sum[200050];
char st[200050];
bool Same(int *st,int a,int b,int len)
{
	return st[a]==st[b]&&st[a+len]==st[b+len];
}
void DA(int m=1000)
{
int cnt,i,len,*x=arr1,*y=arr2;
	memset(arr1,127,sizeof(arr1));
	memset(arr2,127,sizeof(arr2));
	for (i=0;i<=m;i++) sum[i]=0;
	for (i=1;i<=n;i++) sum[x[i]=st[i]]++;
	for (i=1;i<=m;i++) sum[i]+=sum[i-1];
	for (i=n;i>=1;i--) sa[sum[x[i]]--]=i;
	for (cnt=0,len=1;cnt<n;len<<=1,m=cnt)
	{
		for (cnt=0,i=n-len+1;i<=n;i++) y[++cnt]=i;
		for (i=1;i<=n;i++)
		if  (sa[i]>len) y[++cnt]=sa[i]-len;
		for (i=0;i<=m;i++) sum[i]=0;
		for (i=1;i<=n;i++) sum[x[y[i]]]++;
		for (i=1;i<=m;i++) sum[i]+=sum[i-1];
		for (i=n;i>=1;i--) sa[sum[x[y[i]]]--]=y[i];
		swap(x,y);
		for (cnt=1,x[sa[1]]=1,i=2;i<=n;i++)
		if  (Same(y,sa[i-1],sa[i],len)) x[sa[i]]=cnt; else x[sa[i]]=++cnt;
	}
	for (i=1;i<=n;i++) rk[sa[i]]=i;
}
void Height()
{
int len,i;
	for (len=0,i=1;i<=n;height[rk[i++]]=len)
	{
		if (len) len--;
		if (rk[i]==1) continue;
		for (;st[i+len]==st[sa[rk[i]-1]+len];len++);
	}
}
void Update(Node *&root,int nowl,int nowr,int askl,int askr,int add)
{
int mid=(nowl+nowr)/2;
	if (nowr<askl||askr<nowl) return;
	if (askl<=nowl&&nowr<=askr)
	{
		root->cnt+=add;
		return;
	}
	if (root->l) arr[++vs]=*root->l; else arr[++vs]=Node();
	root->l=&arr[vs];
	if (root->r) arr[++vs]=*root->r; else arr[++vs]=Node();
	root->r=&arr[vs];
	Update(root->l,nowl,mid,askl,askr,add);
	Update(root->r,mid+1,nowr,askl,askr,add);
	root->cnt=root->l->cnt+root->r->cnt;
}
int Ask(Node *&root,int nowl,int nowr,int askl,int askr)
{
int mid=(nowl+nowr)/2,ans;
	if (nowr<askl||askr<nowl) return 0;
	if (askl<=nowl&&nowr<=askr) return root->cnt;
	ans=0;
	if (root->l) ans+=Ask(root->l,nowl,mid,askl,askr);
	if (root->r) ans+=Ask(root->r,mid+1,nowr,askl,askr);
	return ans;
}
void Solve(int k,int m)
{
int low,mid,high;
	low=0;
	high=n-1;
	while (low+1<high)
	{
		mid=(low+high)/2;
		if  (Ask(root[mid],1,n-1,k,n-1)<m) low=mid; else high=mid;
	}
	if  (Ask(root[high],1,n-1,k,n-1)==m) printf("%d\n",sa[high]-1); else
		printf("Not found\n");
}
int main()
{
int cas,i,k,m,q;
    freopen("sorting.in", "r", stdin);
    freopen("sorting.out", "w", stdout);
	scanf("%d",&cas);
	while (cas--)
	{
		memset(sa,0,sizeof(sa));
		memset(rk,0,sizeof(rk));
		memset(height,0,sizeof(height));
		memset(st,0,sizeof(st));
		memset(arr,0,sizeof(arr));
		vs=0;
		scanf("%s",st+1);
		n=strlen(st+1);
		st[++n]='z'+5;
		DA();
		Height();
		arr[++vs]=Node();
		root[1]=&arr[vs];
		Update(root[1],1,n-1,n-1-sa[1]+1,n-1-sa[1]+1,1);
		for (i=2;i<n;i++)
		{
			arr[++vs]=*root[i-1];
			root[i]=&arr[vs];
			Update(root[i],1,n-1,n-1-sa[i]+1,n-1-sa[i]+1,1);
			if  (height[i]) Update(root[i],1,n-1,height[i],height[i],-1);
		}
		scanf("%d",&q);
		for (i=1;i<=q;i++)
		{
			scanf("%d%d",&k,&m);
			Solve(k,m);
		}
	}
}
