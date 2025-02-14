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
	int n, m, x, y; cin >> n >> m >> x >> y;
	vector<int> a(n), b(m);
	for (auto& X : a) cin >> X;
	for (auto& X : b) cin >> X;
	sort(all(a)), sort(all(b));
	int ans = 0, l = 0, r = n;
	auto possible = [&] (int K) {
		vector<int> cnt(n);
		int ptr = 0;
		for (auto X : b) {
			while (ptr != n and a[ptr] < X) ptr++;
			if (ptr == n) return false;
			if (ptr < K) {
				if (cnt[ptr] == y) ptr++;
			} else {
				if (cnt[ptr] == x) ptr++;
			}
			if (ptr == n) return false;
			cnt[ptr]++;
		}
		return true;
	};
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, l = md+1;
		else r = md-1;
	}
	if (!possible(0)) {
		cout << "impossible" << endl;
		return;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
