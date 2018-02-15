#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
//#include<ctime>
#define N 200010
using namespace std;
struct ppp
{
	long long x,y;
	int num,k;
}b[N];
bool cmp(ppp x,ppp y)
{
	if(x.x!=y.x) return x.x<y.x;
	return x.y<y.y;
}
long long ax[N],ay[N];
map<long long,int>px,py;
int ans[N];
int nx,ny;
int l[N<<2],r[N<<2],rt[N<<2];
int ch[N*20][2],siz[N*20],a[N*20],fa[N*20],ti[N*20],cnt;
inline void pup(int x){siz[x]=siz[ch[x][0]]+ti[x]+siz[ch[x][1]];}
void rotate(int x,int &k)
{
	int y=fa[x],z=fa[y];
	int l=0,r;
	if(ch[y][1]==x) l=1;r=l^1;
	if(y==k) k=x;
	else
	{
		if(ch[z][0]==y) ch[z][0]=x;
		else ch[z][1]=x;
	}
	fa[ch[x][r]]=y;
	fa[y]=x;
	fa[x]=z;
	ch[y][l]=ch[x][r];
	ch[x][r]=y;
	pup(y);//pup(x);
}
void splay(int x,int &k)
{
	while(x!=k)
	{
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if(ch[z][0]==y^ch[y][0]==x) rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void add(int &k,int x)
{
	if(!k)
	{
		cnt++;k=cnt;
		siz[cnt]=ti[cnt]=1;
		a[cnt]=x;
		return;
	}
	int z,p=k;
    while(p)
    {
        z=p;
        siz[z]++;
        if(x==a[z])
        {
            ti[z]++;
            return;
        }
        if(x>a[z])
        p=ch[z][1];
        else p=ch[z][0];
    }
    ti[++cnt]=1;
    siz[cnt]=1;
    a[cnt]=x;
    fa[cnt]=z;
    if(x>a[z])
    ch[z][1]=cnt;
    else ch[z][0]=cnt;
    splay(cnt,k);
}
int numgetrank(int k,int x,bool f)
{
	if(!k) return 0;
	if(a[k]==x) 
	{
		if(!f) return siz[ch[k][0]]+ti[k];
		return ti[k];
	}
	if(x<a[k]) return numgetrank(ch[k][0],x,f);
	else
	{
		if(!f) return numgetrank(ch[k][1],x,f)+siz[ch[k][0]]+ti[k];
		return numgetrank(ch[k][1],x,f);
	}
}
inline void build(int now,int ll,int rr)
{
	l[now]=ll;r[now]=rr;
	if(ll==rr) return;
	int mid=(ll+rr)>>1;
	build(now<<1,ll,mid);
	build(now<<1|1,mid+1,rr); 
}
inline int check(int now,int v,int k,bool f)
{
	if(l[now]==r[now]) return l[now];
	int t=numgetrank(rt[now<<1],v,f);
	if(k<=t) return check(now<<1,v,k,f);
	else return check(now<<1|1,v,k-t,f);
}
inline void change(int now,int x,int v)
{
	add(rt[now],v);
	if(l[now]==r[now]) return;
	int mid=(l[now]+r[now])>>1;
	if(x<=mid) change(now<<1,x,v);
	else change(now<<1|1,x,v);
}
const int ___=1<<15;
char ZZ[___|1],*_=ZZ,*Z=ZZ,Z_[___],_Z;
#define getc() (_==Z&&(Z=(_=ZZ)+fread(ZZ,1,___,stdin),_==Z)?0:*_++)
inline int read()
{
	int x=0,f=1;
	char c=getc();
	for(;c<48||c>57;c=getc())if(c==45)f=-1;
	for(;c>=48&&c<=57;)x=x*10+c-48,c=getc();
	return x*f;
}
inline long long readll()
{
	long long x=0,f=1;
	char c=getc();
	for(;c<48||c>57;c=getc())if(c==45)f=-1;
	for(;c>=48&&c<=57;)x=x*10+c-48,c=getc();
	return x*f;
}
long long X1,X2,Y1,Y2;
int main()
{
	int n;
	int tot=0,st=clock();
	n=read();
	long long x,y;
	X1=readll();Y1=readll();X2=readll();Y2=readll();
	bool fl=false; 
	if(X1*Y2==Y1*X2)
	{
		fl=true;
		X2=-Y1;Y2=X1;
	}
	long long tmp=1;
	if(X1*Y2-Y1*X2<0) tmp=-1;
	int i,j;
	for(i=1;i<=n;i++)
	{
		x=readll();y=readll();
		b[i].x=tmp*(x*Y2-y*X2);
		b[i].y=tmp*(y*X1-x*Y1);
		b[i].num=i;
		ax[i]=b[i].x;
		ay[i]=b[i].y;
	}
	for(i=1;i<=n;i++)
	b[i].k=read();
	sort(ax+1,ax+n+1);
	ax[0]=707185547;
	for(i=1;i<=n;i++)
	if(ax[i]!=ax[i-1])
	{
		nx++;
		px[ax[i]]=nx;
	}
	sort(ay+1,ay+n+1);
	ay[0]=707185547;
	for(i=1;i<=n;i++)
	if(ay[i]!=ay[i-1])
	{
		ny++;
		py[ay[i]]=ny;
	}
	sort(ax+1,ax+n+1);
    sort(ay+1,ay+n+1);
    int sx=unique(ax+1,ax+n+1)-ax;
    int sy=unique(ay+1,ay+n+1)-ay;
    for (int i = 1; i <= n; i ++)
    {
        int u=lower_bound(ax+1,ax+sx,b[i].x)-ax;
        int v=lower_bound(ay+1,ay+sy,b[i].y)-ay;
        b[i].x=u,b[i].y=v;
    }
	sort(b+1,b+n+1,cmp);
	build(1,1,n);
	for(i=1;i<=n;i++)
	{
		tmp=numgetrank(rt[1],b[i].y,fl);
		if(tmp<b[i].k) ans[b[i].num]=b[i].num;
		else ans[b[i].num]=min(check(1,b[i].y,b[i].k,fl),b[i].num);
	//	st=clock();
		change(1,ans[b[i].num],b[i].y);
	//	tot+=clock()-st;
	}
	for(i=1;i<n;i++)
	printf("%d ",ans[i]);
	printf("%d",ans[n]);
//	cout<<tot;
}
