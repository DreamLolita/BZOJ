#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,tot;
int w1[N<<1],w2[N<<1];
bool vis[N];

struct Tdata
{
	int x,op,id;
};
Tdata p[N<<1];

bool cmp(Tdata A,Tdata B)
{
	if(A.x==B.x)
		return A.op<B.op;
	return A.x>B.x;
}

struct Tnode
{
	int xl,yl,xr,yr;
};
Tnode a[N];

struct Tqueue
{
	priority_queue<int>q,p;
	void dele(){
		while(!p.empty() && q.top()==p.top())
			q.pop(),p.pop();
	}
	int top(){
		dele();return q.top();
	}
	bool empty(){
		dele();return q.empty();
	}
	void push(int x){
		q.push(x);
	}
	void erase(int x){
		p.push(x);
	}
};

struct Seqment
{
	int mx[N<<3],mn[N<<3];
	Tqueue col[N<<3];

	void update(int x,int l,int r)
	{
		if(l^r)
		{
			mn[x]=min(mn[x<<1],mn[x<<1|1]);
			mx[x]=max(mx[x<<1],mx[x<<1|1]);
		}
		else
			mn[x]=mx[x]=0;
		//cerr<<"unhappy"<<endl;
		if(!col[x].empty())
		{
			int t=col[x].top();
		//cerr<<"unhappy"<<endl;
			if(vis[t])
				mn[x]=max(mn[x],t);
			else
				mx[x]=max(mx[x],t);
			if(mn[x]>mx[x])
				mx[x]=0;
		}
	}

	void ins(int x,int l,int r,int L,int R,int v)
	{
		//cerr<<l<<" "<<r<<" "<<v<<endl;
		if(L<=l && r<=R)
		{
			//cerr<<"happy"<<endl;
			if(v>0)
				col[x].push(v);
			else
			if(v<0)
				col[x].erase(-v);
			//cerr<<"happy"<<endl;
			update(x,l,r);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)
			ins(x<<1,l,mid,L,R,v);
		if(R>mid)
			ins(x<<1|1,mid+1,r,L,R,v);
		update(x,l,r);
	}
}tr;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF983D.in","r",stdin);
	freopen("CF983D.out","w",stdout);
#endif
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i].xl=read();a[i].yl=read();a[i].xr=read();a[i].yr=read();
		w1[i]=a[i].xl;w1[i+n]=a[i].xr;
		w2[i]=a[i].yl;w2[i+n]=a[i].yr;
	}
	sort(w1+1,w1+n*2+1);sort(w2+1,w2+n*2+1);
	for(int i=1;i<=n;++i)
	{
		a[i].xl=lower_bound(w1+1,w1+n*2+1,a[i].xl)-w1;
		a[i].xr=lower_bound(w1+1,w1+n*2+1,a[i].xr)-w1;	
		a[i].yl=lower_bound(w2+1,w2+n*2+1,a[i].yl)-w2;
		a[i].yr=lower_bound(w2+1,w2+n*2+1,a[i].yr)-w2-1;
		p[++tot].x=a[i].xr;p[tot].op=0;p[tot].id=i;
		p[++tot].x=a[i].xl;p[tot].op=1;p[tot].id=i;
		//printf("%d %d %d %d\n",a[i].xl,a[i].yl,a[i].xr,a[i].yr);
	}
	sort(p+1,p+tot+1,cmp);

	int l=1,ans=0;
	while(l<=tot)
	{
		int r=l;
		while(r<tot && p[r+1].x==p[l].x)
			++r;
		while(l<=r)
		{
			//cerr<<a[p[l].id].yl<<" "<<a[p[l].id].yr<<endl;
			if(!p[l].op)
				tr.ins(1,1,n<<1,a[p[l].id].yl,a[p[l].id].yr,p[l].id);
			else
				tr.ins(1,1,n<<1,a[p[l].id].yl,a[p[l].id].yr,-p[l].id);
			++l;
		}
		while(tr.mx[1])
		{
			++ans;
			int x=tr.mx[1];vis[x]=1;
			tr.ins(1,1,n<<1,a[x].yl,a[x].yr,0);
		}
	}
	printf("%d\n",ans+1);

	return 0;
}
