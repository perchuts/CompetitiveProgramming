#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


template<typename T> struct matrix : vector<vector<T>> {
	int n, m;

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
				M[i][j] += add%MOD;
				if (M[i][j] >= MOD) M[i][j] -= MOD;
#else
				M[i][j] += add;
#endif
			}
		return M;
	}
};

string solve(int k, vector<string>& ops, ll N, string& t) {
    int n = sz(t);
    string resp(n, 'a');
    auto get = [&] (int a, int b) { for (int i = 0; i < n; ++i) resp[(b*i+a+n)%n] = t[i]; };
    auto compose = [&] (ii x, ii y) { return make_pair((x.first + x.second*y.first + n)%n, x.second*y.second); };
    vector<int> a(k+2), e(k+2);
    for (int i = 1; i <= k; ++i) {
        int A = 0, E = 1;
        for (auto c : ops[i-1]) {
            if (c == 'a') A += n - 1;
            else E *= -1, A = -A + 2*n - 1;
            if (A >= n) A -= n;
        }
         a[i] = A, e[i] = E;
    }
    a[k+1] = a[k], e[k+1] = e[k];
    for (int i = k-1; i; --i) {
        auto [aa, bb] = compose({a[i], e[i]}, {a[k+1], e[k+1]});
        a[k+1] = aa, e[k+1] = bb;
    }
    if (N <= k+1) {
        get(a[N], e[N]);
        return resp;
    }
    e[0] = e[k+1];
    vector<ll> helper(k+1);
    auto multi = [&] (matrix<ll> &M, int p) {
        int c0 = (n - e[p]) % n;
        int ck = (e[p] + e[(p-1+k+1)%(k+1)] * e[p] + n) % n;
        for (int i = 0; i <= k; ++i) helper[i] = (M[0][i] * c0 + M[k][i] * ck) % n;
        rotate(begin(M), begin(M)+1, end(M));
        swap(M[k], helper);
    };
    matrix<ll> P(k+1, k+1, 1); 
    multi(P, 1); 
    for (int i = 0; i < k; ++i) multi(P, (1+1+i)%(k+1));
    ll need = (N - k - 1) / (k + 1);
    matrix<ll> Z(k+1, k+1, 1);
    while (need) {
        if (need & 1) {
            Z = Z * P;
            for (auto& x : Z) for (auto& y : x) y %= n;
        }
        need /= 2, P = P * P;
        for (auto& x : P) for (auto& y : x) y %= n;
    }
    ll current = N / (k + 1) * (k + 1) + 1;
    while (current <= N) multi(Z, (current++)%(k+1));
    int aN = 0;
    for (int i = 1; i <= k+1; ++i) aN = (aN + Z[k][i-1] * a[i]) % n;
    get(aN, e[N%(k+1)]);
    return resp;
}

int32_t main() {_
#ifndef gato
    int k; ll N;
    string t; 
    cin >> k;
    vector<string> ops(k);
    for (auto& s : ops) cin >> s;
    cin >> N >> t;
    cout << solve(k, ops, N, t) << endl;
#else
    int T = 1;
    while (true) {
        int k = rnd(1, 30);
        vector<string> ops(k);
        for (auto& s : ops) {
            s = string(rnd(1, 30), 'a');
            for (auto& x : s) if (rnd(0, 2) == 1) x = 'b';
        }
        int N = rnd(1, 15285);
        string t(rnd(1, 215), 'a');
        for (auto& x : t) x = char('a' + rnd(0, 1));
        string my = solve(k, ops, N, t);
        string ans = brute(k, ops, N, t);
        if (my != ans) {
            cout << "Wrong answer on test " << T << endl;
            cout << k << endl;
            for (auto x : ops) cout << x << endl;
            cout << N << endl;
            cout << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << T++ << endl;
    }
#endif
}

