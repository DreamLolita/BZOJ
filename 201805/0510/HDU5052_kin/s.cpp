#pragma comment(linker, "/STACK:1024000000,1024000000") //��OJ����Windowsϵͳ��Ҫ������һ������ �����ֶ���ջ�������Ͳ�������ջ
#include<stdio.h>
#include<string.h>
#include<vector>
#define LL long long
using namespace std;
const int N = 50005;

int num[N],deep[N],son[N],fath[N];
int p[N],top[N],pos;
int head[N], to[N << 1], next1[N << 1], tot;

void init(int n)
{
    pos=0; tot=0;
    memset(head,-1,sizeof(head));
}
void addEdge(const int& u, const int& v) {
  to[tot] = v, next1[tot] = head[u], head[u] = tot++;
}

void addUndirEdge(const int& u, const int& v) {
  addEdge(u, v), addEdge(v, u);
}
void dfs1(int u,int pre,int d)//���ر�
{
    num[u]=1;
    deep[u]=d;
    fath[u]=pre;
    son[u]=-1;
    for(int i=head[u]; i!=-1; i=next1[i]){
        int v=to[i];
        if(v==fath[u])continue;
        dfs1(v,u,d+1);
        num[u]+=num[v];
        if(son[u]==-1||num[v]>num[son[u]])
            son[u]=v;
    }
}
void getpos(int u,int root)//�����ر߳�������ÿ�����������ཻ
{
    top[u]=root;   p[u]=++pos;
    if(son[u]==-1)
        return ;
    getpos(son[u],root);
    for(int i=head[u]; i!=-1; i=next1[i]){
        int v=to[i];
        if(son[u]!=v&&v!=fath[u])
            getpos(v,v);
    }
}

struct tree
{
    LL maxprice,minprice,addv,maxprofit0,maxprofit1;//����ֵ����С��ֵ���ӽڵ��ÿ���㶼��ӵ�ֵ�������ҵõ���������󣬴��ҵ���õ����������
}root[N*3];
LL val[N];

