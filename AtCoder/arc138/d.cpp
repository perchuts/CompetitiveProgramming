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
	if (k % 2 == 0) {
		cout << "No" << endl;
		exit(0);
	}
	if (n == k) {
		if (n != 1) cout << "No" << endl;
		else cout << "Yes\n 0 1" << endl;
		exit(0);
	}
	bool flag = false;
	if (k == 1) k = n - 1, flag = true;
	vector<int> model(1<<(k+1));
	for (int i = 0; i < (1 << (k + 1)); ++i) model[i] = i^(i>>1);
	if (flag) {
		cout << "Yes" << endl;
		for (auto x : model) cout << x << ' ';
		cout << endl;
		exit(0);
	}
	for (int i = 0; i < (1 << (k + 1)); i += 2) model[i] ^= ((1 << (k+1))-1);
	auto ans = model;
	auto printAns = [&] (vector<int> v) {
		for (auto x : v) cout << x << ' ';
		cout << endl;
		//for (int i = 0; i < sz(v); ++i) cout << __builtin_popcount(v[i]^v[(i+1)%sz(v)]) << ' ';
		//cout << endl;
	};
	for (int bit = k + 1; bit < n; ++bit) {
		int N = sz(ans), A = -1;
		for (int j = 0; j < N; ++j) {
			int a = ans[j], b = ans[(j+1)%N];
			int x = (a^ans[1]), y = (b^ans[0]);
			if (__builtin_popcount(x) == k-1 && __builtin_popcount(y) == k-1) A = (j+1)%N;
		}
		assert(A != -1);
		vector<int> new_ans = {ans[0]};
		for (int i = 0; i < N; ++i) new_ans.pb(ans[(A+i)%N]+(1<<bit));
		for (int i = 1; i < N; ++i) new_ans.pb(ans[i]);
		swap(new_ans, ans);
	}
	cout << "Yes" << endl;
	printAns(ans);
	//for (auto x : ans) cout << x << ' ';
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
