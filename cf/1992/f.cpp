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
vector<int> divs[maxn];
int structure[maxn];
void solve(){
	int n, x; cin >> n >> x;
	vector<int> a(n);
	for (auto z : divs[x]) structure[z] = 0;
	structure[1] = 1;
	int ans = 1, i = 0;
	for (auto& y : a) {
		cin >> y;
		if (x % y) continue;
		for (auto z : divs[x]) {
			if (z % y == 0) structure[z] |= structure[z/y];
		}
		if (structure[x] == 1) {
			for (auto z : divs[x]) structure[z] = 0;
			structure[1] = structure[y] = 1;
			ans++;
		}
		i++;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  for (int i = 1; i <= 1e5; ++i) {
		for (int j = i; j <= 1e5; j += i) divs[j].pb(i);
  }
  for (int i = 1; i <= 1e5; ++i) reverse(all(divs[i]));
  while(t--) solve();
}
