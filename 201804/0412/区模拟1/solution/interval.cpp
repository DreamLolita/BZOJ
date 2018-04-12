#include <bits/stdc++.h>

#define N 100020

using namespace std;

int n, m, a[N], b[N];
int ql[N], qr[N], id[N], ansl[N], ansr[N];
vector<int> query;
vector< pair<int, int> > linv, rinv;

bool cmp(int x, int y) {
	if (ql[x] != ql[y]) return ql[x] < ql[y];
	return qr[x] < qr[y];
}

void upd(int, int&, int&, int&, int&, int);

void upd2(int x, int &nowl, int &nowr, int &nowmin, int &nowmax, int lim) {
	if (x < nowl) {
		int test = nowl;
		nowl = x;
		if (nowr - nowl + 1 > lim) return;
		for (int i = x; i < test; ++i)
			upd(i, nowl, nowr, nowmin, nowmax, lim);
	} else
	if (x > nowr) {
		int test = nowr;
		nowr = x;
		if (nowr - nowl + 1 > lim) return;
		for (int i = test + 1; i <= x; ++i)
			upd(i, nowl, nowr, nowmin, nowmax, lim);
	}
}

void upd(int x, int &nowl, int &nowr, int &nowmin, int &nowmax, int lim) {
	if (a[x] < nowmin) {
		int test = nowmin;
		nowmin = a[x];
		if (nowmax - nowmin + 1 > lim) {
			nowl = -1;
			return;
		}
		for (int i = a[x]; i < test; ++i)
			upd2(b[i], nowl, nowr, nowmin, nowmax, lim);
	} else
	if (a[x] > nowmax) {
		int test = nowmax;
		nowmax = a[x];
		if (nowmax - nowmin + 1 > lim) {
			nowl = -1;
			return;
		}
		for (int i = test + 1; i <= a[x]; ++i)
			upd2(b[i], nowl, nowr, nowmin, nowmax, lim);
	}	
}

void dc(int l, int r, vector<int> & q) {
	if (q.size() == 0) return;
	if (l == r) {
		for (int i = 0; i < q.size(); ++i)
			ansl[q[i]] = ansr[q[i]] = l;
		return;
	}
	vector<int> nxt;
	int mid = (l + r) / 2;
	nxt.clear();
	for (int i = 0; i < q.size(); ++i) 
		if (qr[q[i]] <= mid)
			nxt.push_back(q[i]);
	dc(l, mid, nxt);
	nxt.clear();
	for (int i = 0; i < q.size(); ++i)
		if (ql[q[i]] > mid)
			nxt.push_back(q[i]);
	dc(mid + 1, r, nxt);

	int nowl, nowr, nowmin, nowmax;
	linv.clear();
	rinv.clear();
	
	nowl = nowr = mid + 1;
	nowmin = nowmax = a[mid + 1];
	while (nowl >= l && nowr <= r) {
		if (-- nowl < l) break;
		upd(nowl, nowl, nowr, nowmin, nowmax, r - l + 1);
		if (nowl < l || nowr > r) break;
		linv.push_back( make_pair(nowl, nowr) );
	}

	nowl = nowr = mid;
	nowmin = nowmax = a[mid];
	while (nowl >= l && nowr <= r) {
		if (++ nowr > r) break;
		upd(nowr, nowl, nowr, nowmin, nowmax, r - l + 1);
		if (nowl < l || nowr > r) break;
		rinv.push_back( make_pair(- nowr, - nowl) );
	}

	sort(linv.begin(), linv.end());
	sort(rinv.begin(), rinv.end());

	for (int i = 0; i < q.size(); ++i) {
		int al = n, ar = 1;
		vector< pair<int, int> > :: iterator it;
		it = upper_bound(linv.begin(), linv.end(), make_pair(ql[q[i]], n + 1));
		if (it == linv.begin()) continue;
		-- it;
		al = min(al, it -> first);
		ar = max(ar, it -> second);
		it = upper_bound(rinv.begin(), rinv.end(), make_pair(- qr[q[i]], n + 1));
		if (it == rinv.begin()) continue;
		-- it;
		al = min(al, - it -> second);
		ar = max(ar, - it -> first);
		ansl[q[i]] = max(ansl[q[i]], al);
		ansr[q[i]] = min(ansr[q[i]], ar);
	}
}

int main() {
     freopen("interval.in", "r", stdin);
     freopen("interval.out", "w", stdout);
     
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &ql[i], &qr[i]);
	for (int i = 1; i <= m; ++i)
		id[i] = i;
	sort(id + 1, id + m + 1, cmp);
	for (int i = 1; i <= m; ++i)
		query.push_back(id[i]);
	for (int i = 1; i <= m; ++i)
		ansl[i] = 1, ansr[i] = n;
	dc(1, n, query);
	for (int i = 1; i <= m; ++i)
		printf("%d %d\n", ansl[i], ansr[i]);
} // 897989
