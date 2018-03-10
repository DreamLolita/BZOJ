    #include<bits/stdc++.h>  
    using namespace std;  
    const int MX = 2e5 + 5;  
    const int MXE = 4e6 + 5;  
    struct Edge {  
        int v, w, nxt, pre;  
    } E[MXE], edge[MXE];  
    int Head[MX], head[MX], rear, tot, tail[MX];  
    int mark[MX], sz[MX];  
    int N, n, cnt, rt, midedge, Max;  
    void init() {  
        memset(head, -1, sizeof(head));  
        tot = 0;  
    }  
    void INIT() {  
        memset(Head, -1, sizeof(Head));  
        rear = 0;  
    }  
    void add(int u, int v, int w) {  
        edge[tot].v = v;  
        edge[tot].w = w;  
        edge[tot].nxt = head[u];  
        head[u] = tot++;  
    }  
    void ADD(int u, int v, int w) {  
        E[rear].v = v;  
        E[rear].w = w;  
        E[rear].nxt = Head[u];  
        Head[u] = rear++;  
    }	  
    void Delete(int u, int i) {  
        if (Head[u] == i) Head[u] = E[i].nxt;  
        else E[E[i].pre].nxt = E[i].nxt;  
        if (tail[u] == i) tail[u] = E[i].pre;  
        else E[E[i].nxt].pre = E[i].pre;  
    }  
    //保证每个点的度不超过3  
    void build(int u, int fa) {  
        int father = 0;  
        for (int i = head[u]; ~i; i = edge[i].nxt) {  
            int v = edge[i].v, w = edge[i].w;  
            if (v == fa) continue;  
            if (father == 0) { //还没有增加子节点，直接连上  
                ADD(u, v, w); ADD(v, u, w);  
                father = u;  
                build(v, u);  
            } else {        //已经有一个子节点，则创建一个新节点，把v连在新节点上  
                mark[++N] = 0;  
                ADD(N, father, 0); ADD(father, N, 0);  
                father = N;  
                ADD(v, father, w); ADD(father, v, w);  
                build(v, u);  
            }  
        }  
    }  
    //nxt是下一条边的编号，pre是上一条边的编号  
    void get_pre() {  
        memset(tail, -1, sizeof(tail));  
        for (int i = 1; i <= N; i++) {  
            for (int j = Head[i]; ~j; j = E[j].nxt) {  
                E[j].pre = tail[i];  
                tail[i] = j;  
            }  
        }  
    }  
    //重建一个图  
    void rebuild() {  
        INIT();  
        N = n;  
        for (int i = 1; i <= N; i++) mark[i] = 1;  
        build(1, 0);  
        get_pre();  
        init();  
    }  
      
    struct point {  
        int u, dis;  
        point() {}  
        point(int _u, int _dis) {  
            u = _u; dis = _dis;  
        }  
        bool operator<(const point& _A)const {  
            return dis < _A.dis;  
        }  
    };  
    struct node {  
        int rt, midlen, ans; //根节点，中心边，答案(最长树链)  
        int ls, rs;         //左右子树编号  
        priority_queue<point>q;  
    } T[2*MX];  
      
    //搜索每个子树大小  
    void dfs_size(int u, int fa, int dir) {  
        add(u, rt, dir);  
        //如果是白点，则压入根节点rt的队列，dist为到根的距离  
        //队列中的点用来pt的父亲树的更新，pt节点不需要用到，  
        //因此T[pt].rt是父亲树的中心边上的点  
        if (mark[u]) T[rt].q.push(point(u, dir));  
        sz[u] = 1;  
        for (int i = Head[u]; ~i; i = E[i].nxt) {  
            int v = E[i].v, w = E[i].w;  
            if (v == fa) continue;  
            dfs_size(v, u, dir + w);  
            sz[u] += sz[v];  
        }  
    }  
    //找中心边  
    void dfs_midedge(int u, int code) {  
        if (max(sz[u], sz[T[rt].rt] - sz[u]) < Max) {  
            Max = max(sz[u], sz[T[rt].rt] - sz[u]);  
            midedge = code;  
        }  
        for (int i = Head[u]; ~i; i = E[i].nxt) {  
            int v = E[i].v;  
            if (i != (code ^ 1)) dfs_midedge(v, i);  
        }  
    }  
    //更新  
    void PushUP(int rt) {  
        T[rt].ans = -1;  
        while (!T[rt].q.empty() && mark[T[rt].q.top().u] == 0) T[rt].q.pop();//弹出黑点  
        int ls = T[rt].ls, rs = T[rt].rs; //ls为左儿子，rs为右儿子  
        if (ls == 0 && rs == 0) { //没有左右儿子  
            if (mark[T[rt].rt])T[rt].ans = 0;  
        } else {  
            if (T[ls].ans > T[rt].ans) T[rt].ans = T[ls].ans; //如果左儿子的结果大于右儿子  
            if (T[rs].ans > T[rt].ans) T[rt].ans = T[rs].ans; //如果右儿子的结果大于左儿子  
            if (!T[ls].q.empty() && !T[rs].q.empty()) //穿过中心边的  
                T[rt].ans = max(T[rt].ans, T[ls].q.top().dis + T[rs].q.top().dis + T[rt].midlen);  
        }  
    }  
    void DFS(int id, int u) {  
        rt = id; Max = N; midedge = -1;  
        T[id].rt = u;  
        dfs_size(u, 0, 0);  
        dfs_midedge(u, -1);  
        if (~midedge) {  
            //中心边的左右2点  
            int p1 = E[midedge].v;  
            int p2 = E[midedge ^ 1].v;  
            //中心边长度  
            T[id].midlen = E[midedge].w;  
            //左右子树  
            T[id].ls = ++cnt;  
            T[id].rs = ++cnt;  
            //删除中心边  
            Delete(p1, midedge ^ 1);  
            Delete(p2, midedge);  
            DFS(T[id].ls, p1);  
            DFS(T[id].rs, p2);  
        }  
        PushUP(id);  
    }  
    void update(int u) {  
        mark[u] ^= 1;  
        for (int i = head[u]; ~i; i = edge[i].nxt) {  
            int v = edge[i].v, w = edge[i].w;  
            if (mark[u] == 1) T[v].q.push(point(u, w));  
            PushUP(v);  
        }  
    }  
    int main() {  
       	freopen("SPOJ_QTREE4.in","r",stdin);
		freopen("SPOJ_QTREE4.out","w",stdout);  
        scanf("%d", &n);  
        init();  
        for (int i = 1, u, v, w; i < n; i++) {  
            scanf("%d%d%d", &u, &v, &w);  
            add(u, v, w); add(v, u, w);  
        }  
        rebuild();  
        DFS(cnt = 1, 1);  
        char op[2]; int m, x;  
        scanf("%d", &m);  
        while (m--) {  
            scanf("%s", op);  
            if (op[0] == 'A') {  
                if (T[1].ans == -1) printf("They have disappeared.\n");  
                else printf("%d\n", T[1].ans);  
            } else {  
                scanf("%d", &x);  
                update(x);  
            }  
        }  
        return 0;  
    }  
