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
const int maxn = 8e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int bit[maxn], N;

void insert(int x, int k) {
	while (x <= N) ckmax(bit[x], k), x += x&(-x);
}

int query(int x) {
	int ans = 0;
	while (x) ckmax(ans, bit[x]), x -= x&(-x);
	return ans;
}

void solve(){
	int n; cin >> n;
	vector<int> a(n);
	vector<int> cc;
	for (auto& x : a) cin >> x, cc.pb(x), cc.pb(x+1), cc.pb(x+2);
	sort(all(cc)), cc.erase(unique(all(cc)), end(cc));
	N = sz(cc) + 10;
	int ans = 0;
	auto coord = [&] (int x) { 
		int ret = lower_bound(all(cc), x) - begin(cc) + 1; 
		return ret;
	};
	vector<int> best_right(n);
	for (int i = n - 1; i >= 0; --i) {
		int my = coord(a[i]);
		int best = query(N - my - 1) + 1;
		ckmax(ans, query(N) + 1); // fazer eu virar um cara pequeno o bastante;
		insert(N - my, best);
		if (i >= 2) best_right[i-2] = query(N-coord(a[i-2]+2));
		ckmax(ans, best);
	}
	for (int i = 0; i <= N; ++i) bit[i] = 0;
	for (int i = 0; i < n; ++i) {
		int my = coord(a[i]);
		int best = query(my-1)+1;
		insert(my, best);
		if (i != n-1) ckmax(ans, best + 1 + best_right[i]);
	}
	cout << ans << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
