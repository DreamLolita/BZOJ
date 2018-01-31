#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 140142
#define seed 131
#define which(x)	(ch[fa[x]][1]==x)
using namespace std;
typedef unsigned long long ll;
char str[N],op[10],val[10];
int fa[N],ch[N][2],size[N],n,root,tot;
ll hash[N],pow[N];
char s[N];

void Pushup(int x)
{
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	hash[x]=hash[ch[x][0]]+pow[size[ch[x][0]]]*s[x]+pow[size[ch[x][0]]+1]*hash[ch[x][1]];
}

void Rotate(int x)
{
	int f=fa[x];
	bool k=which(x);
	ch[f][k]=ch[x][!k];
	ch[x][!k]=f;
	ch[fa[f]][which(f)]=x;
	fa[ch[f][k]]=f;
	fa[x]=fa[f];
	fa[f]=x;
	size[x]=size[f],hash[x]=hash[f];
	Pushup(f);
}

void Splay(int x,int g)
{
	while(fa[x]!=g)
	{
		int f=fa[x];
		if(fa[f]==g)
		{
			Rotate(x);
			break;
		}
		if(which(x)^which(f))
			Rotate(x);
		else
			Rotate(f);
		Rotate(x);
	}
	if(!g)	root=x;
}

int Rank(int x,int k)
{
	if(k<=size[ch[x][0]])
		return Rank(ch[x][0],k);
	else if(k==size[ch[x][0]]+1)
		return x;
	else
		return Rank(ch[x][1],k-size[ch[x][0]]-1);
}

int Build(int l,int r,int f)
{
	if(l>r)	return 0;
	int x=++tot,mid=l+r>>1;
	fa[x]=f,s[x]=str[mid];
	ch[x][0]=Build(l,mid-1,x);
	ch[x][1]=Build(mid+1,r,x);
	Pushup(x);
	return x;
}

void Insert(int k,char val)
{
	int x=Rank(root,k),y=Rank(root,k+1);
	Splay(x,0),Splay(y,x);
	s[++tot]=val;
	fa[tot]=y,ch[y][0]=tot;
	Pushup(tot);
	Pushup(y);
	Pushup(x);
}

void Change(int k,char val)
{
	int x=Rank(root,k);
	Splay(x,0);
	s[x]=val;
	Pushup(x);
}

int LCQ(int kx,int ky)
{
	int l=0,r=n,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(ky+mid>n+2)
		{
			r=mid-1;
			continue;
		}
		int x=Rank(root,kx-1),y=Rank(root,kx+mid);
		Splay(x,0),Splay(y,x);
		ll temp=hash[ch[y][0]];
		x=Rank(root,ky-1),y=Rank(root,ky+mid);
		Splay(x,0),Splay(y,x);
		if(temp==hash[ch[y][0]])
			l=mid+1;
		else 
			r=mid-1;
	}
	return r;
}

int main()
{
//	freopen("BZOJ1014.in","r",stdin);
//	freopen("BZOJ1014.out","w",stdout);
	
	int m,i,j,k,x,y;
	scanf("%s%d",str+1,&m);
	n=strlen(str+1);
	for(pow[0]=1,i=1;i<N;i++)
		pow[i]=pow[i-1]*seed;
	root=Build(0,n+1,0);
	for(i=1;i<=m;i++)
	{
		scanf("%s",op);
		if(op[0]=='I')
		{
			scanf("%d%s",&x,val);
			Insert(x+1,val[0]);
			n++;
		}
		else if(op[0]=='R')
		{
			scanf("%d%s",&x,val);
			Change(x+1,val[0]);
		}
		else
		{
			scanf("%d%d",&x,&y);
			if(x>y)	swap(x,y);
			if(x!=y)
				printf("%d\n",LCQ(x+1,y+1));
			else
				printf("%d\n",n-x+1);
		}
	}
	return 0;
}

