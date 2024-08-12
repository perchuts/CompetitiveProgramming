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
	vector<int> v(n);
	for (int i = 0; i < n; ++i) v[i] = (s[i] == 'p');
	vector<int> ans = v;
	int st = 0;
	while (st < n && v[st] == 0) st++;
	vector<char> mp = {'d', 'p'};
	if (st == n) {
		for (auto x : ans) cout << mp[x]; 
		return;
	}
	vector<ii> test;
	for (int i = st+1; i < n; ++i) {
		if (v[i] == 0 && v[i-1] == 1) test.pb({st, i-1});	
	}
	if (v.back() == 1) test.pb({st, n-1});
	for (auto [x, y] : test) {
		vector<int> v2 = v;
		for (int i = x; i <= y; ++i) v2[i] = (v[y-i+x]^1);
		ckmin(ans, v2);
	}
	for (auto x : ans) cout << mp[x];
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
