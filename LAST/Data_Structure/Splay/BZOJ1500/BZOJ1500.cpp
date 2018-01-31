#include<bits/stdc++.h>
#define key_val ch[ch[root][1]][0]
using namespace std;

const int INF=0x3f3f3f3f;
const int MAXN=5e5+10;
int n,m,top1,top2,root;
int a[MAXN],sum[MAXN],siz[MAXN],rev[MAXN],add[MAXN];
int pre[MAXN],L[MAXN],R[MAXN],key[MAXN],s[MAXN],mx[MAXN];
int ch[MAXN][2];

void update_rev(int x)
{
	if(x==0)
		return;
	swap(ch[x][0],ch[x][1]);
	swap(L[x],R[x]);
	rev[x]^=1;
}

void update_add(int x,int v)
{
	if(x==0)
		return;
	add[x]=key[x]=v;
	sum[x]=v*siz[x];
	L[x]=R[x]=mx[x]=max(v,v*siz[x]);
}

void pushup(int x)
{
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+key[x];
	L[x]=max(L[ch[x][0]],sum[ch[x][0]]+key[x]+max(0,L[ch[x][1]]));
	R[x]=max(R[ch[x][1]],sum[ch[x][1]]+key[x]+max(0,R[ch[x][0]]));
	mx[x]=max(0,R[ch[x][0]])+key[x]+max(0,L[ch[x][1]]);
	mx[x]=max(mx[x],max(mx[ch[x][0]],mx[ch[x][1]]));
}

void pushdown(int x)
{
	if(rev[x])
	{
		update_rev(ch[x][0]);
		update_rev(ch[x][1]);
		rev[x]=0;
	}
	if(add[x]!=-2333)
	{
		update_add(ch[x][0],add[x]);
		update_add(ch[x][1],add[x]);
		add[x]=-2333;
	}
}

void rotate(int x,int kind)
{
	int y=pre[x];
	pushdown(y);
	pushdown(x);
	
	ch[y][!kind]=ch[x][kind];
	pre[ch[x][kind]]=y;
	if(pre[y])
		ch[pre[y]][ch[pre[y]][1]==y]=x;
	pre[x]=pre[y];
	ch[x][kind]=y;
	pre[y]=x;
	pushup(y);
}

void splay(int x,int goal)
{
	while(pre[x]!=goal)
	{
		if(pre[pre[x]]==goal)
			rotate(x,ch[pre[x]][0]==x);
		else
		{
			int y=pre[x];
			int kind=ch[pre[y]][0]==y;
			
			if(ch[y][kind]==x)
			{
				rotate(x,!kind);
				rotate(x,kind);
			}
			else
			{
				rotate(y,kind);
				rotate(x,kind);
			}
		}
	}
	pushup(x);
	if(goal==0)
		root=x;
}


void new_node(int &x,int fa,int k)
{
	if(top2)
		x=s[top2--];
	else
		x=++top1;
	ch[x][0]=ch[x][1]=rev[x]=sum[x]=0;
	add[x]=-2333;
	pre[x]=fa;siz[x]=1;
	L[x]=R[x]=mx[x]=key[x]=k;
}

void build(int &x,int l,int r,int fa)
{
	if(l>r)
		return;
	int mid=(l+r)>>1;
	new_node(x,fa,a[mid]);
	build(ch[x][0],l,mid-1,x);
	build(ch[x][1],mid+1,r,x);
	pushup(x);
}

void init()
{
	root=top1=top2=0;
	ch[0][0]=ch[0][1]=pre[0]=siz[0]=rev[0]=key[0]=0;
	add[0]=-2333;
	L[0]=R[0]=mx[0]=-INF;
	new_node(root,0,INF);
	new_node(ch[root][1],root,INF);
	build(key_val,1,n,ch[root][1]);
	pushup(ch[root][1]);
	pushup(root);
}

int get_k(int x,int k)
{
	pushdown(x);
	int t=siz[ch[x][0]];
	if(t+1==k)
		return x;
	if(t+1<k)
		return get_k(ch[x][1],k-t-1);
	else
		return  get_k(ch[x][0],k);
}

void erase(int x)
{
	if(x)
	{
		s[++top2]=x;
		erase(ch[x][0]);
		erase(ch[x][1]);
	}
}

void INSERT(int p,int len)
{
	splay(get_k(root,p+1),0);
	splay(get_k(root,p+2),root);
	build(key_val,1,len,ch[root][1]);
	pushup(ch[root][1]);
	pushup(root);
}

void DELETE(int l,int r)
{
	splay(get_k(root,l),0);
	splay(get_k(root,r+2),root);
	erase(key_val);
	pre[key_val]=0;
	key_val=0;
	pushup(ch[root][1]);
	pushup(root);
}

void CHANGE(int l,int r,int c)
{
	splay(get_k(root,l),0);
	splay(get_k(root,r+2),root);
	update_add(key_val,c);
	pushup(ch[root][1]);
	pushup(root);
}

void REVERSE(int l,int r)
{
	splay(get_k(root,l),0);
	splay(get_k(root,r+2),root);
	update_rev(key_val);
	pushup(ch[root][1]);
	pushup(root);
}

int QUERY(int l,int r)
{
	splay(get_k(root,l),0);
	splay(get_k(root,r+2),root);
	return sum[key_val];
}

int QUERYSUM(int l,int r)
{
	splay(get_k(root,l),0);
	splay(get_k(root,r+2),root);
	return mx[key_val];
}

void debug(int x)
{
	if(ch[x][0])
		debug(ch[x][0]);
	printf("%d %d %d %d\n",x,key[x],sum[x],mx[x]);
	if(ch[x][1])
		debug(ch[x][1]);
}

int main()
{
//	freopen("BZOJ1500.in","r",stdin);
//	freopen("BZOJ1500.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	init();
//	printf("%d\n",root);
//	debug(root);
	while(m--)
	{
		char opt[10];
		int b,c,d;
		scanf("%s",opt);
		if(strcmp(opt,"INSERT")==0)
		{
			scanf("%d%d",&b,&c);
			for(int i=1;i<=c;++i)
				scanf("%d",&a[i]);
			INSERT(b,c);
		}
		else
		if(strcmp(opt,"DELETE")==0)
		{
			scanf("%d%d",&b,&c);
			DELETE(b,b+c-1);
		}
		else
		if(strcmp(opt,"MAKE-SAME")==0)
		{
			scanf("%d%d%d",&b,&c,&d);
			CHANGE(b,b+c-1,d);
		}
		else
		if(strcmp(opt,"REVERSE")==0)
		{
			scanf("%d%d",&b,&c);
			REVERSE(b,b+c-1);
		}
		else
		if(strcmp(opt,"GET-SUM")==0)
		{
			scanf("%d%d",&b,&c);
			printf("%d\n",QUERY(b,b+c-1));
//			printf("%d\n",root);
//			debug(root);
		}
		else
			printf("%d\n",QUERYSUM(1,siz[root]-2));
//		if(m==7)
//			return 0;
//		debug(root);
//		printf("\n");
	}
	
	return 0;
}
