#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 70000;
const int M = 275;
const int MAXM = 550;
int n,m,ans,cnt;
int cc[N+1],cx[M+1];

struct Lump
{
    Lump *las,*nex;
    int tot;
    int v[MAXM+1];
    int cc[N+1],cx[M+1];
}xu[M+1],*s;

void init()
{
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
    	int z;
       	scanf("%d",&z);
        xu[i/M+1].tot++;
        xu[i/M+1].v[xu[i/M+1].tot]=z;
        xu[i/M+1].cc[z]++;
        xu[i/M+1].cx[z/M]++;
    }
    cnt=n/M+1;
    for(i=0;i<cnt;i++)
        xu[i].nex=xu+(i+1);
    for(i=1;i<=cnt;i++)
        xu[i].las=xu+(i-1);
    for(i=1;i<=cnt;i++)
    {
        for(j=0;j<=N;j++)
            xu[i].cc[j]+=xu[i-1].cc[j];
        for(j=0;j<=M;j++)
            xu[i].cx[j]+=xu[i-1].cx[j];
    }
}

void Change(int x,int y)
{
    Lump *now=xu;
    while(now->tot<x)
    {
        x-=now->tot;
        now=now->nex;
    }
    int z=now->v[x];
    now->v[x]=y;
    while(now)
    {
        now->cc[y]++;
        now->cc[z]--;
        now->cx[y/M]++;
        now->cx[z/M]--;
        now=now->nex;
    }
}

int Find(int l,int r,int x)
{
    int i;
    Lump *a,*b;
    a=xu;
    while(a->tot<l)
    {
        l-=a->tot;
        a=a->nex;
    }
    b=xu;
    while(b->tot<r)
    {
        r-=b->tot;
        b=b->nex;
    }
    memset(cx,0,sizeof cx);
    for(i=1;i<l;i++)
        cx[a->v[i]/M]--;
    for(i=1;i<=r;i++)
        cx[b->v[i]/M]++;
    a=a->las;
    b=b->las;
    for(i=0;;i++)
    {
        if(x<=b->cx[i]+cx[i]-a->cx[i])
            break;
        x-=b->cx[i]+cx[i]-a->cx[i];
    }
//    printf("k:%d\n",i);
    int zl=i*M;
    int zr=min(N,zl+M-1);
    memset(cc+zl,0,sizeof(int)*(zr-zl+1));
    a=a->nex;
    b=b->nex;
    for(i=1;i<l;i++)
        cc[a->v[i]]--;
    for(i=1;i<=r;i++)
        cc[b->v[i]]++;
    a=a->las;
    b=b->las;
  //  for(int i=1;i<=zr;++i)
 //   	printf("ccc:%d %d\n",cc[i],cx[i]);
 //   return 0;
    for(i=zl;;i++)
    {
        if(x<=b->cc[i]+cc[i]-a->cc[i])
            break;
        x-=b->cc[i]+cc[i]-a->cc[i];
    }
    return i;
}

void Big(Lump *x)
{
    if(x->tot==MAXM)
    {
        cnt++;
        int i;
        for(i=0;i<=M;i++)
            xu[cnt].cx[i]=x->cx[i];
        for(i=0;i<=N;i++)
            xu[cnt].cc[i]=x->cc[i];
        for(i=1;i<=M;i++)
            xu[cnt].v[i]=x->v[i];
        for(i=M+1;i<=MAXM;i++)
        {
            x->v[i-M]=x->v[i];
            xu[cnt].cc[x->v[i]]--;
            xu[cnt].cx[x->v[i]/M]--;
        }
        xu[cnt].tot=M;
        x->tot=M;
        xu[cnt].las=x->las;
        x->las->nex=xu+cnt;
        xu[cnt].nex=x;
        x->las=xu+cnt;
    }
}

void Insert(int x,int y)
{
    Lump *now=xu->nex;
    while(now->tot<x-1)
    {
        x-=now->tot;
        now=now->nex;
    }
    int i;
    now->tot++;
    for(i=now->tot;i>x;i--)
        now->v[i]=now->v[i-1];
    now->v[x]=y;
    Lump *jie=now;
    while(now)
    {
        now->cc[y]++;
        now->cx[y/M]++;
        now=now->nex;
    }
    Big(jie);
}

void solve()
{
    char t[3];
    int a,b,c;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%s%d%d",t,&a,&b);
  		a^=ans;b^=ans;  
        if(t[0]=='M')
            Change(a,b);
        else if(t[0]=='Q')
        {
            scanf("%d",&c);c^=ans;
            ans=Find(a,b,c);
            printf("%d\n",ans);
        }
        else
            Insert(a,b);
 //       printf("%d %d %d\n",a,b,c);
//    	if(m==24)
 //   		return;
    }
}

int main()
{
//	freopen("BZOJ3065.in","r",stdin);
//	freopen("BZOJ3065.out","w",stdout);
    init();
    solve();
    return 0;
}
