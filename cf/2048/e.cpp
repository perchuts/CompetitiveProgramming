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
	int n, m; cin >> n >> m;
	if (m >= 2*n) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	vector<vector<int>> ans(2*n, vector<int>(m));
	// os primeiros m caras vao ser so caras do matching 1 - 2, 3 - 4, ..., (2n-1) - 2n
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < min(n, m); ++j) {
			// nessa rodada, o j-esimo cara vai pegar a aresta (i + j) mod n
			int edg = (i + j) % n;
			int x = 2*edg, y = 2*edg+1;
			ans[x][j] = ans[y][j] = i+1;
		}
	}
	// agora comeco no m
	for (int i = 0; i < n; ++i) {
		for (int j = n; j < m; ++j) {
			int edg = (i + j) % n;
			int x = 2*edg, y = (2*edg+3)%(2*n);
			ans[x][j] = ans[y][j] = i+1;
		}
	}
	for (auto x : ans) {
		for (auto y : x) cout << y << ' ';
		cout << endl;
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
