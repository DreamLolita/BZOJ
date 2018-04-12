#include <bits/stdc++.h>

using namespace std;

int f[1000020];

int main() {
	freopen("auxiliary.in", "r", stdin);
	freopen("auxiliary.out", "w", stdout);
	int n;
	scanf("%d", &n);
	memset(f, 128, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		if (i >= 2) f[i] = max(f[i], f[i - 2] + 1);
		if (i >= 4) f[i] = max(f[i], f[i - 4] + 4);
		if (i >= 3) f[i] = max(f[i], f[i - 3] + 7);
	}
	printf("%d\n", f[n]);
}
