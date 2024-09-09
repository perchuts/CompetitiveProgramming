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

void solve() {
	int n; cin >> n;
	int x, y, z; cin >> x >> y >> z;
	vector<int> A(n);
	vector<int> freq(n);
	for (auto &i : A) {
		cin >> i;
		freq[i]++;
	}
	vector<int> ans(n, 0);
	string ops;
	vector<int> pos;

	auto make_op = [&] (char op, int i) {
		freq[i]--;
		if (op == '&') x--;
		if (op == '|') y--;
		if (op == '^') z--;
		ops += op;
		pos.push_back(i);
	};

	for (int i = n - 1; i >= 0; --i) {
		if (freq[i] > 0 && freq[i] % 2 == 0 && x > 0) {
			make_op('&', i);
		}
	}

	for (int i = n - 1; i >= 0; --i) {
		while (freq[i] >= 3 && x >= 2) {
			make_op('&', i);
			make_op('&', i);
		}
	}

	for (int i = 0; i < n; i++) {
		if (freq[i] >= 3 && x == 1) {
			make_op('&', i);
		}
	}

	for (int i = 0; i < n; i++) {
		if (freq[i] && x >= 1) {
			make_op('&', i);
		}
	}

	for (int i = 0; i < n; i++) {
		if (freq[i] % 2 == 1) {
			ans[i] = true;
			while (freq[i] > 0 && z > 0) {
				make_op('^', i);
			}
		} else {
			while (freq[i] > 1 && z > 0)
				make_op('^', i);
		}
	}

	for (int i = 0; i < n; i++) {
		if (freq[i] > 0 && z > 0)
			make_op('^', i);
	}

	for (int i = 0; i < n; i++) {
		while (freq[i] > 0 && y > 0) {
			ans[i] = true;
			make_op('|', i);
		}
	}

	assert(x == 0);
	assert(y == 0);
	assert(z == 0);

	for (int i = 0; i < n; i++) cout << ans[n-i-1];
	cout << endl;
	cout << ops << endl;
	for (int i = 0; i < n; i++) cout << pos[i] << " ";
	cout << endl;
}

int32_t main(){ _
  int t = 1; cin >> t;
  while(t--) solve();
}
