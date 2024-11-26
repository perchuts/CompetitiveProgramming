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
	int n, k; cin >> n >> k;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int x, int y) {
		return a[x] < a[y];
	});
	multiset<int> mt;
	int S = 0, ans = 0;
	for (int i = 0; i < k; ++i) mt.insert(b[ord[i]]), S += b[ord[i]];
	ans = S * a[ord[k-1]];
	for (int i = k; i < n; ++i) {
		mt.insert(b[ord[i]]);
		auto v = *prev(end(mt));
		mt.extract(v);
		S -= v;
		S += b[ord[i]];
		ckmin(ans, S * a[ord[i]]);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
