#include<bits/stdc++.h>
using namespace std;

const int N=1200010;
int mask,qs;
char s[N*3];

void readin()
{
	int x=mask;
	scanf("%s",s);int len=strlen(s);
	for(int i=0;i<len;++i)
	{
		x=(x*131+i)%len;
		char t=s[i];
		s[i]=s[x];s[x]=t;
	}
}

struct LCT
{
	int top;
	int fa[N],ch[N][2],w[N],tar[N],q[N];
	bool rev[N];
	
	void add(int x,int v)
	{
		if(x)
		{
			w[x]+=v;
			tar[x]+=v;
		}
	}
	
	void pushdown(int x)
	{
		int l=ch[x][0],r=ch[x][1];
		if(tar[x])
		{
			add(l,tar[x]);add(r,tar[x]);
			tar[x]=0;
		}
	}
	
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],l,r;
		l=(ch[y][1]==x);r=l^1;
		if(!isroot(y))
			ch[z][ch[z][1]==y]=x;
		fa[ch[x][r]]=y;fa[y]=x;fa[x]=z;
		ch[y][l]=ch[x][r];ch[x][r]=y;
	}
	
	void splay(int x)
	{
		top=0;q[++top]=x;
		for(int i=x;!isroot(i);i=fa[i])
			q[++top]=fa[i];
		for(int i=top;i;--i)
			pushdown(q[i]);
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y))
			{
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
	}
	
	void access(int x)
	{
		int t=0;
		while(x)
		{
			splay(x);
			ch[x][1]=t;
			t=x;x=fa[x];
		}
	}
	
	void link(int x,int f)
	{
		fa[x]=f;
		access(f);splay(f);
		add(f,w[x]);
	}
	
	void cut(int x)
	{
		access(x);splay(x);
		add(ch[x][0],-w[x]);
		fa[ch[x][0]]=0;ch[x][0]=0;
	}
};
LCT tr;

struct SAM
{
	int cnt,las;
	int fa[N],ch[N][26],mx[N];

	SAM(){
		las=++cnt;
	}
	
	void extend(int c)
	{
		int p=las,np=las=++cnt;
		tr.w[np]=1;mx[np]=mx[p]+1;
		while(p && !ch[p][c])
			ch[p][c]=np,p=fa[p];
		if(!p)
			fa[np]=1,tr.link(np,1);
		else
		{
			int q=ch[p][c];
			if(mx[p]+1==mx[q])
				fa[np]=q,tr.link(np,q);
			else
			{
				int nq=++cnt;mx[nq]=mx[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];
				tr.link(nq,fa[q]);
				fa[np]=fa[q]=nq;
				tr.cut(q);tr.link(q,nq);tr.link(np,nq);
				while(ch[p][c]==q && p)
					ch[p][c]=nq,p=fa[p];
			}
		}
	}
	
	void build()
	{
		scanf("%s",s);
		int len=strlen(s);
		for(int i=0;i<len;++i)
			extend(s[i]-'A');
	}
	
	void add()
	{
		readin();
		int len=strlen(s);
		for(int i=0;i<len;++i)
			extend(s[i]-'A');
	}
	
	int query()
	{
		readin();
		int p=1,len=strlen(s);
		for(int i=0;i<len;++i)
			if(!(p=ch[p][s[i]-'A']))
				return 0;
		tr.splay(p);
		return tr.w[p];
	}
};
SAM sam;

int main()
{
	freopen("BZOJ2555.in","r",stdin);
	freopen("BZOJ2555.out","w",stdout);
	
	scanf("%d",&qs);sam.build();
	while(qs--)
	{
		scanf("%s",s);
		if(s[0]=='A')
			sam.add();
		else
		{
			int ans=sam.query();
			printf("%d\n",ans);
			mask^=ans;
		}
	}
	
	return 0;
}
