#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=2e5+10;
int n;
int ta[N],tb[N];
priority_queue<int,vector<int>,greater<int> >q;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Splay
{
	int root,sz;
	int fa[N],siz[N],sizu[N],sizd[N],key[N];
	int ch[N][2];
    LL sum[N];
	
	void pushup(int x)
	{
		int ls=ch[x][0],rs=ch[x][1];
		siz[x]=siz[ls]+siz[rs]+1;
		sizu[x]=sizu[ls]+sizu[rs]+(key[x]>0);
		sizd[x]=sizd[ls]+sizd[rs]+(key[x]<0);
		sum[x]=sum[ls]+sum[rs]+key[x];
	}
	
	void rotate(int x,int &k)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==k)
			k=x;
		else
			ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[y]=x;fa[x]=z;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x,int &goal)
	{
		while(x!=goal)
		{
			int y=fa[x],z=fa[y];
			if(y!=goal)
			{
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x,goal);
				else
					rotate(y,goal);
			}
			rotate(x,goal);
		}
	}
	
	int find(int x,int k)
	{
		if(siz[ch[x][0]]+1==k)
			return x;
		if(k<=siz[ch[x][0]])
			return find(ch[x][0],k);
		return find(ch[x][1],k-siz[ch[x][0]]-1);
	}
	
	void insert1(int &x,int val,int f)
	{
		if(!x)
		{
			x=++sz;fa[x]=f;key[x]=val;siz[x]=sizu[x]=1;
			pushup(x);splay(x,root);
			return;
		}
		insert1(ch[x][1],val,x);
	}
	
	void insert2(int &x,int p,int val,int f)
	{
		if(!x)
		{
			x=++sz;fa[x]=f;key[x]=val;siz[x]=sizd[x]=1;
			pushup(x);splay(x,root);
			return;
		}
		int &ls=ch[x][0],&rs=ch[x][1];
		if(p<=sizd[ls]+(key[x]<0))
			insert2(ls,p,val,x);
		else
			insert2(rs,p-(sizd[ls]+(key[x]<0)),val,x);
	}
	
	void dele(int x)
	{
		splay(x,root);int pre=ch[root][0],suc=ch[root][1];
		while(ch[pre][1]) pre=ch[pre][1];
		while(ch[suc][0]) suc=ch[suc][0];
		splay(suc,root);splay(pre,ch[root][0]);
		ch[pre][1]=0;
		pushup(pre);pushup(root);
	}
	
	void init()
	{
		sz=2;memset(siz,0,sizeof(siz));memset(sizu,0,sizeof(sizu));memset(sizd,0,sizeof(sizd));
		memset(fa,0,sizeof(fa));memset(ch,0,sizeof(ch));memset(key,0,sizeof(key));
		siz[1]=2;key[1]=-INF;fa[2]=1;root=1;ch[1][0]=2;key[2]=INF;pushup(2);pushup(1);
	}
	
	void doit(int p,int x)
	{
		int t=find(root,p+2);
		splay(t,root);splay(2,ch[t][0]);
		int sk=sizu[ch[2][1]];
		insert1(ch[root][0],x,root);ta[x]=sz;insert2(root,sk+1,-x,root);tb[x]=sz;
	}
	
	void query(int x)
	{
		splay(tb[x],root);splay(ta[x],ch[root][0]);
		printf("%lld\n",sum[ch[ta[x]][1]]);
	}
}tr;

void _reset()
{
	tr.root=0;
	while(!q.empty()) 
		q.pop();
	for(int i=1;i<=n;++i)
		q.push(i);
	tr.init();
}

void solve()
{
	for(int i=1;i<=n;++i)
	{
//cerr<<i<<endl;
		char opt[8];scanf("%s",opt);
		if(opt[0]=='i')
		{
			int p=read(),x=q.top();q.pop();
			tr.doit(p,x);
		}
		else
		if(opt[0]=='r')
		{
			int x=read();q.push(x);
			tr.dele(ta[x]);tr.dele(tb[x]);			
		}
		else
		{
			int x=read();
			tr.query(x);
		}
	}
}

int main()
{
	freopen("HDU4441.in","r",stdin);
	freopen("HDU4441.out","w",stdout);
	
	int cas=0;
	while(~scanf("%d",&n))
	{
		printf("Case #%d:\n",++cas);
		_reset();
		solve();
	}
	
	
	return 0;
}
