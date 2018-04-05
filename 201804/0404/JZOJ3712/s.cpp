#include <cstdio>

const int MAXN = 22, MAXS = 15555555;

int a[MAXN], b[MAXN], c[MAXN], d[MAXN], pre[MAXN], pow[MAXN], f[MAXS];

int main() {
    freopen("sword.in", "r", stdin);
    freopen("sword.out", "w", stdout);
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    pow[0] = 1;
    for (int i = 0; i < n; ++i) {
        pow[i + 1] = pow[i] * 3;
        pre[i] = n;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
        b[--a[i]] = i;
        if (i > 1)
            pre[a[i]] = a[i - 1];
    }
    a[m + 1] = n;
    f[0] = c[n] = 1;
    for (int i = 0; i < pow[n]; ++i)
        if (f[i]) {
            int cnt = 0, k = 1, pos = 0;
            for (int j = d[0] = 0, t = i; j < n; ++j, t /= 3)
                if (c[j] = t % 3) {
                    ++cnt;
                    if (b[j] > pos)
                        pos = b[j];
                    if (c[j] == 1)
                        d[++d[0]] = j;
                }
            d[d[0] + 1] = n;
            if (cnt == n)
                ans += f[i];
            for (int j = 0; j < n; ++j)
                if (!c[j] && c[pre[j]]) {
                    bool t = true;
                    for (; j > d[k]; ++k);
                    for (int l = pos + 1; t && l <= m + 1 && l <= k; ++l)
                        if (a[l] > j)
                            t = false;
                    if (t)
                        f[i + pow[j] + (k > d[0] ? 0 : pow[d[k]])] += f[i];
                }
        }
    printf("%d\n", ans);
    return 0;
}
