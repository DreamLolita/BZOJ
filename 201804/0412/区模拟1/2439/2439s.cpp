#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar())  if (ch=='-')    f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar())    x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline void print(int x){
    if (x>=10)     print(x/10);
    putchar(x%10+'0');
}
const int N=3e5;
int Ans[N+10],last[N+10],cnt[N+10];
struct S1{
    int x,y,t;
    void join(int i){x=read(),y=read(),t=i;}
    bool operator <(const S1 &a)const{return y!=a.y?y>a.y:x<a.x;}
}A[N*2+10];
struct S2{
    //splay的维护需要按照x坐标为第一关键字，时间为第二关键字来维护 
    #define ls(x) tree[x][0]
    #define rs(x) tree[x][1]
    #define T(x) (rs(f[x])==x)
    struct S3{
        int x,t;
        void clear(){x=t=0;}
        void join(int a,int b){x=a,t=b;}
        bool operator <(const S3 &a)const{return x!=a.x?x<a.x:t<a.t;}
    }val[N*4+10],tmp;
    int f[N*4+10],tree[N*4+10][2];
    int root,len;
    void clear(int x){ls(x)=rs(x)=f[x]=0,val[x].clear();}
    void move(int x){
        int fa=f[x],son=tree[x][T(x)^1];
        tree[x][T(x)^1]=fa;
        tree[fa][T(x)]=son;
        if (son)    f[son]=fa;
        f[x]=f[fa];
        if (f[x])   tree[f[x]][T(fa)]=x;
        f[fa]=x;
    }
    void splay(int x){
        while (f[x]){
            if (f[f[x]])    T(x)==T(f[x])?move(f[x]):move(x);
            move(x);
        }
        root=x;
    }
    void insert(int x,int t){
        val[++len].join(x,t);
        if (!root){
            root=len;
            return;
        }
        int i=root;
        while (true){
            if (val[len]<val[i]){
                if (!ls(i)){f[ls(i)=len]=i;break;}
                i=ls(i);
            }else{
                if (!rs(i)){f[rs(i)=len]=i;break;}
                i=rs(i);
            }
        }
        splay(len);
    }
    int get_pre(){
        int x=ls(root);
        while (rs(x))   x=rs(x);
        return x;
    }
    int get_suc(){
        int x=rs(root);
        while (ls(x))   x=ls(x);
        return x;
    }
    void Delete(int x){
        splay(x);
        if (!(ls(x)&&rs(x))){
            f[root=ls(x)+rs(x)]=0;
            clear(x);
            return;
        }
        //删除必须找后继节点，这样才能保证根不变 
        int i=get_suc();
        splay(i);
        f[ls(i)=ls(x)]=i;
        clear(x);
    }
}Splay;
struct S4{
    int f[N+10];
    int find(int x){return f[x]?f[x]=find(f[x]):x;}
    void merge(int x,int y){
        x=find(x),y=find(y);
        if (x!=y)   f[x]=y,cnt[y]+=cnt[x];
        //merge有顺序 
    }
}F;
int main(){
	freopen("CERC2017B.in","r",stdin);
	freopen("CERC2017B.out","w",stdout);
    int n=read();
    for (int i=1;i<=n;i++){
        A[i].join(0);
        (A[i].x<<=1)--;
        (A[i].y<<=1)--;
    }
    int m=read();
    for (int i=1;i<=m;i++){
        A[i+n].join(i);
        A[i+n].x<<=1;
        A[i+n].y<<=1;
    }
    //消去0.5的影响，所以位移一位 
    sort(A+1,A+1+n+m);
    for(int i=1;i<=n+m;++i)
    	printf("%d %d %d\n",A[i].x,A[i].y,A[i].t);return 0;
    for (int i=1;i<=n+m;i++){
        Splay.insert(A[i].x,A[i].t);
        //因为if语句里两个都要insert，虽然用处不同，但是我懒 
        if (A[i].t){
            int suc=Splay.get_suc();
            if (suc)    last[A[i].t]=Splay.val[suc].t;
            //记录右边的第一个时间比其大的点，方便并查集维护 
            while (true){
                //保证根不变，一个个删掉前驱节点，类似于单调栈
                //至于保证根不变，嘿嘿，splay删除是个骚操作 
                int pre=Splay.get_pre();
                if (!pre||Splay.val[pre].t<A[i].t)  break;
                Splay.Delete(pre);
            }
        }else{
            //insert之后才能找到其后继，但是这个点不能加进去，所以直接删掉 
            int T=Splay.get_suc();
            Splay.Delete(Splay.root);
            if (T)  cnt[Splay.val[T].t]++;
            //初步统计答案 
        }
    }
    for (int i=m;i;i--){
        Ans[i]=cnt[F.find(i)];
        if (last[i])    F.merge(i,last[i]);
        //merge操作有顺序，如果说last[i]的时间大于i的时间，加不加没有任何影响，为了方便，都加 
    }
    for (int i=1;i<=m;i++)  printf("%d\n",Ans[i]);
    return 0;
}
