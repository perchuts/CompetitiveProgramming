#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

void solve(){
 	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	vector<vector<iii>> ans(n+1);
	for (int i = n - 1; i >= 0; --i) {
		int cur_a = a[i], cur_b = b[i], cur_fim = i;
		for (auto [val_a, val_b, fim] : ans[i+1]) {
			int nb = gcd(cur_b, val_b), na = gcd(cur_a, val_a);
			if (nb != cur_b or na != cur_a) ans[i].pb({cur_a, cur_b, cur_fim});
			cur_b = nb, cur_a = na, cur_fim = fim;
		}
		ans[i].pb({cur_a, cur_b, cur_fim});
	}
	vector<iii> suffix;
	int ca = 0, cb = 0;
	suffix.pb({0, 0, n});
	for (int i = n-1; i >= 0; --i) {
		int na = gcd(ca, a[i]), nb = gcd(cb, b[i]);
		if (na != ca or nb != cb) {
			ca = na, cb = nb;
			suffix.pb({ca, cb, i});
		}
	}
	reverse(all(suffix));
	int mx = 0, pre_a = 0, pre_b = 0, j_s = 0;
	ll qnt_ans = 0;
	for (int i = 0; i < n; ++i) {
		if (get<2>(suffix[j_s]) <= i) j_s++;	
		int j = j_s, k = 0, id = i;
		while (k != sz(ans[i])) {
			auto [x1, x2, x3] = ans[i][k];
			auto [y1, y2, y3] = suffix[j];
			if (y3 <= id) { j++; continue; }	
			int lim = min(x3, y3-1);
			int ga = gcd(gcd(x2, pre_a), y1);
			int gb = gcd(gcd(x1, pre_b), y2);
			int val = ga+gb;
			if (ckmax(mx, val)) qnt_ans = lim-id+1;
			else if (mx == val) qnt_ans += lim-id+1;
			id = lim+1;
			if (lim == x3) k++;
		}
		pre_a = gcd(pre_a, a[i]), pre_b = gcd(pre_b, b[i]);
	}
	cout << mx << ' ' << qnt_ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
