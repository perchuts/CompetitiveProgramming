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
const int maxn = 5e6 + 100;
const int mod = 1e9+7;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int trie[maxn][11];

void solve(){
	ll n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	ll ans = 0;
	auto get_digits = [&] (int x) {
		vector<int> d;
		for (int i = 0; i < 15; ++i) d.pb(x % 10), x /= 10;
		reverse(all(d));
		return d;
	};		
	vector<vector<int>> digits(n);
	for (int i = 0; i < n; ++i) {
		digits[i] = get_digits(a[i]);	
		for (auto x : digits[i]) ans += x;
	}
	ans *= n;
	for (int d = 0; d < 15; ++d) {
		int cur = 0;
		for (int k = 0; k < n; ++k) {
			for (int i = d; i < 15; ++i) {
					if (trie[cur][digits[k][i]] == 0) trie[cur][digits[k][i]] = ++cur;
					cur = trie[cur][digits[k][i]];
					trie[cur][10]++;
			}
		}

		for (int k = 0; k < n; ++k) {
			for (int ini_d = 9-digits[i][d]+1; ini_d < 10; ++ini_d) {
				int cur = 0;
				if (trie[cur][ini_d] == 0) continue;
				cur = trie[cur][ini_d];
				for (int w = d+1; w < 15; ++w) {
					
				}
			}
			for (int i = d; i < 15; ++i) {
					if (trie[cur][digits[k][i]] == 0) trie[cur][digits[k][i]] = ++cur;
					cur = trie[cur][digits[k][i]];
					trie[cur][10]++;
			}
		}
		for (int i = 0; i < cur; ++i) {
			for (int j = 0; j <= 10; ++j) trie[i][j] = 0;
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
