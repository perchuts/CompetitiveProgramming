#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull

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

int qtd(vector<int> v) {
	int n = sz(v), ans = 0;
	for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) ans += (v[i] > v[j]);
	return ans;
}

int solve(int n, int k){
	int C;
	if (n >= 1000) C = 8;
	else if (n <= 61) C = 200;
	else C = 20;
	vector<vector<int>> ways(n+1, vector<int>(C+1));
	ways[0][0] = 1;
	for (int i = 1; i <= n; ++i) for (int j = 0; j <= min(C, i-1); ++j) for (int w = 0; w + j <= C; ++w) ways[i][w+j] = min(ways[i][w+j] + ways[i-1][w], k+1);
	int I = 0;
	while (k > ways[n][I]) k -= ways[n][I++];
	vector<int> ans(n), can;
	for (int i = 0; i < min(I+5, n); ++i) can.pb(i);
	for (int i = 1; i <= n; ++i) {
		int j = 0;
		while (k > ways[n-i][I-j]) k -= ways[n-i][I-j], j++;
		ans[i-1] = can[j], I -= j;
		can.erase(begin(can)+j);
		if (!can.empty() and can.back() < n-1) can.push_back(can.back()+1);
	}
	for (auto x : ans) cout << x+1 << ' ';
	cout << endl;
	return I; 
}

int32_t main(){_
	int n, k; cin >> n >> k;
	solve(n, k);
}
