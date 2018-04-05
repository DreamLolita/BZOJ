#include<bits/stdc++.h>
#define ls ch[rt][0]
#define rs ch[rt][1]
using namespace std;

const int N=5e5+10;
const int INF=1e9;
int n,ban,ans,root;

struct Tpoint
{
	int x,y;
};

bool cmpx(Tpoint A,Tpoint B)
{
	if(A.x==B.x)
		return A.y<B.y;
	return A.x<B.x;
}

bool cmpy(Tpoint A,Tpoint B)
{
	if(A.y==B.y)
		return A.x<B.x;
	return A.y<B.y;
}

int dis(Tpoint A,Tpoint B)
{
	return abs(A.x-B.x)+abs(A.y-B.y);
}

struct KD_Tree
{
	Tpoint a[N],low[N],upp[N];
	int root,tf,tc,ch[N][2];
	
	void pushup(int rt)
	{
		if(ls)
		{
			low[rt].x=min(low[rt].x,low[ls].x);low[rt].y=min(low[rt].y,low[ls].y);
			upp[rt].x=max(upp[rt].x,upp[ls].x);upp[rt].y=max(upp[rt].y,upp[ls].y);
		}
		if(rs)
		{
			low[rt].x=min(low[rt].x,low[rs].x);low[rt].y=min(low[rt].y,low[rs].y);
			upp[rt].x=max(upp[rt].x,upp[rs].x);upp[rt].y=max(upp[rt].y,upp[rs].y);
		}
	}
	
	int build(int l,int r,int dep)
	{
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		if(dep&1)
			nth_element(a+l,a+mid,a+r+1,cmpy);
		else
			nth_element(a+l,a+mid,a+r+1,cmpx);
		ch[mid][0]=build(l,mid-1,dep+1);
		ch[mid][1]=build(mid+1,r,dep+1);
		low[mid]=upp[mid]=a[mid];
		pushup(mid);
		return mid;
	}
	
	int calf(int rt)
	{
		return max(abs(low[rt].x-a[ban].x),abs(a[ban].x-upp[rt].x))+
			max(abs(low[rt].y-a[ban].y),abs(a[ban].y-upp[rt].y));
	}
	
	int calc(int rt)
	{
		return max(low[rt].x-a[ban].x,0)+max(a[ban].x-upp[rt].x,0)+
			max(low[rt].y-a[ban].y,0)+max(a[ban].y-upp[rt].y,0);
	}
	
	void queryf(int rt)
	{
		if(!rt)
			return;
		tf=max(tf,dis(a[ban],a[rt]));
		int l=calf(ls),r=calf(rs);
		if(l>r)
		{
			if(l>tf)	
				queryf(ls);
			if(r>tf)	
				queryf(rs);
		}
		else
		{
			if(r>tf)
				queryf(rs);
			if(l>tf)
				queryf(ls);
		}
	}
	
	void queryc(int rt)
	{
		if(!rt)
			return;
		if(rt!=ban)
			tc=min(tc,dis(a[ban],a[rt]));
		int l=calc(ls),r=calc(rs);
		if(l<r)
		{
			if(l<tc)	
				queryc(ls);
			if(r<tc)	
				queryc(rs);
		}
		else
		{
			if(r<tc)
				queryc(rs);
			if(l<tc)
				queryc(ls);
		}
	}
}tr;



int main()
{
	freopen("BZOJ1941.in","r",stdin);
	freopen("BZOJ1941.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&tr.a[i].x,&tr.a[i].y);
	tr.root=tr.build(1,n,0);ans=INF;
	for(int i=1;i<=n;++i)
	{
		ban=i;tr.tf=0;tr.tc=INF;
		tr.queryf(tr.root);tr.queryc(tr.root);
		ans=min(ans,tr.tf-tr.tc);
	}
	printf("%d\n",ans);
	
	return 0;
}
