#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define maxn 4207

inline int rd() {
    char c = getchar();
    while (!isdigit(c)) c = getchar() ; int x = c - '0';
    while (isdigit(c = getchar())) x = x * 10 + c - '0';
    return x;
}

char _p[maxn][7];
int _l[maxn] , tot;

struct Trie {
    int ch[maxn][26];
    int val[maxn];
    int _upcase , sz;

    inline int idx(char c) {
        if (_upcase) return c - 'A';
        else return c - 'a';
    }

    void init(int t) {
        memset(ch[0] , 0 , sizeof ch[0]);
        _upcase = t;
        sz = 1 , tot = 0;
    }

    int get(char*s , int n) {
        int u = 0;
        rep (i , 1 , n) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                val[sz] = 0 , memset(ch[sz] , 0 , sizeof ch[sz]);
                ch[u][c] = sz ++;
            }
            u = ch[u][c];
        }
        if (!val[u]) {
            val[u] = ++ tot;
            if (!_upcase) {
                rep (i , 1 , n)
                    _p[tot][i] = s[i];
                _p[tot][n + 1] = '\0';
                _l[tot] = n;
            }
        }
        return val[u];
    }
}large , small;

char tmp[maxn] , str[maxn] , tar[maxn];
int  K , mark[maxn] , lc[maxn] , rc[maxn] , n , st , f[maxn / 4][maxn] , vis[maxn];

void read_str() {
    int t = 0 , l1 = 0 , r1 = 0 , r2 = 0;
    for (char c = getchar();c != '\n';c = getchar()) {
        if (c == ' ') c = getchar();
        if (c == '=')
            l1 = large.get(tmp , t) , t = 0;
        else if (c == '+')
            r1 = large.get(tmp , t) , t = 0;
        if (isalpha(c)) tmp[++ t] = c;
    }
    if (!r1) {
        r1 = small.get(tmp , t);
        lc[l1] = r1;
        mark[r1] = 1;
    } else {
        r2 = large.get(tmp , t);
        lc[l1] = r1 , rc[l1] = r2;
    }
}

void input() {
    rep (i , 0 , tot) rep(j , 0 , n + 1) f[i][j] = 0;
    rep (i , 0 , tot) mark[i] = lc[i] = rc[i] = vis[i] = 0;
    scanf("%d\n" , &K);
    large.init(1) , small.init(0);
    rep (i , 1 , K)
        read_str();
    scanf("%s" , str + 1);
    scanf("%s" , tar + 1);
    n = strlen(tar + 1);
}

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    if (!u) return;
    if (mark[lc[u]]) {
        int v = u , u = lc[v];
        rep (i , 1 , n + 1) {
            int j = i;
            rep (k , 1 , _l[u])
                if (j > n)
                    break;
                else if (_p[u][k] == tar[j])
                    j ++;
            f[v][i] = j;
        }
    } else {
        dfs(lc[u]) , dfs(rc[u]);
        rep (i , 1 , n + 1)
            f[u][i] = f[rc[u]][f[lc[u]][i]];
    }
}

void solve() {
    st = large.get(str , strlen(str + 1));
    dfs(st);
    if (f[st][1] > n)
        puts("YES");
    else
        puts("NO");
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("BZOJ4060.in","r",stdin);
	freopen("BZOJ4060.out","w",stdout);
    #endif
    per (T , rd() , 1) {
        input();
        solve();
    }
    return 0;
}
