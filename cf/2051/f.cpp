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
	int n, m, q; cin >> n >> m >> q;
	vector<int> a(q);
	for (auto& x : a) cin >> x;
	// preciso manter a borda direita e esquerda de onde o joker pode estar (sempre eh contiguo)
	ii range = {m, m};
	int bl = 0, br = n+1, no = 0;
	for (int i = 0; i < q; ++i) {
		auto& [x, y] = range;
		bool add = 0;
		if (no == 0) {
			if (x <= a[i] and a[i] <= y) add = 1;
			else if (a[i] < x) x--;
			else y++;
		}
		if (bl and a[i] > bl) bl++;
		if (br != n+1 and a[i] < br) br--;
		if (add) {
			if (x == y) no = 1;
			ckmax(bl, 1);
			ckmin(br, n);
		}
		if (no == 0) {
			int ans = y-x+1;
			if (bl != 0) ans += min(bl, x-1);
			if (br != n+1) ans += n - max(br, y+1) + 1;
			cout << ans << ' ';
		} else {
			int ans = bl + (n - max(br, bl+1) + 1);
			cout << ans << ' ';
		}
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
