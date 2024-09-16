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
 	int n, l; cin >> n >> l;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	int used = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 2) {
			if (used > l-2) {
				cout << "No" << endl;
				exit(0);
			}
			used += 3;
		} else used += 2;
	}
	cout << "Yes" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}