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
	int n, s = 0; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x, s += x;
	if (n % 2) {
		if (s % n) {
			cout << "No" << endl;
			return;
		}
	} else {
		if (s % n != 0 and s % n != n/2) {
			cout << "No" << endl;
			return;
		}	
	}
	vector<vector<int>> ans;
	if (s % n) {
		vector<int> temp(n);
		iota(all(temp), 1);
		for (int i = 0; i < n; ++i) v[i] += i+1;
		ans.pb(temp);	
		s += (n+1) * n / 2;
	}
	auto add = [&] (int a, int b) {
		vector<int> v1, v2;
		int cur = 3;
		for (int i = 0; i < n; ++i) {
			if (i != a and i != b) v1.pb(cur++);
			else if (i == a) v1.pb(1);
			else v1.pb(2);
		}
		cur = n-2;
		for (int i = 0; i < n; ++i) {
			if (i != a and i != b) v2.pb(cur--);
			else if (i == a) v2.pb(n-1);
			else v2.pb(n);
			v[i] += v1[i] + v2[i];
		}
		ans.pb(v1), ans.pb(v2);
	};
	int med = s / n;
	vector<int> V = v;
	while (true) {
		int high = -1, low = -1;
		for (int i = 0; i < n; ++i) {
			if (V[i] > med) high = i;
			if (V[i] < med) low = i;
		}
		if (high == -1) {
			assert(low == -1);
			break;
		}
		V[high]--, V[low]++;
		add(high, low);
	}
	cout << "Yes" << endl;
	cout << sz(ans) << endl;
	for (auto x : ans) {
		for (auto y : x) cout << y << " ";
		cout << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
