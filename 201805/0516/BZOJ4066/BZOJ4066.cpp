#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=2e5+10;
const int lim=9387;
int n,D;
LL ans;

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

bool inmp(int xl,int yl,int xxl,int yyl,int xr,int yr,int xxr,int yyr)//l in r
{
	return xl<=xr && yl<=yr && xxl>=xxr && yyl>=yyr;
}

bool outmp(int xl,int yl,int xxl,int yyl,int xr,int yr,int xxr,int yyr)
{
	return xl>xxr || xxl<xr || yl>yyr || yyl<yr;
}

struct Tnode
{
	int d[2],mx[2],mi[2],v,ls,rs;
	LL sum;
	
	friend bool operator==(Tnode A,Tnode B){
		return A.d[0]==B.d[0] && A.d[1]==B.d[1];
	}
	
	friend bool operator<(Tnode A,Tnode B){
		return A.d[D]<B.d[D];
	}
};
Tnode p[N];

struct KDT
{
	int rt,sz,cnt;
	Tnode t[N],now;
	
	void pushup(int x)
	{
		int l=t[x].ls,r=t[x].rs;
		for(int i=0;i<2;++i)
		{
			t[x].mi[i]=t[x].mx[i]=t[x].d[i];
			if(l)
				t[x].mi[i]=min(t[x].mi[i],t[l].mi[i]),t[x].mx[i]=max(t[x].mx[i],t[l].mx[i]);
			if(r)
				t[x].mi[i]=min(t[x].mi[i],t[r].mi[i]),t[x].mx[i]=max(t[x].mx[i],t[r].mx[i]);
		}
		t[x].sum=t[x].v+t[l].sum+t[r].sum;
	}
	
	void insert(int &x,int nd)
	{
		if(!x)
		{
			x=++sz;++cnt;
			t[x].d[0]=t[x].mi[0]=t[x].mx[0]=now.d[0];
			t[x].d[1]=t[x].mi[1]=t[x].mx[1]=now.d[1];
		}
		if(now==t[x])
		{
			t[x].v+=now.v;t[x].sum+=now.v;
			return;
		}
		if(now.d[nd]<t[x].d[nd])
			insert(t[x].ls,nd^1);
		else
			insert(t[x].rs,nd^1);
		pushup(x);
	}
	
	LL query(int x,int lx,int ly,int rx,int ry)
	{
		if(!x)
			return 0;
		LL ret=0;
		if(inmp(lx,ly,rx,ry,t[x].mi[0],t[x].mi[1],t[x].mx[0],t[x].mx[1]))
			return t[x].sum;
		if(outmp(lx,ly,rx,ry,t[x].mi[0],t[x].mi[1],t[x].mx[0],t[x].mx[1]))
			return 0;
		if(inmp(lx,ly,rx,ry,t[x].d[0],t[x].d[1],t[x].d[0],t[x].d[1]))
			ret+=t[x].v;
		ret+=query(t[x].ls,lx,ly,rx,ry)+query(t[x].rs,lx,ly,rx,ry);
		return ret;
	}
	
	int rebuild(int l,int r,int nd)
	{
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		D=nd;nth_element(p+l,p+mid,p+r+1);
		t[mid]=p[mid];
		t[mid].ls=rebuild(l,mid-1,nd^1);
		t[mid].rs=rebuild(mid+1,r,nd^1);
		pushup(mid);
		return mid;
	}
};
KDT tr;

int main()
{
	freopen("BZOJ4066.in","r",stdin);
	freopen("BZOJ4066.out","w",stdout);

	n=read();
	while(true)
	{
		int opt=read();
		if(opt==3)
			break;
		int x,y,xx,yy;
		x=read()^ans;y=read()^ans;xx=read()^ans;
		if(opt&1)
		{
			tr.now.v=tr.now.sum=xx;
			tr.now.d[0]=x;tr.now.d[1]=y;
			tr.insert(tr.rt,0);
			if(tr.cnt==lim)
			{
				for(int i=1;i<=tr.sz;++i)
					p[i]=tr.t[i];
				tr.rt=tr.rebuild(1,tr.sz,0);tr.cnt=0;
			}
		}
		else
		{
			yy=read()^ans;
			ans=tr.query(tr.rt,x,y,xx,yy);
			printf("%lld\n",ans);
		}
	}

	return 0;
}

