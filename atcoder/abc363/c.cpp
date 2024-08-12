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

void solve() {
	int n, k; cin >> n >> k;
	vector<int> p(n);
	iota(all(p), 0);
	string s; cin >> s;
	unordered_map<string, int> nice;
	do {
		bool ok = 1;
		string s2;
		for (int i = 0; i < n; ++i) s2 += s[p[i]];
		for (int i = 0; i + k <= n; ++i) {
			bool pal = 1;
			for (int j = 0; j < k; ++j) {
				pal &= (s[p[i+j]] == s[p[i+k-1-j]]);
			}
			ok &= (!pal);
			if (!ok) break;
		}
		if (ok) nice[s2] = 1;
	} while (next_permutation(all(p)));
	cout << sz(nice) << endl;
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
