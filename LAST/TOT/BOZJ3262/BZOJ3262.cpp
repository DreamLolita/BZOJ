#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,tot,k,num[N];

struct Tnode
{
	int x,y,z,cnt,ans;
};
Tnode p[N];

bool cmpx(Tnode A,Tnode B)
{
	if(A.x!=B.x)	return A.x<B.x;
	if(A.y!=B.y)	return A.y<B.y;
	return A.z<B.z;
}

bool cmpy(Tnode A,Tnode B)
{
	if(A.y!=B.y)	return A.y<B.y;
	return A.z<B.z;
}

struct BIT
{
	int s[N];
	
	void init(){
		memset(s,0,sizeof(s));
	}
	
	int lowbit(int x){
		return x&(-x);
	}
		
	void update(int x,int v)
	{
		for(;x<=k;x+=lowbit(x))
			s[x]+=v;
	}
	
	int query(int x)
	{
		int ret=0;
		for(;x;x-=lowbit(x))
			ret+=s[x];
		return ret;
	}
	
	void clear(int x)
	{
		for(;x<=k;x+=lowbit(x));
			s[x]=0;
	}
};
BIT t;

void CDQ(int l,int r)
{
	if(l==r)
	{
		p[l].ans+=p[l].cnt-1;
		return;
	}
	int mid=(l+r)>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	
	sort(p+l,p+mid+1,cmpy);
	sort(p+mid+1,p+r+1,cmpy);
	
	int j=l;
	for(int i=mid+1;i<=r;++i)
	{
		for(;j<=mid && p[j].y<=p[i].y;++j)
			t.update(p[j].z,p[j].cnt);
		p[i].ans+=t.query(p[i].z);
	}
	
	for(int i=l;i<j;++i)
		t.update(p[i].z,-p[i].cnt);
	sort(p+l,p+r+1,cmpy);
}

bool Same(int a,int b){
	return (p[a].x==p[b].x && p[a].y==p[b].y && p[a].z==p[b].z);
}

int main()
{
//	freopen("BZOJ3262.in","r",stdin);
//	freopen("BZOJ3262.out","w",stdout);
	
	t.init();
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
	sort(p+1,p+n+1,cmpx);
	
	for(int i=1;i<=n;++i)
	{
		if(Same(i,i-1))
			p[tot].cnt++;
		else
			p[++tot]=p[i],p[tot].cnt=1;
	}
	CDQ(1,tot);
	sort(p+1,p+tot+1,cmpx);
	for(int i=1;i<=tot;++i)
		num[p[i].ans]+=p[i].cnt;
	for(int i=0;i<n;++i)
		printf("%d\n",num[i]);
	
	return 0;	
} 
