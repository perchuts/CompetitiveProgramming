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
	int n, k; cin >> n >> k;
	if (2 * k > n) {
		cout << -1 << endl;
		return;
	}
	vector<int> p(n, -1);
	int i = 0;
	while (4 * k <= n - i) {
		for (int j = i; j < i + k; ++j) p[j] = j + k;
		for (int j = i + k; j < i + 2 * k; ++j) p[j] = j - k;
		i += 2 * k;
	}
	int x = n % (2*k);
	if (x > k) {
		for (int j = i; j < i + k; ++j) p[j] = j + k;
		for (int j = i + k; j < i + x; ++j) p[j] = j-k;
		for (int j = i + x; j < n - k; ++j) p[j] = j+k;
		int pt = p[i+x-1]+1; 
		for (int j = n - k; j < n; ++j) {
			if (pt == p[i]) pt += k;
			p[j] = pt++;
		}	
	} else {
		for (int j = i; j < n - k; ++j) p[j] = (j + k);
		for (int j = n - k; j < n; ++j) p[j] = i + j - n + k;
	}
	for (auto z : p) cout << z + 1 << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

