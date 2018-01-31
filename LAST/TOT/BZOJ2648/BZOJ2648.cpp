   #include<cstdio>  
    #include<cstring>  
    #include<cstdlib>  
    #include<cmath>  
    #include<iostream>  
    #include<algorithm>  
    #define maxn 1000010  
    #define inf 1000000000  
       
    using namespace std;  
       
    int n,m,root,ans,cur;  
       
    int fabs(int x)  
    {  
        if (x>=0) return x;  
        else return -x;  
    }  
       
    struct P  
    {  
        int d[2],mx[2],mn[2],lch,rch;  
        int& operator[](int x) {return d[x];}  
        friend bool operator<(P x,P y) {return x[cur]<y[cur];}  
        friend int dis(P x,P y) {return fabs(x[0]-y[0])+fabs(x[1]-y[1]);}  
    }p[maxn];  
       
    struct kdtree  
    {  
        P t[maxn],T;  
        int ans;  
        void update(int k)  
        {  
            int l=t[k].lch,r=t[k].rch;  
            for (int i=0;i<2;i++)  
            {  
                t[k].mn[i]=t[k].mx[i]=t[k][i];  
                if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);  
                if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);  
                if (l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);  
                if (r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);  
            }  
        }  
        int build(int l,int r,int now)  
        {  
            cur=now;  
            int mid=(l+r)/2;  
            nth_element(p+l,p+mid,p+r+1);  
            t[mid]=p[mid];  
            for (int i=0;i<2;i++) t[mid].mn[i]=t[mid].mx[i]=t[mid][i];  
            if (l<mid) t[mid].lch=build(l,mid-1,now^1);  
            if (r>mid) t[mid].rch=build(mid+1,r,now^1);  
            update(mid);  
            return mid;  
        }  
        int getmn(P x)  
        {  
            int tmp=0;  
            for (int i=0;i<2;i++)  
            {  
                tmp+=max(T[i]-x.mx[i],0);  
                tmp+=max(x.mn[i]-T[i],0);  
            }  
            return tmp;  
        }  
        void querymn(int k)  
        {  
            ans=min(ans,dis(t[k],T));  
            int l=t[k].lch,r=t[k].rch,dl=inf,dr=inf;  
            if (l) dl=getmn(t[l]);  
            if (r) dr=getmn(t[r]);  
            if (dl<dr)  
            {  
                if (dl<ans) querymn(l);  
                if (dr<ans) querymn(r);  
            }  
            else  
            {  
                if (dr<ans) querymn(r);  
                if (dl<ans) querymn(l);  
            }  
        }  
        void insert(int k,int now)  
        {  
            if (T[now]>=t[k][now])  
            {  
                if (t[k].rch) insert(t[k].rch,now^1);  
                else  
                {  
                    t[k].rch=++n;t[n]=T;  
                    for (int i=0;i<2;i++) t[n].mx[i]=t[n].mn[i]=t[n][i];  
                }  
            }  
            else  
            {  
                if (t[k].lch) insert(t[k].lch,now^1);  
                else  
                {  
                    t[k].lch=++n;t[n]=T;  
                    for (int i=0;i<2;i++) t[n].mx[i]=t[n].mn[i]=t[n][i];  
                }  
            }  
            update(k);  
        }  
        int query(int x,int y)  
        {  
            ans=inf;  
            T[0]=x;T[1]=y;T.lch=0;T.rch=0;  
            querymn(root);  
            return ans;  
        }  
        void insert1(int x,int y)  
        {  
            T[0]=x;T[1]=y;T.lch=0;T.rch=0;insert(root,0);  
        }  
    }kdtree;  
       
    int main()  
    {  
  //  	freopen("BZOJ2648.in","r",stdin);
 //   	freopen("BZOJ2648.out","w",stdout);
    	
        scanf("%d%d",&n,&m);  
        for (int i=1;i<=n;i++) scanf("%d%d",&p[i][0],&p[i][1]);  
        root=kdtree.build(1,n,0);  
        while (m--)  
        {  
            int op,x,y;  
            scanf("%d%d%d",&op,&x,&y);  
            if (op==1) kdtree.insert1(x,y);  
            else printf("%d\n",kdtree.query(x,y));  
        }  
        return 0;  
    }  
