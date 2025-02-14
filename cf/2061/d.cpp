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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, m; cin >> n >> m;
	vector<int> a(n), b(m);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	sort(all(a)), sort(all(b));
	int pt = 0;
	multiset<int> valid;
	for (int i = 0; i < m; ++i) {
		while (pt < n and a[pt] <= b[i]) valid.insert(a[pt++]);
		if (valid.find(b[i]) != end(valid)) {
			valid.erase(valid.find(b[i]));
			continue;
		}
		if (valid.empty()) {
			cout << "No" << endl;
			return;
		}
		auto x = *begin(valid);
		if (b[i] < 2 * x) {
			cout << "No" << endl;
		}
		
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
