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
    //��֤ÿ����ĶȲ�����3  
    void build(int u, int fa) {  
        int father = 0;  
        for (int i = head[u]; ~i; i = edge[i].nxt) {  
            int v = edge[i].v, w = edge[i].w;  
            if (v == fa) continue;  
            if (father == 0) { //��û�������ӽڵ㣬ֱ������  
                ADD(u, v, w); ADD(v, u, w);  
                father = u;  
                build(v, u);  
            } else {        //�Ѿ���һ���ӽڵ㣬�򴴽�һ���½ڵ㣬��v�����½ڵ���  
                mark[++N] = 0;  
                ADD(N, father, 0); ADD(father, N, 0);  
                father = N;  
                ADD(v, father, w); ADD(father, v, w);  
                build(v, u);  
            }  
        }  
    }  
    //nxt����һ���ߵı�ţ�pre����һ���ߵı��  
    void get_pre() {  
        memset(tail, -1, sizeof(tail));  
        for (int i = 1; i <= N; i++) {  
            for (int j = Head[i]; ~j; j = E[j].nxt) {  
                E[j].pre = tail[i];  
                tail[i] = j;  
            }  
        }  
    }  
    //�ؽ�һ��ͼ  
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
        int rt, midlen, ans; //���ڵ㣬���ıߣ���(�����)  
        int ls, rs;         //�����������  
        priority_queue<point>q;  
    } T[2*MX];  
      
    //����ÿ��������С  
    void dfs_size(int u, int fa, int dir) {  
        add(u, rt, dir);  
        //����ǰ׵㣬��ѹ����ڵ�rt�Ķ��У�distΪ�����ľ���  
        //�����еĵ�����pt�ĸ������ĸ��£�pt�ڵ㲻��Ҫ�õ���  
        //���T[pt].rt�Ǹ����������ı��ϵĵ�  
        if (mark[u]) T[rt].q.push(point(u, dir));  
        sz[u] = 1;  
        for (int i = Head[u]; ~i; i = E[i].nxt) {  
            int v = E[i].v, w = E[i].w;  
            if (v == fa) continue;  
            dfs_size(v, u, dir + w);  
            sz[u] += sz[v];  
        }  
    }  
    //�����ı�  
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
    //����  
    void PushUP(int rt) {  
        T[rt].ans = -1;  
        while (!T[rt].q.empty() && mark[T[rt].q.top().u] == 0) T[rt].q.pop();//�����ڵ�  
        int ls = T[rt].ls, rs = T[rt].rs; //lsΪ����ӣ�rsΪ�Ҷ���  
        if (ls == 0 && rs == 0) { //û�����Ҷ���  
            if (mark[T[rt].rt])T[rt].ans = 0;  
        } else {  
            if (T[ls].ans > T[rt].ans) T[rt].ans = T[ls].ans; //�������ӵĽ�������Ҷ���  
            if (T[rs].ans > T[rt].ans) T[rt].ans = T[rs].ans; //����Ҷ��ӵĽ�����������  
            if (!T[ls].q.empty() && !T[rs].q.empty()) //�������ıߵ�  
                T[rt].ans = max(T[rt].ans, T[ls].q.top().dis + T[rs].q.top().dis + T[rt].midlen);  
        }  
    }  
    void DFS(int id, int u) {  
        rt = id; Max = N; midedge = -1;  
        T[id].rt = u;  
        dfs_size(u, 0, 0);  
        dfs_midedge(u, -1);  
        if (~midedge) {  
            //���ıߵ�����2��  
            int p1 = E[midedge].v;  
            int p2 = E[midedge ^ 1].v;  
            //���ı߳���  
            T[id].midlen = E[midedge].w;  
            //��������  
            T[id].ls = ++cnt;  
            T[id].rs = ++cnt;  
            //ɾ�����ı�  
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
