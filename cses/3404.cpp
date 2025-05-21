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

const int INF = inf;

template<typename T> vector<T> lis(vector<T>& v) {
	int n = v.size(), m = -1;
	vector<T> d(n+1, INF);
	vector<int> l(n);
	d[0] = -INF;

	for (int i = 0; i < n; i++) {
		// Para non-decreasing use upper_bound()
		int t = lower_bound(d.begin(), d.end(), v[i]) - d.begin();
		d[t] = v[i], l[i] = t, m = max(m, t);
	}

	int p = n;
	vector<T> ret;
	while (p--) if (l[p] == m) {
		ret.push_back(v[p]);
		m--;
	}
	reverse(ret.begin(),ret.end());

	return ret;
}
void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : b) cin >> x, --x;
    if (n < m) swap(a, b), swap(n, m);
    vector<int> na;
    for (auto x : a) if (x < m) na.pb(x);
    swap(a, na);
    n = m;
    vector<int> occ(n);
    for (int i = 0; i < n; ++i) occ[a[i]] = i;
    for (int i = 0; i < n; ++i) b[i] = occ[b[i]];
    auto ans = lis<int>(b);
    cout << sz(ans) << endl;
    for (auto x : ans) cout << a[x] + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
