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
	string s, t; cin >> s >> t;
	int n = sz(s);
	if (sz(t) != n) {
		cout << -1 << endl;
		return;
	}
	if (true) {
		int x = 0, y = 0;
		for (int i = 0; i < n; ++i) {
			x += (s[i] == '1' ? 1 : -1);
			y += (t[i] == '1' ? 1 : -1);
		}
		if (x != y) {
			cout << -1 << endl;
			return;
		}
	}
	int ops = 0;
	vector<int> bl = {1}, bt = bl;
	for (int i = 1; i < n; ++i) {
		if (s[i] != s[i-1]) bl.pb(1);
		else bl.back()++;
		if (t[i] != t[i-1]) bt.pb(1);
		else bt.back()++;
	}
	if (s == t) {
		cout << 0 << endl;
		return;
	}
	if (sz(bl) < sz(bt)) {
		cout << -1 << endl;
		return;
	}
	if (sz(bl) == sz(bt) && sz(bl) == 1) {
		cout << -1 << endl;
		return;
	}
	assert(sz(bl) > 1);
	reverse(all(bl));
	if (s[0] != t[0]) {
		int x = bl.back();
		bl.pop_back();
		int y = bl.back();
		bl.pop_back();
		if (!bl.empty()) bl.back() += x, bl.pb(y);
		else bl.pb(x), bl.pb(y);
		ops++;
	}
	for (int i = 0; i < sz(bt); ++i) {
		while (sz(bl) > 2 and bl.back() < bt[i]) {
			int x = bl.back();
			bl.pop_back();
			int y = bl.back();
			bl.pop_back();
			if (sz(bl) == 1) {
				bl.back() += x;
				bl.pb(y);
				swap(bl[0], bl[1]);

			} else {
				bl.back() += x;
				bl[sz(bl)-2] += y;
			}
			ops++;
		}
		if (bl.back() != bt[i]) {
			cout << -1 << endl;
			return;
		}
		bl.pop_back();
	}
	cout << ops << endl;
}

int32_t main(){_
	int t = 1; cin >> t;
	while(t--) solve();
}
