#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,m;

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

void write(LL x)
{
    if(x<0) x=-x,putchar('-');
    if(x>9) write(x/10);
    putchar((x%10)^48);
}

struct LCT
{
    int rev[N],siz1[N],siz2[N],fa[N],ch[N][2];
    stack<int>q;
    
    void init()
    {
    	for(int i=1;i<=n;++i)
    		siz1[i]=siz2[i]=1;
	}

    bool isroot(int x)
    {
        return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x; 
    }

    void pushup(int x)
    {
        int ls=ch[x][0],rs=ch[x][1];
        siz1[x]=siz1[ls]+siz1[rs]+siz2[x];
    }

    void pushdown(int x)
    {
        int ls=ch[x][0],rs=ch[x][1];
        if(rev[x])
        {
            rev[x]^=1;rev[ls]^=1;rev[rs]^=1;
            swap(ch[x][0],ch[x][1]);
        }
    }

    void rotate(int &x)
    {
        int y=fa[x],z=fa[y],kind=ch[y][1]==x;
        if(!isroot(y))
            ch[z][ch[z][1]==y]=x;
        fa[x]=z;fa[y]=x;fa[ch[x][!kind]]=y;
        ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
        pushup(y);pushup(x);
    }

    void splay(int &x)
    {
        q.push(x);
        for(int i=x;!isroot(i);i=fa[i])
            q.push(fa[i]);
        while(!q.empty())
            pushdown(q.top()),q.pop();
        while(!isroot(x))
        {
            int y=fa[x],z=fa[y];
            if(!isroot(y))
            {    
				if((ch[y][0]==x)^(ch[z][0]==y))
                    rotate(x);
                else
                    rotate(y);
            }
            rotate(x);
        }
    }

    void access(int x)
    {
        for(int t=0;x;t=x,x=fa[x])
        {
		    splay(x);siz2[x]+=siz1[ch[x][1]];
			ch[x][1]=t;siz2[x]-=siz1[t];pushup(x);
		}
	}

    void makeroot(int x)
    {
        access(x);splay(x);
        rev[x]^=1;
    }

    void link(int x,int y)
    {
        makeroot(x);makeroot(y);fa[x]=y;
        siz2[y]+=siz1[x];pushup(y);
    }

    void cut(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        fa[x]=ch[y][0]=0;
        pushup(y);
    }

    LL query(int x,int y)
    {
        makeroot(x);access(y);splay(x);
        LL ret=1ll*siz2[y]*(siz1[x]-siz2[y]);
        return ret;
    }
}tr;

int main()
{
    freopen("BZOJ4530.in","r",stdin);
    freopen("BZOJ4530.out","w",stdout);

    n=read();m=read();tr.init();
    while(m--)
    {
        char opt[2];int x,y;
        scanf("%s",opt);x=read();y=read();
        if(opt[0]=='A')
            tr.link(x,y);
        else
			write(tr.query(x,y)),puts("");
	}

    return 0;
}
