#include<bits/stdc++.h>
using namespace std;
 
const int maxn=1010;
const int maxm=12010;
 
int n,m;//m¡À¨ª¨º?¨°?12¨®Dm¨¬?¡À?
 
int E[maxn];
int v[maxm],cir[maxm],next[maxm];//cir[]¡À¨ª¨º?¨º?¡¤?¨º?¨¨£¤no¨®¦Ì?¡ä??¨²¦Ì??¡¤¦Ì?¡À?
 
int mp;
int path[maxm];//?????¨°¦Ì?¦Ì??¡¤??
 
int cnt,totalm;
bool vis[maxm];
bool cirvis[maxn];
 
int instack[maxn];//??¡ê??¨°?¡¤¨º¡À¡ä¡é¡ä?¨ºy?Y¦Ì??¨¢11
int sta[maxm],top;
 
void contact(int i,int j)//¨¢?¡À?
{
    cnt++;
    v[cnt]=j; cir[cnt]=0; next[cnt]=E[i]; E[i]=cnt;
}
 
void init()
{
    scanf("%d",&n);
    cnt=0;
    for (int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        m+=k;//¨ª3??¨°?12?¨¤¨¦¨´¨¬?¡À?
        for (int j=1;j<=k;j++)
        {
            int arv;
            scanf("%d",&arv);
            contact(i,arv);
        }
    }
}
 
int dfs(int k)//¦Ì¨²¨°?¡ä?¡À¨¦¨¤¨²¡ê?2¡é?¨°¡¤¦Ì???¨¢¨º?¦Ì?
{
    cnt++;
    path[cnt]=k;
    for (int p=E[k];p;p=next[p])
        if (!vis[p])
        {
            vis[p]=1;
            totalm++;
            return dfs(v[p]);
        }
    return k;
}
 
void dfs_no_circle(int k)//¦Ì¨²?t¡ä?¡À¨¦¨¤¨²¡ê?2?¡Á?¨ª??¨²2?¦Ì??¡¤
{
    cnt++;
    path[cnt]=k;
    for (int p=E[k];p;p=next[p])
        if (!vis[p] && !cir[p])//¡Á¡é¨°a2?¡Á??¡¤
        {
            vis[p]=1;
            dfs_no_circle(v[p]);
            return;
        }
}
 
void out_path()//¨º?3??¡¤??
{
    for (int i=2;i<=cnt;i++)
        printf("%d ",path[i]);
    printf("0\n");
}
 
bool deal_circle(int i,int edgecnt)//?¨°?¡¤
{
    cirvis[i]=1;
    top++; instack[i]=top; sta[top]=edgecnt;
    for (int p=E[i];p;p=next[p])
    {
        int j=v[p];
        if (j==n) continue;
        if (!vis[p])
        {
            vis[p]=1;
            if (instack[j]>0)//¨¨?1???¦Ì?¨°??-?¨²??¨¤?¨¢?¡ê??¨¨¡ê?¨°??-?¨°¦Ì?¨°????¡¤
            {
                cir[p]=1;
                while (top>instack[j]) {cir[sta[top]]=1; top--;}//¡ã??a?¡¤¨¦?¦Ì?¡À?¡Á¡Â¨¦?¡À¨º??¡ê?¡À¨ª¨º?¨º??¡¤¨¦?¦Ì?¡À?
                return true;
            }
            else
            {
                bool tmp=deal_circle(j,p);
                if (tmp) return tmp;//¨¨?1??¨°¦Ì??¡¤¨¢?¡ê??¨ª2??¨´?¨¬D??¨°¨¢?¡ê?¡¤??¨°¡ê??¨¬D?
            }
        }
    }
    instack[i]=0; sta[top]=0; top--;//??¦Ì?3???¡ã?¡ê??¨¦¨¢¡¥¦Ì?ccy¡À-??¨¢?¨°???3?¦Ì?¦Ì?¡¤?
    return false;
}
 
int main()
{
 //   freopen("BZOJ3708.in","r",stdin);
//    freopen("BZOJ3708.out","w",stdout);
 
    init();
 
    cnt=totalm=0;
    memset(vis,0,sizeof(vis));
    int endvx=dfs(1);//¦Ì¨²¨°?¡ä?¡À¨¦¨¤¨²
    if (endvx!=n || totalm<m)//¨¨?1??¨¢¨º?????2??¨²n¦Ì??¨°??2?¨º??¡¤¨¤-¨ª?¡ê??¡À?¨®¨º?3??¨°¦Ì?¦Ì??¡¤??
        out_path();
    else
    {
        bool flag=false;
        memset(cirvis,0,sizeof(cirvis));
        memset(cir,0,sizeof(cir));
        for (int i=1;i<n;i++)
        {
            if (cirvis[i]) continue;//??¨®¨²¨ª??D??????¨®D¡¤??¨º1y¦Ì?¦Ì?¡ê¡§n3y¨ªa¡ê?¡ê??D??¡ä¨®i3?¡¤¡é¨®D?¡¤2?
            top=0;
            memset(vis,0,sizeof(vis));
            memset(sta,0,sizeof(sta));//¡ä?¦Ì?¨º?¡À?¦Ì?¡À¨¤o?
            memset(instack,0,sizeof(instack));//?3??¦Ì??¨²sta¦Ì?????????
            bool tmp=deal_circle(i,0);//?D??¨®D?¡¤2?
            if (tmp==true) {flag=true; break;}//?¨°¦Ì?¨°????¨ª?¨¦¨°?¨¬?3?¨¢?
        }
        if (flag==false) printf("NIE\n");
        else
        {
            cnt=0;
            memset(vis,0,sizeof(vis));
            dfs_no_circle(1);//?T¨º¨®?¡¤¡ê???D?dfs¡ê??¨°¨¬??¡¤??
            out_path();
        }
    }
 
    return 0;
}
