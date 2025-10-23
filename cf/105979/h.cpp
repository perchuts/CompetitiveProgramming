#include <bits/stdc++.h>
// Otimizacoes agressivas, pode deixar mais rapido ou mais devagar
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
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

void solve() {
    int n, h, k; cin >> n >> h >> k;
    vector<array<int, 3>> a(n);
    for (auto &[x, y, z] : a) cin >> x >> y >> z;

    int pos = -1;
    {
        int x, y; cin >> x >> y;
        for (int i = 0; i < n; i++) {
            auto [x1, y1, __] = a[i];
            if (x == x1 && y == y1) {
                pos = i;
            }
        }
        assert(pos != -1);

		if (y == 0) {
			cout << 0 << endl;
			return;
		}
    }

    vector<int> d(n, n); d[pos] = 0;
    queue<int> q; q.push(pos);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        auto [xu, yu, rodu] = a[u];
        for (int v = 0; v < n; v++) if (d[v] > d[u] + 1) {
			auto [xv, yv, rodv] = a[v];
			int dist = (xu - xv) * (xu - xv);
			dist += (yu - yv) * (yu - yv);
			
			if (rodv && dist <= k*k) {
				d[v] = d[u] + 1;
				q.push(v);
			} else if (rodu && dist <= h*h) {
				d[v] = d[u] + 1;
				q.push(v);
			}
        }
    }

	int ans = n + 1;
	for (int u = 0; u < n; u++) {
		auto [xu, yu, rodu] = a[u];
		if (rodu && d[u] != n && -yu <= h) {
			ans = min(ans, d[u] + 1);
		}
	}

	if (ans == n + 1) ans = -1;

	cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
