#include<bits/stdc++.h>
using namespace std;

const int INF=5e8;
const int N=1e5+10;
int n,m;
int a[N],b[N],sum[N];

struct Tdata
{
	int opt,x,y,ans;
};
Tdata q[N<<2];

struct Seqmenet
{
	int siz,root;
	int ls[N*100],rs[N*100],s[N*100];

	void init()
	{
		siz=root=0;
	}

	int newnode()
	{
		++siz;
		ls[siz]=rs[siz]=s[siz]=0;
		return siz;
	}
	
	void update(int &rt,int l,int r,int L,int R,int v)
	{
		if(!rt)
			rt=newnode();
		if(L<=l && r<=R)
		{
			s[rt]+=v;
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)
			update(ls[rt],l,mid,L,R,v);
		if(R>mid)
			update(rs[rt],mid+1,r,L,R,v);
	}
	
	int query(int rt,int l,int r,int p)
	{
		if(!rt)
			return 0;
		if(l==r)
			return s[rt];
		int mid=(l+r)>>1;
		if(p<=mid)
			return query(ls[rt],l,mid,p)+s[rt];
		else
			return query(rs[rt],mid+1,r,p)+s[rt];
	}
}tr;


void solve()
{
	tr.init();sum[0]=1;
	int now=1,tar=0,ans=0;
	
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	for(int i=1;i<n;++i)
		tr.update(tr.root,0,2*INF,min(sum[i],sum[i+1])+INF,max(sum[i],sum[i+1])+INF,1);
	for(int i=0;i<n;++i)
		if(1ll*sum[i]*sum[i+1]<0)
			++ans;
	
	for(int i=1;i<=m;++i)
	{
		if(q[i].opt==1)
		{
			if(now==1)
				continue;
			--now;sum[now]-=tar;
			tr.update(tr.root,0,INF*2,min(sum[now],sum[now+1])+INF,max(sum[now],sum[now+1])+INF,1);
		}
		else
		if(q[i].opt==2)
		{
			if(now==n)
				continue;
			tr.update(tr.root,0,INF*2,min(sum[now],sum[now+1])+INF,max(sum[now],sum[now+1])+INF,-1);
			sum[now]+=tar;++now;
		}
		else
		if(q[i].opt==3)
		{
			ans-=tr.query(tr.root,0,INF*2,INF-tar);
			if(1ll*sum[now-1]*(sum[now]+tar)<0)
				--ans;
			ans+=tr.query(tr.root,0,INF*2,a[now]-q[i].x-tar+INF);
			tar+=q[i].x-a[now];a[now]=q[i].x;
			if(1ll*sum[now-1]*(sum[now]+tar)<0)
				++ans;
		}
		else
			q[i].ans+=ans;
//		printf("opt:%d ans:%d %d %d\n",q[i].opt,ans,now,tar);
	}
}

int main()
{
	freopen("LOJ503.in","r",stdin);
	freopen("LOJ503.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i],&b[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		char op[2];scanf("%s",op);
		if(op[0]=='B')
			q[i].opt=1;
		else
		if(op[0]=='F')
			q[i].opt=2;
		else
		if(op[0]=='C')
			q[i].opt=3,scanf("%d%d",&q[i].x,&q[i].y);
		else
			q[i].opt=4;
	}
	solve();
	for(int i=1;i<=n;++i)
		swap(a[i],b[i]);
	for(int i=1;i<=m;++i)
		swap(q[i].x,q[i].y);
	solve();
	for(int i=1;i<=m;++i)
		if(q[i].opt==4)
			printf("%d\n",q[i].ans);
	
	return 0;
}
