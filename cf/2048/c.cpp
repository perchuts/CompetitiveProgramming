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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

iii trie[5000*2500+100];

void solve(){
	string s; cin >> s;
	int n = sz(s);
	auto& [a, b, c] = trie[0];
	c = 0;
	int h = 0;
	for (int i = n-1; i >= 0; --i) {
		int cur = 0;
		for (int j = i; j < n; ++j) {
			auto& [zero, um, mx] = trie[cur];
			if (s[j] == '0') {
				if (zero == 0) {
					zero = ++h;
				}
				cur = zero;
			} else {
				if (um == 0) {
					um = ++h;
				}
				cur = um;
			}
			auto& [z2, u2, mx2] = trie[cur];
			mx2 = i;
		}
	}
	string ans = "0";
	ii p;
	for (int tam = 1; tam < n; ++tam) {
		// quero ir ate tam
		int cur = 0;
		string ss;
		for (int j = 0; j < n-tam; ++j) ss += s[j];
		for (int j = 0; j < tam; ++j) {
			int my_val = s[n-tam+j] - '0';
			auto [zero, um, mx] = trie[cur];
			assert(mx <= n-tam);
			if (my_val == 1) {
				// quero zero
				if (zero != 0 and get<2>(trie[zero]) <= n-tam) cur = zero, ss += '1';
				else cur = um, ss += '0';
			} else {
				// quero um
				if (um != 0 and get<2>(trie[um]) <= n-tam) cur = um, ss += '1';
				else cur = zero, ss += '0';
			}
		}
		auto [zero, um, mx] = trie[cur];
		if (tam == 1) {
			ans = ss;
			p = {mx, mx};
		}
		else {
			if (ckmax(ans, ss)) p = {mx, mx+tam-1};
		}
	}
	for (int i = 0; i <= h; ++i) trie[i] = {0, 0, 0};
	cout << 1 << ' ' << n << " " << p.first + 1 << ' ' << p.second + 1 << endl;
}		


int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
