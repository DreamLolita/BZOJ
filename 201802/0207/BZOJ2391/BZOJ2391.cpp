#include<bits/stdc++.h>
using namespace std;

const int N=2020;
const int INF=12345;

int n,m,q,tot;
int f[N][N],rid[N];
int root,ch[N][2],pool;
int sum[N],key[N],fa[N],que[N];

struct Tpoint
{
    int x,y,v,id;
    Tpoint operator - (Tpoint b)
    {
        return (Tpoint){x-b.x,y-b.y,0,0};
    }
};
Tpoint p[N<<1];

int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || '9'<ch){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9')x=x*10+(ch^48),ch=getchar();
    return x*f;
}

int sqr(int x){return x*x;}
int cross(Tpoint a,Tpoint b){return a.x*b.y-a.y*b.x;}
int dist(Tpoint a,Tpoint b){return sqr(a.x-b.x)+sqr(a.y-b.y);} 

bool cmps(Tpoint a,Tpoint b)
{
    if(cross(b-p[0],a-p[0])==0)
        return dist(p[0],a)<dist(p[0],b);
    return cross(b-a,p[0]-a)>0;
}

void init()
{
    root=0;
    memset(ch,0,sizeof(ch));
    memset(fa,0,sizeof(fa));
}

void update(int x)
{
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+p[x].v;
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int l=(ch[y][1]==x);
    if(z){ch[z][ch[z][1]==y]=x;}
    fa[x]=z;fa[y]=x;fa[ch[x][l^1]]=y;
    ch[y][l]=ch[x][l^1],ch[x][l^1]=y;
    update(y);update(x);
}

int Insert(int base,int now)
{
    sum[now]=p[now].v;
    ch[now][0]=ch[now][1]=0;
    key[now]=rand();
    int ret=0;
    if(!root)
    {
        root=now;
        return ret;
    }

    int pos=root,tmp=0,son=0;
    while(pos)
    {
        tmp=pos;
        sum[pos]+=p[now].v;
        if(cross(p[now]-p[base],p[pos]-p[base])>0)
            pos=ch[pos][son=0];
        else
        {
            ret+=sum[ch[pos][0]]+p[pos].v;
            pos=ch[pos][son=1];
        }
    }

    fa[now]=tmp;
    ch[tmp][son]=now;

    while(key[now]<key[fa[now]])
        rotate(now);
    if(!fa[now])
        root=now;
    return ret;
}  

int main()
{
	freopen("BZOJ2391.in","r",stdin);
	freopen("BZOJ2391.out","w",stdout);
	
	n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        ++tot;
		p[tot].x=read();p[tot].y=read();
        p[tot].id=tot;
    }
    for(int i=1;i<=m;i++)
    {
    	++tot;
        p[tot].x=read();p[tot].y=read();
        p[tot].v=read();p[tot].id=tot;
    }

    p[0].x=p[0].y=-INF;
    sort(p+1,p+tot+1,cmps);
    for(int i=1;i<=tot;i++)
        rid[p[i].id]=i;
    for(int i=1;i<tot;i++)
    {
        init();
        for(int j=i+1;j<=tot;j++)
            f[i][j]=f[j][i]=Insert(i,j);
    }

    q=read();
    while(q--)
    {
        int cnt=read();
        for(int i=1;i<=cnt;i++)
            que[i]=rid[read()];
        que[cnt+1]=que[1];

        int ans=0;
        for(int i=1;i<=cnt;i++)
            if(cross(p[que[i+1]]-p[0],p[que[i]]-p[0])>0)
                ans+=f[que[i]][que[i+1]];
            else
                ans-=f[que[i]][que[i+1]];
        printf("%d\n",abs(ans));
    }
	
	return 0;
}
