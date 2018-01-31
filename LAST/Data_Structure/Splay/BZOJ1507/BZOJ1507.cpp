#include<bits/stdc++.h>
#define key_val ch[ch[root][1]][0]
using namespace std;

const int MAXN=1024*1024*2+10;
int n,top1,root,T;
int pre[MAXN],siz[MAXN],ch[MAXN][2];
char opt[20],ins[MAXN],key[MAXN];
bool flag;

void debug(int x)
{
	if(ch[x][0])
		debug(ch[x][0]);
	printf("%d %d %d %d %d %d\n",x,(int)key[x],siz[x],ch[x][0],ch[x][1],pre[x]);
	if(ch[x][1])
		debug(ch[x][1]);
}

void new_node(int &x,int fa,char k)
{
	x=++top1;
	ch[x][0]=ch[x][1]=0;
	pre[x]=fa;siz[x]=1;key[x]=k;
}

void pushup(int x)
{
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}

void build(int &x,int l,int r,int fa)
{
	if(l>r)
		return;
	int mid=(l+r)>>1;
	new_node(x,fa,ins[mid]);
	build(ch[x][0],l,mid-1,x);
	build(ch[x][1],mid+1,r,x);
	pushup(x);
}

void init()
{
	ch[0][0]=ch[0][1]=pre[0]=siz[0]=flag=0;
	new_node(root,0,'\n');
	new_node(ch[root][1],root,'\n');
}

int get_k(int x,int k)
{
	int t=siz[ch[x][0]];
	if(t+1==k)
	{
//		printf("x:%d\n",x);
		return x;
	}
	if(t+1<k)
		return get_k(ch[x][1],k-t-1);
	else
		return get_k(ch[x][0],k);
}

void rotate(int x,int kind)
{
	int y=pre[x];
	
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

void INSERT(int p,int len)
{
//	debug(root);
//	if(T==10)return;
//	printf("k:%d\n",get_k(root,p+1));
	splay(get_k(root,p+1),0);
	splay(get_k(root,p+2),root);
	build(key_val,1,len,ch[root][1]);
	pushup(ch[root][1]);
	pushup(root);
}

void DELETE(int p,int len)
{
//	int p1=get_k(root,p+1),p2=get_k(root,p+len+2);
//printf("first:\n");debug(root);
//printf("    %d   ",get_k(root,p+1));
	splay(get_k(root,p+1),0);
//printf("first:\n");	debug(root);return;
	splay(get_k(root,p+len+2),root);
//printf("first:\n");
//	debug(root);
//return ;
	ch[ch[root][1]][0]=0; 
	pushup(ch[root][1]);
	pushup(root);
}

void print_ans(int x)
{
	if(ch[x][0])
		print_ans(ch[x][0]);
	if(key[x]!='\n');
		printf("%c",key[x]);
	if(ch[x][1])
		print_ans(ch[x][1]);	
}

void PRINT(int p,int len)
{
//	debug(root);return ;
	splay(get_k(root,p+1),0);
	splay(get_k(root,p+len+2),root);
	if(flag)
		printf("\n");
	else
		flag=true;
	print_ans(key_val);
}

void ri(int len)
{
    int i=0;  
	while(i<len)  
    {  
    	scanf("%c",&ins[i+1]);  
    	if(ins[i+1]!='\n') 
			++i;
    }  
}

int main()
{
//	freopen("LGP4008.in","r",stdin);
//	freopen("LGP4008.out","w",stdout);
	
	scanf("%d",&T);
	init();

	int len,p=0;
	while(T--)
	{
//		printf("%d\n",T);
		scanf("%s",opt);
		if(opt[0]=='P')
			--p;
		if(opt[0]=='N')
			++p;
		if(opt[0]=='M')
		{
			scanf("%d",&p);
	//		return 0;
		}
		if(opt[0]=='I')
		{
			scanf("%d",&len);
			ri(len);
//			printf("ins:");
////			for(int i=1;i<=len;++i)
//				printf("%c",ins[i]);
//			printf("\n");
			INSERT(p,len);//	return 0;
//			printf("debug: %d\n",T);debug(root);
		}
		if(opt[0]=='D')
		{
			scanf("%d",&len);
			DELETE(p,len);
//			printf("debug: %d\n",T);debug(root);
		}
		if(opt[0]=='G')
		{
			scanf("%d",&len);
			PRINT(p,len);
		}
//		printf("debug: %d\n",T);debug(root);
/*		if(T==6)
		{
			for(int i=0;i<strlen(opt);++i)
				printf("%c",opt[i]);
			printf(" %d %d\n",p,len);
			return 0;
		}*/
/*	printf("debug: %d\n",T);debug(root);
		if(T==13)
		{
			printf("again:\n");debug(root);
			scanf("%s",opt);scanf("%d",&len);
			DELETE(p,len);
			return 0;
		}*/
	}
	
	return 0;
}
