#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	int n, q; cin >> n >> q;
	string s; cin >> s;
	vector<vector<int>> ps(3, vector<int>(n+1));
	for (int i = 1; i <= n; ++i) {
		ps[0][i] = ps[0][i-1] + (s[i-1] == '/');
		ps[1][i] = ps[1][i-1] + (s[i-1] == '1');
		ps[2][i] = ps[2][i-1] + (s[i-1] == '2');
	}
	while (q--) {
		int lx, rx; cin >> lx >> rx;
		int l = 1, r = n, ans = (ps[0][rx]-ps[0][lx-1] >= 1);
		while (l <= r) {
			int md = l + (r-l+1)/2;
			int a = lx, b = rx, c = -1, d = -1;
			while (a <= b) {
				int md1 = a + (b-a+1)/2;
				if (ps[1][md1] - ps[1][lx-1] >= md) c = md1, b = md1-1;
				else a = md1+1;
			}
			a = lx, b = rx;
			while (a <= b) {
				int md1 = a + (b-a+1)/2;
				if (ps[2][rx] - ps[2][md1-1] >= md) d = md1, a = md1+1;
				else b = md1-1;
			}
			if (min(c, d) == -1 or ps[0][d-1] - ps[0][c] <= 0) r = md-1;
			else l = md+1, ans = 2*md+1;
		}
		cout << ans << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
