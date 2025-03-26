#include "rect.h"
#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

long long solve01(vector<vector<int>> a) {
    int n = sz(a), m = sz(a[0]);
    vector<vector<int>> h(n, vector<int>(m)), h2(n, vector<int>(m));
	for (int j = 0; j < m; ++j) h[0][j] = a[0][j] ^ 1, h2[0][j] = a[0][j];
    for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (a[i][j] == 1) h[i][j] = 0, h2[i][j] = 1 + h2[i-1][j];
        else h[i][j] = 1 + h[i-1][j], h2[i][j] = 0;
    }
    int ans = 0;
    for (int i = 1; i < n-1; ++i) {
		for (int l = 0, r = 0; l < m; l = r) {
			if (a[i][r]) r++;
			else {
				int ok = (h[i][r] <= i);
				while (r < m and a[i][r] == 0) ok &= (h[i][r] == h[i][l] and a[i+1][r]), r++;
				ok &= (r < m and a[i][r]);
				ok &= (l and a[i][l-1]);
				if (ok) {
					ok &= (h2[i][l-1] >= h[i][l]);
					ok &= (h2[i][r] >= h[i][l]);
				}
				ans += ok;
			}
		}
    }
    return ans;
}
int brute(int n, int m, vector<vector<int>> a) {
	int ans = 0;
	for (int x1 = 1; x1 < n-1; ++x1) for (int y1 = 1; y1 < m-1; ++y1) {
			for (int x2 = x1; x2 < n-1; ++x2) for (int y2 = y1; y2 < m-1; ++y2) {
				int ok = 1;
				for (int i = x1; i <= x2; ++i) for (int j = y1; j <= y2; ++j) {
					ok &= (a[i][j] < min({a[i][y1-1], a[i][y2+1], a[x1-1][j], a[x2+1][j]}));
				}
				ans += ok;
			}
	}
	return ans;
}
long long cubic(int n, int m, vector<vector<int>> a) {
	vector<vector<vector<int>>> oks(m, vector<vector<int>>(m)), up = oks;
	vector<vector<int>> st(m, vector<int>(1, 0));
	vector<int> seta(m);
	int ans = 0;
	for (int i = 0; i < n-1; ++i) {
		for (int j = 1; j < m-1; ++j) {
			while (!st[j].empty() and a[i+1][j] > a[st[j].back()][j]) st[j].pop_back();
			seta[j] = (st[j].empty() ? -1 : st[j].back());
			st[j].push_back(i+1);
		}
		for (int j = 1; j < m; ++j) for (int k = j, okd = 1, oku = 1, mx = -1, mn_seta = -1; k < m-1; ++k) {
			okd &= (a[i][k] < a[i+1][k]);
			oku &= (i and a[i][k] < a[i-1][k]);
			ckmax(mx, a[i][k]);
			ckmax(mn_seta, seta[k]);
			for (int w = j; w <= k; ++w) while (!oks[j][k].empty() and a[i][w] >= a[oks[j][k].back()][w]) oks[j][k].pop_back();
			if (oku) oks[j][k].pb(i-1);
			if (mx < min(a[i][j-1], a[i][k+1])) {
				if (okd) {
					int tot = 0;
					for (auto x : oks[j][k]) if (x >= mn_seta) tot++;
					ans += tot;
				}
			}
			else oks[j][k].clear();
		}
	}
	return ans;
}
long long count_rectangles(vector<vector<int>> a) {
    int n = sz(a), m = sz(a[0]), mx = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) ckmax(mx, a[i][j]);
    if (mx <= 1) return solve01(a);
	return cubic(n, m, a);
}
#ifdef gato
int main() {
	int t = 1;
	while (true) {
		int n = rnd(1, 20), m = rnd(1, 20);
		vector<vector<int>> a(n, vector<int>(m));
		for (auto& x : a) for (auto& y : x) y = rnd(0, 20);
		int ans = brute(n, m, a), my = cubic(n, m, a);
		if (ans != my) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << m << endl;
			for (auto x : a) {
				for (auto y : x) cout << y << ' ';
				cout << endl;
			}
			cout << "Your output: " << my << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
}
#endif