LL MAX(LL a,LL b){  return a>b?a:b; }
LL MIN(LL a,LL b){  return a>b?b:a; }
//void swp(int &a,int &b){  int tt=a; a=b; b=tt; }
void pushUp(int k)
{
    root[k].maxprofit0=MAX(root[k<<1].maxprofit0, root[k<<1|1].maxprofit0);
    root[k].maxprofit0=MAX(root[k].maxprofit0,root[k<<1|1].maxprice-root[k<<1].minprice);

    root[k].maxprofit1=MAX(root[k<<1].maxprofit1, root[k<<1|1].maxprofit1);
    root[k].maxprofit1=MAX(root[k].maxprofit1,root[k<<1].maxprice-root[k<<1|1].minprice);

    root[k].maxprice=MAX(root[k<<1].maxprice,root[k<<1|1].maxprice);
    root[k].minprice=MIN(root[k<<1].minprice,root[k<<1|1].minprice);
}
void pushDown(int k)
{
    if(root[k].addv){
        root[k<<1].maxprice+=root[k].addv;
        root[k<<1].minprice+=root[k].addv;
        root[k<<1].addv+=root[k].addv;

        root[k<<1|1].maxprice+=root[k].addv;
        root[k<<1|1].minprice+=root[k].addv;
        root[k<<1|1].addv+=root[k].addv;
        root[k].addv=0;
    }
}
void build(int l,int r,int k)
{
    root[k].addv=0;
    if(l==r){
        root[k].maxprofit0=root[k].maxprofit1=0;
        root[k].maxprice=root[k].minprice=val[l]; return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,k<<1);
    build(mid+1,r,k<<1|1);
    pushUp(k);
}
void update(int l,int r,int k,const int L,const int R,LL c)
{
    if(L<=l&&r<=R){
        root[k].maxprice+=c;
        root[k].minprice+=c;
        root[k].addv+=c;
        return ;
    }
    pushDown(k);
    int mid=(l+r)>>1;
    if(L<=mid) update(l,mid,k<<1,L,R,c);
    if(mid<R)  update(mid+1,r,k<<1|1,L,R,c);
    pushUp(k);
}
LL query(int l,int r,int k,const int L,const int R,const int op,LL& maxprice,LL& minprice)
{
    if(L<=l&&r<=R){
        maxprice=root[k].maxprice;
        minprice=root[k].minprice;
        if(op==0)                       //op==0��ʾ�����ߵ��ҵõ����������
            return root[k].maxprofit0;
        else
            return root[k].maxprofit1;
    }
    pushDown(k);
    int mid=(l+r)>>1 ;

    if(R<=mid) return  query(l,mid,k<<1,L,R,op,maxprice,minprice);           
    else if(mid<L)  return  query(mid+1,r,k<<1|1,L,R,op,maxprice,minprice);
    else{      //�ڿ�Խ���ҽڵ�ʱҪע��
        LL lmax,lmin,rmax,rmin,profit=0;
        profit=MAX(profit , query(l,mid,k<<1,L,R,op,lmax,lmin) );
        profit=MAX(profit , query(mid+1,r,k<<1|1,L,R,op,rmax,rmin) );
        if(op==0)
            profit=MAX(profit , rmax-lmin ); //ע��ĵط��������ߵ��ң��ҽڵ����ڵķ�Χ�����ֵ-��ڵ����ڷ�Χ����Сֵ
        else
            profit=MAX(profit , lmax-rmin );
        maxprice=MAX(lmax, rmax);  //��ǰ�ڵ����ڷ�Χ�������Сֵ
        minprice=MIN(lmin, rmin);
        return profit;
    }
}
LL solve(int u,int v,int c)
{
    int fu=top[u], fv=top[v];
    LL profit=0 ,tmax,tmin;  //���󣬵�ǰ����ε����ֵ����Сֵ
    LL maxu=0, minu=root[1].maxprice, maxv=0, minv=root[1].maxprice; //u,v ���߹���������ڵ������Сֵ
    while(fu!=fv){
        if(deep[fu]>=deep[fv]){
            profit=MAX(profit, query(1,pos,1,p[fu],p[u],1,tmax,tmin) ); //��ǰ����ε��������
            profit=MAX(profit, tmax-minu); //��ǰ�ε����ֵ-����u������߹�������ε���Сֵ
            profit=MAX(profit, maxv-tmin); //�����յ�v��ĳһ����������ֵ-��ǰ����ε���Сֵ
            maxu=MAX(maxu, tmax);  //u�㼺�߹���������ڵ����ֵ
            minu=MIN(minu, tmin);  //u�㼺�߹���������ڵ���Сֵ
            update(1,pos,1,p[fu],p[u],(LL)c);   //�Ȳ�֮�󣬵�ǰ����εĵ�ֵ������c
            u=fath[fu]; fu=top[u];
        }
        else{
            profit=MAX(profit, query(1,pos,1,p[fv],p[v],0,tmax,tmin) );
            profit=MAX(profit, maxv-tmin);
            profit=MAX(profit, tmax-minu);
            maxv=MAX(maxv, tmax);
            minv=MIN(minv, tmin);
            update(1,pos,1,p[fv],p[v],(LL)c);
            v=fath[fv]; fv=top[v];
        }
    }
    if(deep[u]>=deep[v]){
        profit=MAX(profit, query(1,pos,1,p[v],p[u],1,tmax,tmin) );
        profit=MAX(profit, maxv-tmin);//��Ҫ��������������ıȽ�
        profit=MAX(profit, tmax-minu);
        update(1,pos,1,p[v],p[u],(LL)c);
    }
    else{
        profit=MAX(profit, query(1,pos,1,p[u],p[v],0,tmax,tmin) );
        profit=MAX(profit, maxv-tmin);
        profit=MAX(profit, tmax-minu);
        update(1,pos,1,p[u],p[v],(LL)c);
    }

    return profit;
}
int main()
{
    int T,n,q,a,b,c,price[N];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        init(n);
        for(int i=1; i<=n; i++)
            scanf("%d",&price[i]);
        for(int i=1; i<n; i++){
            scanf("%d%d",&a,&b);
            addUndirEdge(a,b);
        }
        dfs1(1,1,1);
        getpos(1,1);
        pos=n;
        for(int i=1; i<=n; i++)
            val[p[i]]=(LL)price[i];
        build(1,pos,1);

        scanf("%d",&q);
        while(q--){
            scanf("%d%d%d",&a,&b,&c);
            printf("%lld\n",solve(a,b,c));
        }
    }
}

