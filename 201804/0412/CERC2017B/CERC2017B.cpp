#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10;
const int M=N*4;
int n,m,tot;
int las[N],cnt[N],f[N],ans[N];

struct Tdata
{
	int x,y,id;
	Tdata(){}
	Tdata(int x,int y,int id):x(x),y(y),id(id){}
}a[M];

bool cmp(Tdata A,Tdata B)
{
	if(A.y^B.y)
		return A.y>B.y;
	return A.x<B.x;
}

struct Tele
{
	int x,t;
	Tele(){}
	Tele(int x,int t):x(x),t(t){}
	bool operator <(const Tele &A)const{
		if(x^A.x)
			return x<A.x;
		return t<A.t;
	}
};

struct Splay
{
	int root,len;
	int ch[M][2],fa[M];
	Tele val[M];
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=ch[fa[x]][1]==x,t=ch[x][!kind];
		ch[y][kind]=t;ch[x][!kind]=y;
		if(t)
			fa[t]=y;
		fa[x]=z;
		if(z)
			ch[z][ch[fa[y]][1]==y]=x;
		fa[y]=x;
	}
	
	void splay(int x)
	{
		while(fa[x])
		{
			int y=fa[x];
			if(fa[y])
			{
				if(ch[fa[x]][1]==x^ch[fa[y]][1]==y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
		root=x;
	}
	
	void insert(int x,int t)
	{
		val[++len]=Tele(x,t);
		if(!root)
		{
			root=len;
			return;
		}
		int now=root;
		while(true)
		{
			if(val[len]<val[now])
			{
				if(!ch[now][0])
				{
					ch[now][0]=len;
					fa[len]=now;
					break;
				}
				now=ch[now][0];
			}
			else
			{
				if(!ch[now][1])
				{
					ch[now][1]=len;
					fa[len]=now;
					break;
				}
				now=ch[now][1];
			}
		}
		splay(len);
	}
	
	int findpre()
	{
		int x=ch[root][0];
		while(ch[x][1])
			x=ch[x][1];
		return x;
	}
	
	int findsuc()
	{
		int x=ch[root][1];
		while(ch[x][0])
			x=ch[x][0];
		return x;
	}
	
	void reset(int x)
	{
		ch[x][0]=ch[x][1]=fa[x]=0;
		val[x].x=val[x].t=0;
	}
	
	void dele(int x)
	{
		splay(x);
		if(!ch[x][0] || !ch[x][1])
		{
			root=ch[x][0]+ch[x][1];
			fa[root]=0;
			reset(x);
			return;
		}
		int now=findsuc();
		splay(now);ch[now][0]=ch[x][0];
		fa[ch[now][0]]=now;
		reset(x);
	}
}tr;

int findf(int x)
{
	return f[x]?f[x]=findf(f[x]):x;
}

void merge(int x,int y)
{
	x=findf(x);y=findf(y);
	if(x^y)
		f[x]=y,cnt[y]+=cnt[x];
}

int main()
{
	freopen("CERC2017B.in","r",stdin);
	freopen("CERC2017B.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=Tdata((x<<1)-1,(y<<1)-1,0);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i+n]=Tdata(x<<1,y<<1,i);
	}
	tot=n+m;
	sort(a+1,a+tot+1,cmp);

	for(int i=1;i<=tot;++i)
	{
		tr.insert(a[i].x,a[i].id);
		if(a[i].id)
		{
			int suc=tr.findsuc();
//printf("%d\n",suc);
			if(suc)
				las[a[i].id]=tr.val[suc].t;
			while(true)
			{
				int pre=tr.findpre();
				if(!pre || tr.val[pre].t<a[i].id)
					break;
				tr.dele(pre);
			}
		}
		else
		{
			int suc=tr.findsuc();
//printf("!%d\n",suc);
			tr.dele(tr.root);
			if(suc)
				cnt[tr.val[suc].t]++;
		}
	}
	
	for(int i=m;i;--i)
	{
		ans[i]=cnt[findf(i)];
		if(las[i])
			merge(i,las[i]);
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	
	return 0;
}
