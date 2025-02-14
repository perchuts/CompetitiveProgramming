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
	int n, m; cin >> n >> m;

	bool ok = true;
	vector<vector<int>> a(n);
	for (int i = 0; i < n; i++) {
		a[i].resize(m);
		for (auto &x : a[i]) cin >> x;
		sort(a[i].begin(), a[i].end());
	}

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&] (auto i, auto j) {
		return a[i][0] < a[j][0];
	});

	for (int j = 1; j < m; j++) {
		ok &= a[ord[0]][j] > a[ord[n - 1]][j - 1];
		for (int i = 1; i < n; i++) {
			ok &= a[ord[i]][j] > a[ord[i - 1]][j];
		}
	}

	if (ok) {
		for (auto i : ord) cout << i + 1 << " ";
		cout << endl;
	} else cout << -1 << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
