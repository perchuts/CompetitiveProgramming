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

void solve() {
	int n, m; cin >> n >> m;
	vector<int> vals(n);
	vector<ii> edg(m);
	for (auto& [u, v] : edg) {
		cin >> u >> v; --u, --v;
		vals[u] += (1ll << v);
		vals[v] += (1ll << u);
	}
	vector<int> ans(n);
	for (int i = 0; i < n; ++i) {
		vector<int> repr(60), coord(60);
		for (int j = 0; j < n; ++j) {
			if (j == i) continue;
			int cur_repr = (1ll << j), cur_val = vals[j];
			for (int k = 0; k < 60; ++k) {
				if ((cur_val>>k)&1) {
					if (repr[k] == 0) {
						repr[k] = cur_repr, coord[k] = cur_val;
						break;
					}
					cur_repr ^= repr[k];
					cur_val ^= coord[k];
				}
			}
		}
		int cur_repr = (1ll<<i), cur_val = vals[i];
		for (int j = 0; j < 60; ++j) {
			if ((cur_val>>j)&1) {
				if (repr[j] == 0) {
					cout << "No" << endl;
					exit(0);
				}
				cur_repr ^= repr[j];
				cur_val ^= coord[j];
			}
		}
		if (cur_val) {
			cout << "No" << endl;
		}
		for (int j = 0; j < n; ++j) {
			if ((cur_repr>>j)&1) {
				ans[j] += (1ll << i);
			}
		}
	}
	cout << "Yes" << endl;
	for (int i = 0; i < n; ++i) {
		assert((ans[i]>>i)&1);
		cout << ans[i] << ' ';
	}
	cout << endl;
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
