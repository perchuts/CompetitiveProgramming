#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

struct matrix {
	int n;
	vector<vector<int>> m;
	matrix() {}
	matrix(int n_) {
		n = n_;
		m = vector<vector<int>>(n, vector<int>(n));
	}
	matrix operator*(const matrix& other) const {
		matrix ans = matrix(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) ans.m[i][j] = (ans.m[i][j] + m[i][k] * other.m[k][j]) % mod; 
			}
		}
		return ans;
	}
	void print() {
		for (auto x : m) {
			for (auto y : x) cout << y << ' ';
			cout << endl;
		}
		cout << endl;
	}
};


void solve(){
 	int n, m; cin >> n >> m;
	const int bits = 60;
	const int tam = 100;
	vector<vector<int>> obj(bits+1, vector<int>(tam + 1));
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b;
		obj[b][a]++;
	}
	for (int i = 1; i <= bits; ++i) for (int j = 1; j <= tam; ++j) obj[i][j] += obj[i-1][j];
	vector<matrix> M(bits+1), mi(bits+1);
	M[0] = matrix(tam);
	for (int i = 0; i < tam; ++i) M[0].m[i][i] = 1;
	for (int i = 1; i <= bits; ++i) {
		mi[i] = matrix(tam);
		for (int j = 0; j < tam; ++j) mi[i].m[0][j] = obj[i-1][j+1];
		for (int j = 1; j < tam; ++j) mi[i].m[j][j-1] = 1;
		M[i] = M[i-1] * mi[i] * M[i-1];	
	}
	auto solve = [&] (int N) {
		matrix ans = M[0];
		for (int i = bits-1; i >= 0; --i) {
			if ((N >> i) & 1) ans = mi[i+1] * M[i] * ans;	
		}
		return ans.m[0][0];
	};
	cout << solve(n) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
