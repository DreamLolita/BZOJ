#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int INF=1e9+10;
const int MAXN=2e4+10;
const int MAXQ=1e5+10;

int n,m,qs,tot,cnt;
int head[MAXQ],ans[MAXQ],dis[MAXQ<<1];
int ids[MAXQ];
//int q[MAXQ];

struct Tway
{
	int pnt,nex,w;
};
Tway e[MAXQ<<2];

struct Tpoint
{
	int sx,sy,dx,dy,id;
};
Tpoint a[MAXQ],b[MAXQ];

struct QUQ
{
	int d,ids;

	QUQ(){}
	QUQ(int dd,int idss)
	{
		d=dd;ids=idss;
	}
};

bool operator < (const QUQ &A,const QUQ &B)
{
	return A.d>B.d;
}

inline int read()
{  
    int x=0; char ch=getchar();  
    while (ch<'0' || ch>'9') ch=getchar();  
    while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }  
    return x;  
}  

inline int getp(int x,int y)
{
	return (x-1)*m+y;
}

inline void add(int u,int v,int w)
{
	++tot;
	e[tot].pnt=v;e[tot].w=w;
	e[tot].nex=head[u];head[u]=tot;
}

inline void init()
{
	n=read();m=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<m;++j)
		{
			int x,u,v;
			x=read();
			u=getp(i,j);v=getp(i,j+1);
			add(u,v,x);add(v,u,x);
//			printf("u:%d v:%d\n",u,v);	
		}
	}
	
	for(int i=1;i<n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			int x,u,v;
			x=read();
			u=getp(i,j);v=getp(i+1,j);
			add(u,v,x);add(v,u,x);
//			printf("u:%d v:%d\n",u,v);
		}
	}
	
	qs=read();
	for(int i=1;i<=qs;++i)
	{
		a[i].sx=read();a[i].sy=read();
		a[i].dx=read();a[i].dy=read();
//		scanf("%d%d%d%d",&a[i].sx,&a[i].sy,&a[i].dx,&a[i].dy);
		a[i].id=i;ans[i]=INF;
	}
	
/*	printf("ways:\n");
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			int t=getp(i,j);
			printf("%d:",t);
			for(int p=head[t];p;p=e[p].nex)
				printf("%d ",e[p].pnt);
			printf("\n");
		}
	printf("\n\n");*/
}


/*inline void pup(int x)
{
	int y=q[x],t=dis[y];
	for(;x>1 && t<dis[q[x>>1]];x>>=1)
	{
		q[x]=q[x>>1];
		ids[q[x]]=x;
	}
	q[x]=y;ids[y]=x;
}

inline void pud(int x)
{
	int y=x<<1,z=q[x],t=dis[z];  
    if (y<cnt && dis[q[y|1]]<dis[q[y]]) 
		y|=1;  
    while (y<=cnt && dis[q[y]]<t)
	{  
        q[x]=q[y]; ids[q[x]]=x;  
        x=y; y<<=1; 
		if (y<cnt && dis[q[y|1]]<dis[q[y]]) 
			y|=1;  
    }  
    q[x]=z;ids[z]=x;  
}

inline void dij(int sta,int x,int xx,int y,int yy)
{
	cnt=1;
	q[1]=sta; ids[sta]=1; dis[sta]=0;  
    for(int i=x;i<=xx;++i)  
        for(int j=y;j<=yy;++j)
		{  
            int t=getp(i,j);  
            if (t!=sta)
			{ 
				dis[t]=INF; 
				q[++cnt]=t; 
				ids[t]=cnt;
			}  
        }  
    while (cnt)
	{  
        int u=q[1]; q[1]=q[cnt--]; ids[q[1]]=1; pud(1);  
//		printf("u:%d\n",u);
		
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].pnt;
			int px=(v-1)/m+1,py=(v-1)%m+1;
//			printf("%d %d %d\n",px,py,i);
			if(px>=x && px<=xx && py>=y && py<=yy && dis[u]+e[i].w<dis[v])
			{
				dis[v]=dis[u]+e[i].w;
				pup(ids[v]);
			}
		}
    }  
    
   	for(int i=x;i<=xx;++i)  
        for(int j=y;j<=yy;++j)
		{  
            int x=getp(i,j);  
            printf("%d ",dis[x]);
        }  
    printf("\n");
}*/

