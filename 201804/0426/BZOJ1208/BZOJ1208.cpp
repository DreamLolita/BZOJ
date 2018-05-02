#include<bits/stdc++.h>
using namespace std;

const int mod=1e6;
const int N=1e5+10;
int n,m,t1,t2,ans;

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Splay
{
	int sz,rt,typ;
	int ch[N][2],fa[N],num[N];
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==rt)
			rt=x;
		else
			ch[z][ch[z][1]==y]=x;
		fa[x]=z;fa[y]=x;fa[ch[x][!kind]]=y;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
	}
	
	void splay(int x)
	{
		while(x!=rt)
		{
			int y=fa[x],z=fa[y];
			if(z)
			{
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
	}
	
	void insert(int &x,int nm,int las)
	{
		if(!x)
		{
			x=++sz;num[x]=nm;fa[x]=las;splay(x);
			return;
		}
		if(nm<num[x])
			insert(ch[x][0],nm,x);
		else
			insert(ch[x][1],nm,x);
	}
	
	void dele(int x)
	{
		splay(x);
		if(!ch[x][0] || !ch[x][1])
			rt=ch[x][0]+ch[x][1];
		else
		{
			int t=ch[x][1];
			while(ch[t][0])
				t=ch[t][0];
			ch[t][0]=ch[x][0];fa[ch[x][0]]=t;
			rt=ch[x][1];
		}
		fa[rt]=0;
	}
	
	void querypre(int x,int k)
	{
		if(!x)
			return;
		if(num[x]<=k)
			t1=x,querypre(ch[x][1],k);
		else
			querypre(ch[x][0],k);
	}
	
	void querysuc(int x,int k)
	{
		if(!x)
			return;
		if(num[x]>=k)
			t2=x,querysuc(ch[x][0],k);
		else
			querysuc(ch[x][1],k);
	}

	void solve(int x)
	{
		t1=t2=-1;
		querypre(rt,x);querysuc(rt,x);
		if(t1==-1)
		{
			ans+=num[t2]-x;ans%=mod;
			dele(t2);
		}
		else
		if(t2==-1)
		{
			ans+=x-num[t1];ans%=mod;
			dele(t1);
		}
		else
		{
			if(x-num[t1]>num[t2]-x)
			{
				ans+=num[t2]-x;ans%=mod;
				dele(t2);
			}
			else
			{
				ans+=x-num[t1];ans%=mod;
				dele(t1);
			}
		}
	}
}tr;

int main()
{
	freopen("BZOJ1208.in","r",stdin);
	freopen("BZOJ1208.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;++i)
	{
		int opt=read(),x=read();
		if(!tr.rt)
			tr.typ=opt,tr.insert(tr.rt,x,0);
		else
		if(tr.typ==opt)
			tr.insert(tr.rt,x,0);
		else
			tr.solve(x);
	}
	printf("%d\n",ans);
	
	return 0;
}
