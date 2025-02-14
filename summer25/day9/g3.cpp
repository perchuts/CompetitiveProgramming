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
	int n; cin >> n;
	vector<int> nim(n+1);
	vector<vector<int>> can(n+1, vector<int>(512));
	int mx = 0, ss = 0;
	for (int i = 3; i <= n; ++i) {
		int cnt = 0;
		for (int j = 0; ; ++j) if (can[i][j] == 0) { nim[i] = j; break; }
		for (int j = 1; i+j <= min(2*i-1, n); ++j) {
			int nn = nim[i] ^ nim[j];
			if (can[i+j][nn] == 0) can[i+j][nn] = 1, cnt++;
		}
		ckmax(mx, cnt);
		ss += cnt;
		cout << i << endl;
		cout.flush();
	}
	cout << mx << endl;
	cout << ss << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
