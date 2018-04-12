#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int ans1,ans2,n,x,y,q,ans;
int num[N],mx[N*N],mi[N*N];
bool flag[N][N];

void build(int rt,int l,int r)
{
	if(l==r)
	{
		mx[rt]=mi[rt]=num[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
	mi[rt]=min(mi[rt<<1],mi[rt<<1|1]);
}

int querymi(int rt,int l,int r,int L,int R)
{
	if(L<=l && r<=R)
		return mi[rt];
	int mid=(l+r)>>1;
	int ret=1e9;
	if(L<=mid)
		ret=min(ret,querymi(rt<<1,l,mid,L,R));
	if(R>mid)
		ret=min(ret,querymi(rt<<1|1,mid+1,r,L,R));
	return ret;
}

int querymx(int rt,int l,int r,int L,int R)
{
	if(L<=l && r<=R)
		return mx[rt];
	int mid=(l+r)>>1;
	int ret=-1e9;
	if(L<=mid)
		ret=max(ret,querymx(rt<<1,l,mid,L,R));
	if(R>mid)
		ret=max(ret,querymx(rt<<1|1,mid+1,r,L,R));
	return ret;
}

int main()
{
	freopen("2438.in","r",stdin);
	freopen("2438.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&num[i]);
	build(1,1,n);
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
		{
			int x=querymi(1,1,n,i,j),y=querymx(1,1,n,i,j);
//			printf("%d %d %d %d\n",i,j,x,y);
			if(y-x==j-i)
				flag[i][j]=1;
		}
	scanf("%d",&q);
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);ans=1e9;
		for(int i=1;i<=l;++i)
			for(int j=r;j<=n;++j)
				if(flag[i][j])
				{
					if(ans>j-i+1)
						ans=min(ans,j-i+1),ans1=i,ans2=j;
					break;
				}
		printf("%d %d\n",ans1,ans2);			
	}
	
	return 0;
}
