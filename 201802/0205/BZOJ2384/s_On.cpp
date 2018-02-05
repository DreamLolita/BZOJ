#include <cstdio>
#include <cstring>
#include <iostream>
 
using namespace std;
const int maxn=1000010;
int n,m,t1,t2;
int S[maxn],T[maxn],pos[maxn],p1[maxn],p2[maxn],pre[maxn],nxt[maxn],next[maxn],ans[maxn];
inline int rd()
{
    int ret=0,f=1;  char gc=getchar();
    while(gc<'0'||gc>'9') {if(gc=='-')f=-f;   gc=getchar();}
    while(gc>='0'&&gc<='9')   ret=ret*10+gc-'0',gc=getchar();
    return ret*f;
}
int main()
{
    n=rd(),m=rd();
    int i,j;
    for(i=0;i<n;i++) pos[i]=rd()-1,T[pos[i]]=i;
    for(i=0;i<n;i++) pre[i]=i-1,nxt[i]=(i==n-1)?-1:i+1;
    for(i=0;i<m;i++) S[i]=rd();
    for(i=n-1;i>=0;i--)
    {
        p1[i]=(pre[T[i]]==-1)?-1:(i-pos[pre[T[i]]]);
        p2[i]=(nxt[T[i]]==-1)?-1:(i-pos[nxt[T[i]]]);
        if(nxt[T[i]]!=-1)   pre[nxt[T[i]]]=pre[T[i]];
        if(pre[T[i]]!=-1)   nxt[pre[T[i]]]=nxt[T[i]];
    }
    i=0,j=-1,next[0]=-1;
    while(i<n)
    {
        if(j==-1||((p1[j]==-1||T[i-p1[j]]<T[i])&&(p2[j]==-1||T[i-p2[j]]>T[i])))   next[++i]=++j;
        else    j=next[j];
    }
    i=j=0;
    while(i<m)
    {
        if(j==-1||((p1[j]==-1||S[i-p1[j]]<S[i])&&(p2[j]==-1||S[i-p2[j]]>S[i])))   i++,j++;
        else    j=next[j];
        if(j==n)
        {
            ans[++ans[0]]=i-n+1,j=next[j];
        }
    }
    printf("%d\n",ans[0]);
    for(i=1;i<=ans[0];i++)   printf("%d%c",ans[i],i==ans[0]?'\n':' ');
    return 0;
}
