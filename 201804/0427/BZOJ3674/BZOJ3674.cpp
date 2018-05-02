#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const int M=1e7+10;
int n,m,sz,ans,root[N];
int ls[M],rs[M],v[M],dep[M];

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

void build(int &x,int l,int r)
{
	if(!x)
		x=++sz;
	if(l==r)
	{
		v[x]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(ls[x],l,mid);
	build(rs[x],mid+1,r);
}

void update(int x,int &y,int l,int r,int pos,int val)
{
	y=++sz;
	if(l==r)
	{
		v[y]=val;dep[y]=dep[x];
		return;
	}
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(ls[x],ls[y],l,mid,pos,val);
	else
		update(rs[x],rs[y],mid+1,r,pos,val);
}

int query(int x,int l,int r,int pos)
{
	if(l==r)
		return x;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return query(ls[x],l,mid,pos);
	else
		return query(rs[x],mid+1,r,pos);
}

void add(int x,int l,int r,int pos)
{
	if(l==r)
	{
		dep[x]++;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(ls[x],l,mid,pos);
	else
		add(rs[x],mid+1,r,pos);
}

int findf(int x,int k)
{
	int t=query(x,1,n,k);
	if(k==v[t])
		return t;
	return findf(x,v[t]);
}

int main()
{
	freopen("BZOJ3674.in","r",stdin);
	freopen("BZOJ3674.out","w",stdout);
	
	n=read();m=read();
	build(root[0],1,n);
	for(int i=1;i<=m;++i)
	{
//cerr<<i<<endl;
		int opt,a,b,k;
		opt=read();
		if(opt==1)
		{
			root[i]=root[i-1];
			a=read();b=read();a^=ans;b^=ans;
			int fu=findf(root[i],a),fv=findf(root[i],b);
			if(v[fu]==v[fv])
				continue;
			if(dep[fu]>dep[fv])
				swap(fu,fv);
			update(root[i-1],root[i],1,n,v[fu],v[fv]);
			if(dep[fu]==dep[fv])
				add(root[i],1,n,v[fv]);
		}
		else
		if(opt==2)
		{
			k=read();k^=ans;
			root[i]=root[k];
		}
		else
		{
			root[i]=root[i-1];
			a=read();b=read();a^=ans;b^=ans;
			int fu=findf(root[i],a),fv=findf(root[i],b);
			if(v[fu]==v[fv])
				ans=1;
			else
				ans=0;
			printf("%d\n",ans);
		}
		
	}
	
	return 0;
}
