#include<bits/stdc++.h>
using namespace std;
 
const int maxn=1010;
const int maxm=12010;
 
int n,m;//m������?��?12��Dm��?��?
 
int E[maxn];
int v[maxm],cir[maxm],next[maxm];//cir[]������?��?��?��?����no����?��??����??����?��?
 
int mp;
int path[maxm];//?????����?��??��??
 
int cnt,totalm;
bool vis[maxm];
bool cirvis[maxn];
 
int instack[maxn];//??��??��?����������?��y?Y��??��11
int sta[maxm],top;
 
void contact(int i,int j)//��?��?
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
        m+=k;//��3??��?12?��������?��?
        for (int j=1;j<=k;j++)
        {
            int arv;
            scanf("%d",&arv);
            contact(i,arv);
        }
    }
}
 
int dfs(int k)//�̨���?��?����������?2��?������???����?��?
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
 
void dfs_no_circle(int k)//�̨�?t��?����������?2?��?��??��2?��??��
{
    cnt++;
    path[cnt]=k;
    for (int p=E[k];p;p=next[p])
        if (!vis[p] && !cir[p])//���騰a2?��??��
        {
            vis[p]=1;
            dfs_no_circle(v[p]);
            return;
        }
}
 
void out_path()//��?3??��??
{
    for (int i=2;i<=cnt;i++)
        printf("%d ",path[i]);
    printf("0\n");
}
 
bool deal_circle(int i,int edgecnt)//?��?��
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
            if (instack[j]>0)//��?1???��?��??-?��??��?��?��??����?��??-?����?��????��
            {
                cir[p]=1;
                while (top>instack[j]) {cir[sta[top]]=1; top--;}//��??a?����?��?��?���¨�?����??��?������?��??����?��?��?
                return true;
            }
            else
            {
                bool tmp=deal_circle(j,p);
                if (tmp) return tmp;//��?1??����??����?��??��2??��?��D??����?��?��??����??��D?
            }
        }
    }
    instack[i]=0; sta[top]=0; top--;//??��?3???��?��??��������?ccy��-??��?��???3?��?��?��?
    return false;
}
 
int main()
{
 //   freopen("BZOJ3708.in","r",stdin);
//    freopen("BZOJ3708.out","w",stdout);
 
    init();
 
    cnt=totalm=0;
    memset(vis,0,sizeof(vis));
    int endvx=dfs(1);//�̨���?��?��������
    if (endvx!=n || totalm<m)//��?1??����?????2??��n��??��??2?��??����-��?��??��?����?3??����?��??��??
        out_path();
    else
    {
        bool flag=false;
        memset(cirvis,0,sizeof(cirvis));
        memset(cir,0,sizeof(cir));
        for (int i=1;i<n;i++)
        {
            if (cirvis[i]) continue;//??������??D??????��D��??��1y��?��?�ꡧn3y��a��?��??D??�䨮i3?���騮D?��2?
            top=0;
            memset(vis,0,sizeof(vis));
            memset(sta,0,sizeof(sta));//��?��?��?��?��?����o?
            memset(instack,0,sizeof(instack));//?3??��??��sta��?????????
            bool tmp=deal_circle(i,0);//?D??��D?��2?
            if (tmp==true) {flag=true; break;}//?����?��????��?����?��?3?��?
        }
        if (flag==false) printf("NIE\n");
        else
        {
            cnt=0;
            memset(vis,0,sizeof(vis));
            dfs_no_circle(1);//?T����?����???D?dfs��??����??��??
            out_path();
        }
    }
 
    return 0;
}