inline void dij(int sta,int x,int xx,int y,int yy)
{   
	for(int i=x;i<=xx;++i)
		for(int j=y;j<=yy;++j)
			dis[getp(i,j)]=INF;
	dis[sta]=0;
	priority_queue<QUQ>q;
	q.push(QUQ{0,sta});
	
	while(!q.empty())
	{
		int u=q.top().ids,dp=q.top().d;
		q.pop();
		
		for(int i=head[u];i;i=e[i].nex)
		{
			int pn=e[i].pnt;
			int px=(pn-1)/m+1,py=(pn-1)%m+1;
			if(px>=x && px<=xx && py>=y && py<=yy && dis[u]+e[i].w<dis[pn])
			{
				dis[pn]=dis[u]+e[i].w;
				q.push(QUQ{dis[pn],pn});
			}
		}
	}
	
/*	for(int i=x;i<=xx;++i)  
        for(int j=y;j<=yy;++j)
		{  
            int x=getp(i,j);  
            printf("%d ",dis[x]);
        }  
    printf("\n");*/
}

inline void solve(int x,int xx,int y,int yy,int l,int r)
{
//	printf("%d %d %d %d %d %d\n",x,xx,y,yy,l,r);
	if(l>r)
		return;
	if(xx-x>yy-y)
	{
		int mid=(x+xx)>>1;
		for(int i=y;i<=yy;++i)
		{
			dij(getp(mid,i),x,xx,y,yy);
			for(int j=l;j<=r;++j)
				ans[a[j].id]=min(ans[a[j].id] , dis[getp(a[j].sx,a[j].sy)] + dis[getp(a[j].dx,a[j].dy)]);
		}
		
		int j=l-1,k=r+1;
		for(int i=l;i<=r;++i)
			if(a[i].sx<mid && a[i].dx<mid)
				b[++j]=a[i];
			else
			if(a[i].sx>mid && a[i].dx>mid)
				b[--k]=a[i];
				
		for(int i=l;i<=j;++i)
			a[i]=b[i];
		solve(x,mid-1,y,yy,l,j);
		
		for(int i=k;i<=r;++i)
			a[i]=b[i];
		solve(mid+1,xx,y,yy,k,r);
	}
	else
	{
		int mid=(y+yy)>>1;
		for(int i=x;i<=xx;++i)
		{
			dij(getp(i,mid),x,xx,y,yy);
			for(int j=l;j<=r;++j)
				ans[a[j].id]=min(ans[a[j].id] , dis[getp(a[j].sx,a[j].sy)] + dis[getp(a[j].dx,a[j].dy)]);
		}
		
		int j=l-1,k=r+1;
		for(int i=l;i<=r;++i)
			if(a[i].sy<mid && a[i].dy<mid)
				b[++j]=a[i];
			else
			if(a[i].sy>mid && a[i].dy>mid)
				b[--k]=a[i];
				
		for(int i=l;i<=j;++i)
			a[i]=b[i];
		solve(x,xx,y,mid-1,l,j);
		
		for(int i=k;i<=r;++i)
			a[i]=b[i];
		solve(x,xx,mid+1,yy,k,r);
	}
}

inline void print_ans()
{
	for(int i=1;i<=qs;++i)
		printf("%d\n",ans[i]);
}

int main()
{
	freopen("BZOJ4456.in","r",stdin);
	freopen("BZOJ4456.out","w",stdout);
	
	init();
	solve(1,n,1,m,1,qs);
	print_ans();
	
	return 0;
}
