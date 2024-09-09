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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

struct matrix {
	int n, m;
	vector<vector<int>> v;
	matrix(int n_, int m_, int flag = 1) : n(n_), m(m_), v(vector<vector<int>>(n_, vector<int>(m_, 0))) {
		for (int i = 0; i < n; ++i) v[i][i] = flag;
	}
	matrix operator * (matrix const& other) {
		matrix res(n, m, 0);
		assert(other.n == m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < other.m; ++j) {
				for (int k = 0; k < m; ++k) {
					res.v[i][j] = (res.v[i][j] + v[i][k] * other.v[k][j]) % mod; 
				}
			}
		}
		return res;
	};
};


void solve(){
 	int n, q; cin >> n >> q;
	vector<int> a(1<<n);
	for (auto& x : a) cin >> x;
	vector queries(n, vector<int>());
	while (q--) {
		int x, y; cin >> x >> y;
		queries[x].pb(y);
	}
	vector op = vector<matrix>(2, matrix(2, 2));
	op[0] = op[1] = matrix(2, 2);
	op[0].v[1][0] = op[1].v[0][1] = 1;
	for (int i = 0; i < n; ++i) {
		matrix mult(2, 2);
		for (auto val : queries[i]) mult = op[val] * mult;
		for (int j = 0; j < (1 << n); ++j) {
			if ((j >> i) & 1) {
				int k = j - (1 << i);
				int new_k = (a[k] * mult.v[0][0] + a[j] * mult.v[0][1]) % mod; 
				int new_j = (a[k] * mult.v[1][0] + a[j] * mult.v[1][1]) % mod; 
				a[j] = new_j, a[k] = new_k;
			}
		}
	}
	for (auto x : a) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
