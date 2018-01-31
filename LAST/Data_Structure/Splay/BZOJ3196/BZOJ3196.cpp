#include<bits/stdc++.h>
using namespace std;

const int INF=1e9+10;
const int MAXN=2e6+5;
int n,m,tot=2;
int root[MAXN],a[MAXN];

struct seg_tree
{
	int l,r,rt;
	seg_tree *lc,*rc;
	seg_tree():rt(0){}
};
seg_tree *RT=new seg_tree();

struct Tnode
{
	int ch[2],fa;
	int siz,num,val;
};

struct splay_tree
{
	Tnode t[MAXN];
	void pushup(int x)
	{
		t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+t[x].num;
	}
	
	void rotate(int x,int y)
	{
		int kind=x==t[y].ch[1];
		int s=t[x].ch[kind^1],z=t[y].fa;
		if(t[z].ch[0]==y)
			t[z].ch[0]=x;
		if(t[z].ch[1]==y)
			t[z].ch[1]=x;
		if(s)
			t[s].fa=y;
		t[y].ch[kind]=s;
		t[x].fa=z;t[x].ch[kind^1]=y;t[y].fa=x;
		pushup(y);
	}
	
	void splay(int rt,int x,int goal)
	{
		while(t[x].fa!=goal)
		{
			int y=t[x].fa,z=t[y].fa;
			if(z==goal)
				rotate(x,y);
			else
			if(x==t[y].ch[0]^y==t[z].ch[0])
				rotate(x,y),rotate(x,z);
			else
				rotate(y,z),rotate(x,y);
		}
		pushup(x);	
		if(!goal)
			root[rt]=x;
	}
	
	void ins(int rt,int val)
	{
		int x=root[rt];
		if(!x)
		{
			t[++tot].val=val;
			t[tot].num=t[tot].siz=1;
			root[rt]=tot;
			return;
		}
		while(t[x].val!=val)
		{
			if(t[x].val>val)
			{
				if(t[x].ch[0])
					x=t[x].ch[0];
				else
					break;
			}
			else
			{
				if(t[x].ch[1])
					x=t[x].ch[1];
				else
					break;
			}
		}
		if(t[x].val==val)
		{
			t[x].num++;
			splay(rt,x,0);
			return;
		}
		t[++tot].val=val;t[tot].fa=x;t[tot].num=t[tot].siz=1;
		if(val<t[x].val)
			t[x].ch[0]=tot;
		else
			t[x].ch[1]=tot;
		splay(rt,tot,0);
	}
	
	int get_k(int rt,int k)
	{
		int x=root[rt];
		while(t[x].val!=k)
		{
			if(t[x].val>k)
			{
				if(t[x].ch[0])
					x=t[x].ch[0];
				else
					break;
			}
			else
			{
				if(t[x].ch[1])
					x=t[x].ch[1];
				else
					break;
			}
		}
		splay(rt,x,0);
		return x;
	}
	
	int qrank(int rt,int k)
	{
		int x=get_k(rt,k);
		if(t[x].val>=k)
			return t[t[x].ch[0]].siz;
		else
			return t[t[x].ch[0]].siz+t[x].num;
	}
	
	void del(int rt,int val)
	{
		int x=root[rt];
		while(t[x].val!=val)
		{
			if(t[x].val>val)
			{
				if(t[x].ch[0])
					x=t[x].ch[0];
				else
					break;
			}
			else
			{
				if(t[x].ch[1])
					x=t[x].ch[1];
				else
					break;
			}
		}
		splay(rt,x,0);
		if(t[x].num>1)
		{
			--t[x].num;
			return;
		}
		if(!t[x].ch[0])
		{
			root[rt]=t[x].ch[1];t[t[x].ch[1]].fa=0;
			return;
		}
		if(!t[x].ch[1])
		{
			root[rt]=t[x].ch[0];t[t[x].ch[0]].fa=0;
			return;
		}
		
		int y=t[x].ch[0];
		while(t[y].ch[1])
			y=t[y].ch[1];
		splay(rt,y,x);
		t[y].ch[1]=t[x].ch[1];t[y].fa=0;t[t[y].ch[1]].fa=y;
		pushup(y);
		root[rt]=y;
	}
	
	int prec(int rt,int val)
	{
		int x=root[rt];
		while(t[x].val!=val)
		{
			if(t[x].val>val)
			{
				if(t[x].ch[0])
					x=t[x].ch[0];
				else
					break;
			}
			else
			{
				if(t[x].ch[1])
					x=t[x].ch[1];
				else
					break;
			}
		}
		if(t[x].val==val)
		{
			splay(rt,x,0);
			if(!t[x].ch[0])
				return 1;
			x=t[x].ch[0];
			while(t[x].ch[1])
				x=t[x].ch[1];
			return x;
		}
		while(t[x].fa && t[x].val>val)
			x=t[x].fa;
		if(t[x].val<val)
			return x;
		return 1;
	}
	
