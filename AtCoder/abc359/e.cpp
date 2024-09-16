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
	int ans = 0;
	stack<ii> st;
	int x; cin >> x;
	st.push({x, 1});
	cout << x + 1 << ' ';
	ans = x;
	for (int i = 0; i < n-1; ++i) {
		cin >> x;
		int tot = 1;
		while (!st.empty() && st.top().first <= x) {
			auto [hh, qt] = st.top();
			st.pop();
			ans += (x-hh) * qt;
			tot += qt;
		}
		st.push({x, tot});
		ans += x;
		cout << ans + 1 << ' ';
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}