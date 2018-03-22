#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m;
int a[N];

struct Splay
{
	int rt;
	int siz[N],fa[N],a[N],t[2];
	int ch[N][2];
	
	void init()
	{
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			ch[a[i-1]][1]=a[i];
			fa[a[i]]=a[i-1];siz[a[i]]=n-i+1;
		}
		rt=a[1];ch[0][1]=0;
	}
	
	void pushup(int x)
	{
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	}
	
	void rotate(int x,int k)
	{
		int y=fa[x];
		ch[y][!k]=ch[x][k];
		fa[ch[x][k]]=y;
		
		if(fa[y])
			ch[fa[y]][ch[fa[y]][1]==y]=x;
		fa[x]=fa[y];ch[x][k]=y;fa[y]=x;
		pushup(y);pushup(x);
	}
	
	void splay(int x,int goal)
	{
		while(fa[x]!=goal)
		{
//			printf("%d %d\n",x,goal);
			if(fa[fa[x]]==goal)
				rotate(x,ch[fa[x]][0]==x);
			else
			{
				int y=fa[x],k=ch[fa[y]][0]==y;
				if(ch[y][k]==x)
				{
					rotate(x,!k);
					rotate(x,k);
				}
				else
				{
					rotate(y,k);
					rotate(x,k);
				}
			}
		}
		if(goal==0)
			rt=x;
	}
	
	void make_up(int x,int k)
	{
		splay(x,0);
		if(!ch[x][k])	return;
		t[0]=t[1]=ch[x][k];
		while(ch[t[0]][0])
			t[0]=ch[t[0]][0];
		while(ch[t[1]][1])
			t[1]=ch[t[1]][1];
		rt=ch[x][k];
		fa[rt]=0;ch[t[k]][k]=x;
		fa[ch[x][!k]]=t[!k];ch[t[!k]][!k]=ch[x][!k];
		fa[x]=t[k];ch[x][0]=ch[x][1]=0;
		siz[x]=1;
		
		while(fa[x])
		{
			siz[fa[x]]++;
			x=fa[x];
		}
		while(t[!k])
		{
			pushup(t[!k]);
			t[!k]=fa[t[!k]];
		}
		siz[rt]=n;
	}
	
	void swp(int x,int d)
	{
		if(!d)	return;
		splay(x,0);
		if(d==-1)	d=0;
		int r=ch[x][d];
		while(ch[r][!d])
			r=ch[r][!d];
		splay(r,x);
		fa[x]=r;fa[r]=0;
		fa[ch[r][d]]=x;fa[ch[x][!d]]=r;
		ch[x][d]=ch[r][d];ch[r][!d]=ch[x][!d];
		ch[r][d]=x;ch[x][!d]=0;
		swap(siz[x],siz[r]);
		rt=r;
	}
	
	int get_k(int r,int x)
	{
		if(siz[ch[r][0]]+1==x)
			return r;
		if(siz[ch[r][0]]+1>x)
			return get_k(ch[r][0],x);		
		return get_k(ch[r][1],x-siz[ch[r][0]]-1);
	}
	
	void query(int x)
	{
		splay(x,0);
		printf("%d\n",siz[ch[x][0]]);
	}
};
Splay tr;

int main()
{
	freopen("BZOJ1861.in","r",stdin);
	freopen("BZOJ1861.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	tr.init();
	for(int i=1;i<=m;++i)
	{
		int x,y;char opt[8];
		scanf("%s%d",opt,&x);
		if(opt[0]=='A')
			tr.query(x);
		else
		if(opt[0]=='T')
			tr.make_up(x,0);
		else
		if(opt[0]=='B')
			tr.make_up(x,1);
		else
		if(opt[0]=='I')
			scanf("%d",&y),tr.swp(x,y);
		else
			printf("%d\n",tr.get_k(tr.rt,x));
	}
	
	return 0;
}