	int succ(int rt,int val)
	{
		int x=root[rt];
		while(t[x].val!=val)
		{
			if(t[x].val>val)
			{
				if(t[x].ch[0])
					x=t[x].ch[0];
				else
					break;
			}
			else
			{
				if(t[x].ch[1])
					x=t[x].ch[1];
				else
					break;
			}
		}
		if(t[x].val==val)
		{
			splay(rt,x,0);
			if(!t[x].ch[1])
				return 2;
			x=t[x].ch[1];
			while(t[x].ch[0])
				x=t[x].ch[0];
			return x;
		}
		while(t[x].fa && t[x].val<val)
			x=t[x].fa;
		if(t[x].val>val)
			return x;
		return 2;
	}
}s;

void build(seg_tree *p,int rt,int l,int r)
{  
    p->rt=rt; p->l=l; p->r=r;  
    for(int i=l;i<r;++i) 
		s.ins(rt,a[i]);  
    if(l+1==r)
	{
		p->lc=p->rc=NULL;
		return;
	}  
    else 
	if (l+1<r)
	{  
        int mid=(l+r)>>1;  
        p->lc=new seg_tree();  p->rc=new seg_tree();  
        if (l<mid)
			build(p->lc,rt<<1,l,mid);  
        else 
			p->lc=NULL;  
        if (mid<r) 
			build(p->rc,rt<<1|1,mid,r);  
        else 
			p->rc=NULL;  
	}
}
    
int query(seg_tree *p,int l,int r,int k)
{  
    if (l<=p->l&&p->r<=r) 
	 	return s.qrank(p->rt,k);  
    int mid=(p->l+p->r)>>1,ret=0;  
    if(l<mid) 
		ret=query(p->lc,l,r,k);  
    if(r>mid)
		ret+=query(p->rc,l,r,k);  
    return ret;  
}  
      
void change(seg_tree *p,int pos,int val)
{  
    s.del(p->rt,a[pos]); 
	s.ins(p->rt,val);  
    if (p->l+1==p->r) 
		return;  
    int mid=(p->l+p->r)>>1;  
    if (pos<mid) 
		change(p->lc,pos,val);  
    else 
		change(p->rc,pos,val);  
}  
      
int qpre(seg_tree *p,int l,int r,int val)
{  
    if (l<=p->l&&p->r<=r)
	{  
        int x=s.prec(p->rt,val);  
        if(s.t[x].val<val) 
			return s.t[x].val;  
        return -1;  
    }  
    int mid=(p->l+p->r)>>1,ret=-1;  
    if (l<mid) 
		ret=max(ret,qpre(p->lc,l,r,val));  
    if (mid<r) 
		ret=max(ret,qpre(p->rc,l,r,val));  
    return ret;  
}  
      
int qsuc(seg_tree *p,int l,int r,int val)
{  
    if (l<=p->l&&p->r<=r)
	{  
        int x=s.succ(p->rt,val);  
        if(s.t[x].val>val) 
			return s.t[x].val;  
        return INF;  
    }  
    int mid=(p->l+p->r)>>1,ret=1e8;  
    if (l<mid) 
		ret=min(ret,qsuc(p->lc,l,r,val));  
    if (mid<r) 
		ret=min(ret,qsuc(p->rc,l,r,val));  
	return ret;  
}  

int main()
{  
//	freopen("BZOJ3196.in","r",stdin);
//	freopen("BZOJ3196.out","w",stdout);

    scanf("%d%d",&n,&m);  
    for (int i=1;i<=n;++i) 
		scanf("%d",&a[i]);  
    s.t[1].val=-1; s.t[2].val=INF;  
    build(RT,1,1,n+1);  
    
    for (int i=1;i<=m;++i)
	{  
        int opt,x,y,z;  
        scanf("%d%d%d",&opt,&x,&y);  
        if(opt!=3) scanf("%d",&z);  
        if(opt==1) 
			printf("%d\n",query(RT,x,y+1,z)+1);  
        else 
		if(opt==2)
		{  
            int L=0,R=1e8,ans=0;  
            while (L<=R)
			{  
                int mid=(L+R)>>1;  
                if(query(RT,x,y+1,mid)<z)ans=mid,L=mid+1;  
                    else R=mid-1;  
            }printf("%d\n",ans);  
        }
		else 
		if(opt==3) 
			change(RT,x,y),a[x]=y;  
        else 
		if(opt==4) 
			printf("%d\n",qpre(RT,x,y+1,z));  
        else 
		if(opt==5) 
			printf("%d\n",qsuc(RT,x,y+1,z));  
    }  
    return 0;
} 
