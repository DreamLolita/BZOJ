#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f;
const int MAXN=1e5+10;
int n,root,top1,ans;
int pre[MAXN],key[MAXN];
int ch[MAXN][2];

void rotate(int x,int kind)
{
	int y=pre[x];
//	pushdown(y);
//	pushdown(x);
	
	ch[y][!kind]=ch[x][kind];
	pre[ch[x][kind]]=y;
	
	if(pre[y])
		ch[pre[y]][ch[pre[y]][1]==y]=x;
	pre[x]=pre[y];
	ch[x][kind]=y;
	pre[y]=x;
//	pushup(y);
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
//	pushup(x);
	if(goal==0)
		root=x;
}

int get_pre(int x)
{
	int y=ch[x][0];
	while(ch[y][1])
		y=ch[y][1];
	return key[y];
}

int get_suc(int x)
{
	int y=ch[x][1];
	while(ch[y][0])
		y=ch[y][0];
	return key[y];
}

void new_node(int &x,int fa,int k)
{
	x=++top1;
	ch[x][0]=ch[x][1]=0;
	pre[x]=fa;key[x]=k;
}

void INSERT(int x,int k)
{
	int y;
	while(true)
	{
		y=ch[x][key[x]<k];
		if(y==0)
		{
			new_node(y,x,k);
			ch[x][key[x]<k]=y;
			break;
		}
		x=y;
	}
	splay(y,0);
}

void init()
{
	int x;
	scanf("%d",&x);
	ans+=x;
	
	root=top1=0;
	ch[0][0]=ch[0][1]=key[0]=pre[0]=0;
	new_node(root,0,x);
	new_node(ch[root][1],root,INF);
	new_node(ch[root][0],root,-INF);
}

int main()
{
	
	scanf("%d",&n);
	init();
	for(int i=2;i<=n;++i)
	{
		int x;
		scanf("%d",&x);

		INSERT(root,x);
		int cl=get_pre(root);
		int cr=get_suc(root);
//		printf("%d %d %d\n",x,cl,cr);

		ans+=min(abs(x-cl),abs(cr-x));
	}
	printf("%d\n",ans);
	
	return 0;
}
