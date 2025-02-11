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
	vector<int> v(n);
	int s = 0, ans = 0;
	for (auto& x : v) cin >> x, s += x;
	auto testa = [&] (int x) {
		vector<int> vals;
		int soma = 0, soma2 = 0, best = k+1; 
		for (auto y : v) vals.pb(y%x), soma += vals.back();
		sort(all(vals)), reverse(all(vals));
		for (auto y : vals) {
			soma -= y;
			soma2 += x - y;
			ckmin(best, max(soma, soma2));
		}
		if (best <= k) ckmax(ans, x);
	};
	for (int i = 1; i * i <= s; ++i) if (s % i == 0) testa(i), testa(s/i);
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
