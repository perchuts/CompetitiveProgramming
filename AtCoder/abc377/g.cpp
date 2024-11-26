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

// String Hashing
//
// Complexidades:
// construtor - O(|s|)
// operator() - O(1)

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
int uniform(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
 
int P;
struct str_hash { // 116fcb
	int MOD;
	vector<ll> h, p;
	str_hash(string s, int m) : h(s.size()), p(s.size()) {
		MOD = m;
		p[0] = 1, h[0] = s[0];
		for (int i = 1; i < s.size(); i++)
			p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
	}
	ll operator()(int l, int r) { // retorna hash s[l...r]
		ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
		return hash < 0 ? hash + MOD : hash;
	}
};

																//
void solve(){
	int n; cin >> n;
	int mods = 20;
	vector<int> m(mods);
	P = uniform(256, inf-421); // l > |sigma|
	for (auto& x : m) x = uniform(998244353, inf);
	map<vector<int>, int> mp;
	auto add = [&] (string s) {
		int tam = s.size();
		vector<vector<int>> cur(tam, vector<int>(mods));
		for (int i = 0; i < mods; ++i) {
			str_hash hsh(s, m[i]);
			for (int j = 0; j < tam; ++j) cur[j][i] = hsh(0, j);
		}
		for (int j = 0; j < tam; ++j) {
			if (mp.count(cur[j])) ckmin(mp[cur[j]], tam);
			else mp[cur[j]] = tam;
		}
	};
	auto get = [&] (string s) {
		int tam = s.size();
		vector<vector<int>> cur(tam, vector<int>(mods));
		for (int i = 0; i < mods; ++i) {
			str_hash hsh(s, m[i]);
			for (int j = 0; j < tam; ++j) cur[j][i] = hsh(0, j);
		}
		return cur;
	};
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		auto cur = get(s);
		int ans = sz(s);
		for (int j = 0; j < sz(s); ++j) {
			if (mp.count(cur[j])) {
				ckmin(ans, sz(s)-1-j+mp[cur[j]]-j-1);
			}
		}
		cout << ans << endl;
		add(s);
	}

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
