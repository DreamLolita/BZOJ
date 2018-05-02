#include<bits/stdc++.h>
using namespace std;

const int N=1e5+1;
const int P=1e5+10;
const int M=P*108;
int n,m,ans;
int a[P],mx[P],mi[P];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret*f;
}

struct Seqment
{
	int sz;
	int ch[M][3];
	
	void update2(int rt,int l,int r,int mxi,int f)
	{
		int mid=(l+r)>>1;
		ch[rt][2]=max(ch[rt][2],f);
		if(l==r)
			return;
		else
		if(mxi<=mid)
		{
			if(!ch[rt][0])
				ch[rt][0]=++sz;
			update2(ch[rt][0],l,mid,mxi,f);
		}
		else
		{
			if(!ch[rt][1])
				ch[rt][1]=++sz;
			update2(ch[rt][1],mid+1,r,mxi,f);
		}
	}
	
	void update(int rt,int l,int r,int ai,int mxi,int f)
	{
		int mid=(l+r)>>1;
		if(!ch[rt][2])
			ch[rt][2]=++sz;
		update2(ch[rt][2],1,N,mxi,f);
		if(l==r)
			return;
		else
		if(ai<=mid)
		{
			if(!ch[rt][0])
				ch[rt][0]=++sz;
			update(ch[rt][0],l,mid,ai,mxi,f);
		}
		else
		{
			if(!ch[rt][1])
				ch[rt][1]=++sz;
			update(ch[rt][1],mid+1,r,ai,mxi,f);
		}
	}
	
	int query2(int rt,int l,int r,int a0,int ai)
	{
		int mid=(l+r)>>1;
		if(l==a0 && r==ai)
			return ch[rt][2];
		else
		if(ai<=mid)
		{
			if(!ch[rt][0])
				return 0;
			return query2(ch[rt][0],l,mid,a0,ai);
		}
		else
		{
			int ret=0;
			if(ch[rt][1])
				ret=query2(ch[rt][1],mid+1,r,mid+1,ai);
			if(ch[rt][0])
				ret=max(ret,ch[ch[rt][0]][2]);
			return ret;
		}
	}
	
	int query(int rt,int l,int r,int mi0,int mii,int a0,int ai)
	{
		int mid=(l+r)>>1;
		if(mi0==l && r==mii)
		{
			if(!ch[rt][2])
				return 0;
			return query2(ch[rt][2],1,N,a0,ai);
		}
		else
		if(mii<=mid)
		{
			if(!ch[rt][0])
				return 0;
			return query(ch[rt][0],l,mid,mi0,mii,a0,ai);
		}
		else
		{
			int ret=0;
			if(ch[rt][1])
				ret=query(ch[rt][1],mid+1,r,mid+1,mii,a0,ai);
			if(ch[rt][0] && ch[ch[rt][0]][2])
				ret=max(ret,query2(ch[ch[rt][0]][2],1,N,a0,ai));
			return ret;
		}
	}
}tr;

int main()
{
	freopen("BZOJ4553.in","r",stdin);
	freopen("BZOJ4553.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
		a[i]=read()+1,mx[i]=mi[i]=a[i];
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read()+1;
		mx[x]=max(mx[x],y);mi[x]=min(mi[x],y);
	}
	
	tr.sz=1;
	tr.update(1,1,N,1,1,0);
	for(int i=1;i<=n;++i)
	{
		int t=tr.query(1,1,N,1,mi[i],1,a[i])+1;
		ans=max(ans,t);
		tr.update(1,1,N,a[i],mx[i],t);
	}
	printf("%d\n",ans);
	
	return 0;
}
