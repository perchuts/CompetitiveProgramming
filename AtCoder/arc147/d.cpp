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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int n, m, tot;

void solve(int id, int initial, vector<int> changes){
	if (id == n-1) {
		vector<int> cur;
		vector<int> freq(m);
		for (int i = 0; i < n; ++i) {
			cur.clear();
			for (int j = 0; j < m; ++j) if ((initial>>j)&1) cur.pb(j+1), freq[j]++;
			cout << "{";
			for (int j = 0; j < sz(cur); ++j) cout << cur[j] << ",";
			cout << "}" << endl;
			if (i != n-1) initial ^= (1 << changes[i]);
		}
		int ans = 1;
		for (int i = 0; i < m; ++i) ans *= freq[i];
		cout << "Score: " << ans << endl;
		tot += ans;
		return;
	}
	for (int i = 0; i < m; ++i) {
		changes.push_back(i);
		solve(id+1, initial, changes);
		changes.pop_back();
	}
}

int32_t main(){_
	cin >> n >> m;
	int ans = 1;
	for (int i = 1; i <= m; ++i) ans = ans * n % mod;
	for (int i = 1; i < n; ++i) ans = ans * m % mod;
	cout << ans << endl;
}
