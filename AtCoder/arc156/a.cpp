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
	string s; cin >> s;
	int c = 0, adj = 0;
	for (int i = 0; i < n; ++i) {
		c += (s[i] == '1');
		if (i != n-1 && s[i] == s[i+1] && s[i] == '1') adj = 1;
	}
	if (c&1) cout << -1 << endl;
	else if (c == 2 && adj == 1) {
		if (s == "110" or s == "011") cout << -1 << endl;
		else if (s == "0110") cout << 3 << endl;
		else cout << 2 << endl;
	}
	else cout << c/2 << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
