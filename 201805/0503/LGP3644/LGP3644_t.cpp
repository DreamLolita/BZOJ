#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9+10;
const int N=1e5+10;
const int M=5e5+10;
int n,K,tot;
LL ans;

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)){if(c=='A')return -1; if(c=='B')return -2; c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Splay
{
	int sz,root,tpos,ch[M][2];
	int key[M],fa[M],siz[M],cnt[M];
	LL sl[M],sr[M];

	void pushup(int x)
    {
        sl[x]=sl[ch[x][0]]+sl[ch[x][1]]+(LL)cnt[x]*(INF+key[x]);
        sr[x]=sr[ch[x][0]]+sr[ch[x][1]]+(LL)cnt[x]*(INF-key[x]);
        siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];
    }

    Splay()
	{
		sz=2;root=1;ch[1][0]=2;fa[2]=1;
		key[2]=-INF,key[1]=INF;cnt[1]=cnt[2]=1;
		pushup(2);pushup(1);
	}

	void rotate(int x,int goal)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[y]=x;fa[x]=z;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x,int goal)
	{
		while(fa[x]!=goal)
		{
			int y=fa[x],z=fa[y];
			if(fa[y]!=goal)
			{
				if(ch[y][1]==x^ch[z][1]==y)
					rotate(x,goal);
				else
					rotate(y,goal);
			}
			rotate(x,goal);
		}
		if(!goal)
			root=x;
	}
	
	int find_val(int x,int v)
    {
        if(key[x]==v)return x;
        if(v<key[x])return find_val(ch[x][0],v);
        return find_val(ch[x][1],v);
    }
    
    int find_kth(int x,int k)
    {
        if(k>siz[ch[x][0]]&&siz[ch[x][0]]+cnt[x]>=k)
            return x;
        if(siz[ch[x][0]]>=k)
            return find_kth(ch[x][0],k);
        return find_kth(ch[x][1],k-siz[ch[x][0]]-cnt[x]);
    }
    
    void insert(int v)
    {
        int x=root;
        while(1)
        {
            if(key[x]==v)
                {cnt[x]++;pushup(x);break;}
            if(v<key[x])
            {
                if(!ch[x][0])
                {
                    ch[x][0]=++sz;fa[sz]=x;
                    cnt[sz]=siz[sz]=1;key[sz]=v;
                    pushup(sz);break;
                }
                x=ch[x][0];
            }
            else
            {
                if(!ch[x][1])
                {
                    ch[x][1]=++sz;fa[sz]=x;
                    cnt[sz]=siz[sz]=1;key[sz]=v;
                    pushup(sz);break;  
                }
                x=ch[x][1];
            }
        }
        splay(x,0);
    }
    
    void dele(int v)
    {
        int x=find_val(root,v);
        cnt[x]--;splay(x,0);
    }
    
    LL query()
    {
        int x=find_kth(root,siz[root]/2);
        splay(x,0);
        return sr[ch[x][0]]-(LL)(INF-key[x])*siz[ch[x][0]]
        +sl[ch[x][1]]-(LL)(key[x]+INF)*siz[ch[x][1]]-
        (key[x]+INF)-(INF-key[x]);
    }
    
    void debug(int x)
    {
    	if(ch[x][0])
    		debug(ch[x][0]);
    	printf("%d %d %d %d %lld %lld %d %d\n",x,siz[x],key[x],cnt[x],sl[x],sr[x],ch[x][0],ch[x][1]);
		if(ch[x][1])	
			debug(ch[x][1]);
	}
};
Splay tr1,tr2;

struct Tnode
{
	int S,T,md;
};
Tnode a[N];

bool cmp(Tnode A,Tnode B)
{
	return A.md<B.md;
}

void init()
{
	K=read();n=read();tot=n;
	for(int i=1,j=1;i<=n;++i,++j)
	{
		int p1,p2;
		p1=read();a[j].S=read();
		p2=read();a[j].T=read();
		a[j].md=(a[j].S+a[j].T);
		if(p1==p2)
			ans+=abs(a[j].S-a[j].T),--j,--tot;
	}
	n=tot;ans+=n;
	sort(a+1,a+n+1,cmp);
}

void solve()
{
	for(int i=1;i<=n;++i)
		tr1.insert(a[i].S),tr1.insert(a[i].T);
	LL tmpans=tr1.query();
	
	if(K==1)
	{
		ans+=tmpans;
		printf("%lld\n",ans);
		return;
	}
	
//printf("%d %d\n",tr1.siz[tr1.root],tr2.siz[tr2.root]);
//puts("debug:");tr1.debug(tr1.root);
	for(int i=1;i<n;++i)
	{
		tr1.dele(a[i].S);tr1.dele(a[i].T);
//puts("debug:");tr1.debug(tr1.root);
		tr2.insert(a[i].S);tr2.insert(a[i].T);
//printf("%lld %d %d %lld %lld\n",tmpans,tr1.siz[tr1.root],tr2.siz[tr2.root],tr1.query(),tr2.query());
		tmpans=min(tmpans,(LL)tr1.query()+tr2.query());
	}
	ans+=tmpans;
	printf("%lld\n",ans);
}

int main()
{
	freopen("LGP3644.in","r",stdin);
	freopen("LGP3644.out","w",stdout);

	init();
	solve();

	return 0;
}
