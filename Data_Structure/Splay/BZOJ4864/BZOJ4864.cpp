#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 200003
#define inf 2000000000
using namespace std;
int val[N],mx[N],mn[N],ck[N],gv[N],ch[N][2],fa[N],size[N],cnt,root;
int n,m,a[N];
void update(int now)
{
    int l=ch[now][0]; int r=ch[now][1];
    mx[now]=mn[now]=val[now]; ck[now]=gv[now]; size[now]=1;
    if (l) mx[now]=max(mx[now],mx[l]),mn[now]=min(mn[now],mn[l]),
           ck[now]=min(ck[now],ck[l]),size[now]+=size[l];
    if (r) mx[now]=max(mx[now],mx[r]),mn[now]=min(mn[now],mn[r]),
           ck[now]=min(ck[now],ck[r]),size[now]+=size[r];
}
void clear(int x)
{
    val[x]=mx[x]=mn[x]=ck[x]=gv[x]=ch[x][0]=ch[x][1]=0;
}
int build(int l,int r)
{
    if (l>r) return 0;
    if (l==r) {
        int now=++cnt;
        val[now]=mx[now]=mn[now]=a[l]; size[now]=1;
        ck[now]=gv[now]=abs(a[l]-a[l-1]);
        return now;
    }
    int mid=(l+r)/2; int now=++cnt;
    val[now]=a[mid]; gv[now]=abs(a[mid]-a[mid-1]);
    ch[now][0]=build(l,mid-1);
    ch[now][1]=build(mid+1,r);
    fa[ch[now][0]]=fa[ch[now][1]]=now;
    update(now);
    return now;
}
int get(int x)
{
    return ch[fa[x]][1]==x;
}
void rotate(int x)
{
    int y=fa[x]; int z=fa[y]; int which=get(x);
    ch[y][which]=ch[x][which^1]; fa[ch[x][which^1]]=y;
    if (z) ch[z][ch[z][1]==y]=x;
    fa[x]=z; ch[x][which^1]=y; fa[y]=x;
    update(y); update(x);
}
void splay(int x,int tar)
{
    for (int f;(f=fa[x])!=tar;rotate(x)) 
     if (fa[f]!=tar)
      rotate(get(x)==get(f)?f:x);
    if (!tar) root=x;
}
int find(int x)
{
    int now=root; 
    while (true) {
        if (size[ch[now][0]]>=x) 
         now=ch[now][0];
        else {
            x-=size[ch[now][0]];
            if (x==1) return now;
            x--; now=ch[now][1];
        }
    }
}

void debug(int x)
{
	if(ch[x][0])
		debug(ch[x][0]);
	printf("%d %d %d %d %d\n",x,val[x],ck[x],gv[x],size[x]);
	if(ch[x][1])
		debug(ch[x][1]);
}

int main()
{
//	freopen("BZOJ4864.in","r",stdin);
//	freopen("BZOJ4864.out","w",stdout);

    scanf("%d%d",&n,&m);
    a[1]=a[n+2]=inf;
    for (int i=1;i<=n;i++) scanf("%d",&a[i+1]);
    root=build(1,n+2);
    for (int i=1;i<=m;i++) {
        char s[10]; int x,y; scanf("%s%d%d",s+1,&x,&y);
        if (s[2]=='e') {
            int aa=find(x); int bb=find(x+3);
            splay(aa,0); splay(bb,aa);
            int t=ch[ch[root][1]][0];
            clear(t);
            val[t]=mx[t]=mn[t]=y; size[t]=1;
            ck[t]=gv[t]=abs(val[root]-val[t]);
            gv[ch[root][1]]=abs(val[ch[root][1]]-val[t]);
            update(ch[root][1]); update(root);
        }  
        if (s[2]=='i')  {
            int aa=find(x+1); int bb=find(y+2);
            splay(aa,0); splay(bb,aa);
            int t=ch[ch[root][1]][0];
            printf("%d\n",ck[t]);
        }
        if (s[2]=='a') {
            int aa=find(x); int bb=find(y+2);
            splay(aa,0);splay(bb,aa);
            int t=ch[ch[root][1]][0];
            printf("%d\n",mx[t]-mn[t]);
        }
        if (s[1]=='i') {
            int aa=find(x+1); int bb=find(x+2);
            splay(aa,0); splay(bb,aa);
            int t=++cnt; fa[t]=ch[root][1]; ch[ch[root][1]][0]=cnt;
            val[t]=mx[t]=mn[t]=y; size[t]=1;
            ck[t]=gv[t]=abs(val[root]-val[t]);
            gv[ch[root][1]]=abs(val[ch[root][1]]-val[t]);
            update(ch[root][1]); update(root);
        }
    }
}
