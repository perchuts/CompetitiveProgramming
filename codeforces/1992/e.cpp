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

void solve(){
 	int n; cin >> n;
	vector<ii> ans;
	int lg = 0, tmp = n;
	vector<int> vals;
	while (tmp) lg++, vals.pb(tmp%10), tmp /= 10;
	reverse(all(vals));
	for (int a = 1; a <= 10000; ++a) {
		int tam = lg * a;
		for (int j = 1; j <= min(7ll, tam-1); ++j) {
			int b = tam - j, acur = 0;
			for (int k = 0; k < j; ++k) acur = 10 * acur + vals[k%lg];
			if (a * n - b == acur) ans.pb({a, b});
		}
	}
	cout << sz(ans) << endl;
	for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
