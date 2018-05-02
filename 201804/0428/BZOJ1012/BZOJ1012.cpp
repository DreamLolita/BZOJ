#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=1e9;
const LL N=1e6+10;
LL m,ans,mod;

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Splay
{
	LL sz,len,root;
	LL siz[N],key[N],mx[N];
	LL fa[N],ch[N][2];

	void pushup(LL x)
	{
		LL ls=ch[x][0],rs=ch[x][1];
		siz[x]=siz[ls]+siz[rs]+1;
		mx[x]=max(key[x],mx[ls]);
		mx[x]=max(mx[x],mx[rs]);
	}
	
	void rotate(LL x,LL &goal)
	{
		LL y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==goal)
			goal=x;
		else
			ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[y]=x;fa[x]=z;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(LL x,LL &goal)
	{
		while(x^goal)
		{
			LL y=fa[x],z=fa[y];
			if(y^goal)
			{
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x,goal);
				else
					rotate(y,goal);
			}
			rotate(x,goal);
		}
	}
	
	LL find(LL x,LL k)
	{
//printf("find:%d %d %d\n",x,k,siz[ch[x][0]]);
		if(siz[ch[x][0]]+1==k)
			return x;
		if(siz[ch[x][0]]>=k)
			return find(ch[x][0],k);
		return find(ch[x][1],k-siz[ch[x][0]]-1);
	}
	
	void insert(LL &x,LL val,LL f)
	{
		x=++sz;fa[x]=f;key[x]=val;siz[x]=1;
//printf("sz:%d val:%d nowfa:%d\n",x,val,f);
		pushup(x);splay(x,root);
	}
	
	void inse(LL x)
	{
		LL t=find(root,len+1);
//printf("!!!!!!root:%d t:%d %d %d\n",root,t,len,x);
		splay(t,root);
		insert(ch[root][1],x,root);++len;
	}
	
	void query(LL x)
	{
		LL t=find(root,len-x+1);
//printf("!root:%d t:%d %d %d\n",root,t,len,x);
		splay(t,root);
		ans=mx[ch[root][1]];
	}
	
	void init()
	{
		len=0;sz=1;mx[1]=key[1]=0;root=1;
		pushup(1);
	}
	
	void debug(LL x)
	{
		if(ch[x][0])
			debug(ch[x][0]);
		printf("debug:%d %d %d\n",x,key[x],mx[x]);
		if(ch[x][1])
			debug(ch[x][1]);
	}
}tr;

int main()
{
	freopen("BZOJ1012.in","r",stdin);
	freopen("BZOJ1012.out","w",stdout);
	
	m=read();mod=read();tr.init();
	while(m--)
	{
		char opt[3];LL x;
		scanf("%s",opt);x=read();
		if(opt[0]=='Q')
			tr.query(x),printf("%d\n",ans);
		else
		{
			LL t=(x+ans)%mod;
			tr.inse(t);
		}
//		tr.debug(tr.root);
//		puts("");
	}
	
	return 0;
}
