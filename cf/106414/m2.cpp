#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

string solve(int n, int k, int x, int y) {
    if (x == y) return string(k, '0');
    if (x > y) swap(x, y);
    string s(k, '0');
    map<int, int> mp;
    auto solve = [&] (auto&& self, int D) -> int {
        if (mp.count(D)) return mp[D];
        if (D == 0) return 1;
        int tot = 0;
        if (D & 1) {}
        else tot = self(self, D/2);
        if (x <= D and (D & 1) == (x & 1)) tot ^= self(self, (D-x)/2);
        if (y <= D and (D & 1) == (y & 1)) tot ^= self(self, (D-y)/2);
        return mp[D] = tot;
    };
    for (int i = k-y+1; i <= k; ++i) {
        int start;
        if (i + x <= k) start = i + y;
        else start = i;
        int D = n-start;
        if (solve(solve, D)) s[i-1] = '1';
    }
    reverse(begin(s), end(s));
    return s;
}

string brute(int n, int k, int x, int y) {
    vector<int> bichos(n+1);
    for (int i = 1; i <= k; ++i) bichos[i] = (1 << (i-1));
    for (int i = k+1; i <= n; ++i) bichos[i] = bichos[i-x] ^ bichos[i-y];
    string ans;
    for (int i = 0; i < k; ++i) ans += char('0' + (bichos[n]>>i&1));
    reverse(all(ans));
    return ans;
}
// Matriz

#define MODULAR false
template<typename T> struct matrix : vector<vector<T>> {
	int n, m;

	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << (*this)[i][j] << " ";
			cout << endl;
		}
	}

	matrix(int n_, int m_, bool ident = false) :
			vector<vector<T>>(n_, vector<T>(m_, 0)), n(n_), m(m_) {
		if (ident) {
			assert(n == m);
			for (int i = 0; i < n; i++) (*this)[i][i] = 1;
		}
	}
	matrix(const vector<vector<T>>& c) : vector<vector<T>>(c),
		n(c.size()), m(c[0].size()) {}
	matrix(const initializer_list<initializer_list<T>>& c) {
		vector<vector<T>> val;
		for (auto& i : c) val.push_back(i);
		*this = matrix(val);
	}

	matrix<T> operator*(matrix<T>& r) {
		assert(m == r.n);
		matrix<T> M(n, r.m);
		for (int i = 0; i < n; i++) for (int k = 0; k < m; k++)
			for (int j = 0; j < r.m; j++) {
				T add = (*this)[i][k] * r[k][j];
#if MODULAR
#warning Usar matrix<ll> e soh colocar valores em [0, MOD) na matriz!
				M[i][j] += add%MOD;
				if (M[i][j] >= MOD) M[i][j] -= MOD;
#else
				M[i][j] += add;
#endif
			}
		return M;
	}
	matrix<T> operator^(ll e){
		matrix<T> M(n, n, true), at = *this;
		while (e) {
			if (e&1) M = M*at;
			e >>= 1;
			at = at*at;
		}
		return M;
	}
	void apply_transform(matrix M, ll e){
		auto& v = *this;
		while (e) {
			if (e&1) v = M*v;
			e >>= 1;
			M = M*M;
		}
	}
};
int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k, x, y; cin >> n >> k >> x >> y;
        matrix<int> id(k+1, k+1, true), M(k+1, k+1);
        M[x][0] = M[y][0] = 1;
        for (int i = 1; i <= k; ++i) M[i-1][i] = 1;
        auto tmp = M;
        for (int i = 1; i <= n; ++i) {
            M.print();
            M = M * tmp;
            for (auto& aa : M) for (auto& bb : aa) bb %= 2;
            cout << endl;
            if (M == tmp) {
                cout << "done! i = " << i << endl;
            }
        }
        //cout << solve(n, k, x, y) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 10), k = rnd(1, n-1), x = rnd(1, k), y = rnd(1, k);
        string my = solve(n, k, x, y);
        string ans = brute(n, k, x, y);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << " " << x << " " << y << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
