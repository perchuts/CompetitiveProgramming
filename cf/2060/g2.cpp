#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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

void solve(){
	int n; cin >> n;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) cin >> a[i].first;
	for (int i = 0; i < n; i++) cin >> a[i].second;

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&] (int i, int j) {
		return min(a[i].first, a[i].second) < min(a[j].first, a[j].second);
	});

	vector<pair<int, int>> sorted;
	for (int i : ord) sorted.push_back(a[i]);

	vector<int> where(n), p(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
		where[i] = i;
	}
	auto do_swap = [&] (int i, int j) {
		swap(where[p[i]], where[p[j]]);
		swap(p[i], p[j]);
		swap(a[p[i]], a[p[j]]);
		swap(a[p[i]].first, a[p[i]].second);
		swap(a[p[j]].first, a[p[j]].second);
	};

	for (int i = 0; i < n; i++) {
		if (a[i] == sorted[i]) continue;
		else {
			int j = where[ord[i]];
			do_swap(i, j);
		}
	}

	vector dp(n, vector(2, vector(2, false)));
	dp[0][0][0] = 1;
	dp[0][1][1] = 1;
	for (int i = 1; i < n; i++) {
		for (int par = 0; par < 2; par++) {
			for (int last = 0; last < 2; last++) {
				if (dp[i - 1][par][last] != 1) continue;
				for (int w = 0; w < 2; w++) {
					int x = (last ? a[i - 1].second : a[i - 1].first);
					int y = (!last ? a[i - 1].second : a[i - 1].first);
					int x1 = (w ? a[i].second : a[i].first);
					int y1 = (!w ? a[i].second : a[i].first);

					if (x > x1 || y > y1) continue;
					dp[i][par^w][w] = 1;
				}
			}
		}
	}

	bool ok = false;
	ok |= dp[n - 1][0][0];
	ok |= dp[n - 1][0][1];
	cout << (ok ? "YES" : "NO") << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
