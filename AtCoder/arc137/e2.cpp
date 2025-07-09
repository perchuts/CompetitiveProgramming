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
// Simplex
//
// Maximiza c^T x s.t. Ax <= b, x >= 0
//
// O(2^n), porem executa em O(n^3) no caso medio

const double eps = 1e-7;

namespace Simplex {
	vector<vector<double>> T;
	int n, m;
	vector<int> X, Y;

	void pivot(int x, int y) {
		swap(X[y], Y[x-1]);
		for (int i = 0; i <= m; i++) if (i != y) T[x][i] /= T[x][y];
		T[x][y] = 1/T[x][y];
		for (int i = 0; i <= n; i++) if (i != x and abs(T[i][y]) > eps) {
			for (int j = 0; j <= m; j++) if (j != y) T[i][j] -= T[i][y] * T[x][j];
			T[i][y] = -T[i][y] * T[x][y];
		}
	}

	// Retorna o par (valor maximo, vetor solucao)
	pair<double, vector<double>> simplex(
			vector<vector<double>> A, vector<double> b, vector<double> c) {
		n = b.size(), m = c.size();
		T = vector(n + 1, vector<double>(m + 1));
		X = vector<int>(m);
		Y = vector<int>(n);
		for (int i = 0; i < m; i++) X[i] = i;
		for (int i = 0; i < n; i++) Y[i] = i+m;
		for (int i = 0; i < m; i++) T[0][i] = -c[i];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) T[i+1][j] = A[i][j];
			T[i+1][m] = b[i];
		}
		while (true) {
			int x = -1, y = -1;
			double mn = -eps;
			for (int i = 1; i <= n; i++) if (T[i][m] < mn) mn = T[i][m], x = i;
			if (x < 0) break;
			for (int i = 0; i < m; i++) if (T[x][i] < -eps) { y = i; break; }

			if (y < 0) return {-1e18, {}}; // sem solucao para  Ax <= b
			pivot(x, y);
		}
		while (true) {
			int x = -1, y = -1;
			double mn = -eps;
			for (int i = 0; i < m; i++) if (T[0][i] < mn) mn = T[0][i], y = i;
			if (y < 0) break;
			mn = 1e200;
			for (int i = 1; i <= n; i++) if (T[i][y] > eps and T[i][m] / T[i][y] < mn)
				mn = T[i][m] / T[i][y], x = i;

			if (x < 0) return {1e18, {}}; // c^T x eh ilimitado
			pivot(x, y);
		}
		vector<double> r(m);
		for(int i = 0; i < n; i++) if (Y[i] < m) r[Y[i]] = T[i+1][m];
		return {T[0][m], r};
	}
}
void solve() {
    int n, m, d; cin >> n >> m >> d;
    vector<int> a(n), l(m), r(m), c(m);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < m; ++i) cin >> l[i] >> r[i] >> c[i], --l[i], --r[i]; 
    {
        vector<int> lx, rx, cx;
        for (int i = 0; i < m; ++i) {
            if (d * (r[i] - l[i] + 1) > c[i]) lx.pb(l[i]), rx.pb(r[i]), cx.pb(c[i]);
        }
        l = lx, r = rx, c = cx;
        m = sz(l);
    }
    vector<int> cprime(m); 
    for (int i = 0; i < m; ++i) cprime[i] = d * (r[i] - l[i] + 1) - c[i];
    auto dualdual = [&] () {
        vector<vector<double>> A;
        vector<double> B, C;
        for (int i = 0; i < m; ++i) {
            vector<double> restr(i+1);
            restr[i] = 1;
            A.pb(restr);
            B.pb(1);
            C.pb(-c[i]);
        }
        int cur = m;
        map<ii, int> id; 
        for (int i = 0; i < m; ++i) {
            for (int j = l[i]; j <= r[i]; ++j) {
                vector<double> restr(cur+1);
                restr[cur] = 1, restr[i] = -1;
                id[{i, j}] = cur;
                B.pb(0);
                C.pb(d);
                A.pb(restr);
                cur++;
            }
        }
        for (int i = 0; i < n; ++i) {
            vector<double> restr(cur);
            for (int j = 0; j < m; ++j) {
                if (id[{j, i}]) restr[id[{j, i}]] = 1;
            }
            B.pb(a[i]);
            A.pb(restr);
        }
        for (auto& x : A) x.resize(cur);
        auto [sol, cert] = Simplex::simplex(A, B, C);
        cout << sol << endl;
    };
    //dualdual();
    //exit(0);
    vector<double> C(n+m, -1);
    for (int i = m; i < n+m; ++i) C[i] = -a[i-m];
    vector<vector<double>> A(m+n, vector<double>(n+m));
    vector<double> B(m+n);
    // (normal) -> (dual)
    // 0 <= X[i] <= 1 -> X[i]
    // L[i] <= j <= R[i] : 0 <= Z[i][j] <= X[i] -> Z[i][j]
    // sum_i Z[i][j] <= A[j] -> Y[j]
    // maximize -X[i] * C[i] + D * \sum Z[i][j]
    // dual:
    // -C[i] <= -\sum_j Z[i][j] + X[i] (1)
    // D <= Z[i][j] + Y[j] (2)
    // note que o 2 eh basicamente livre, ent podemos setar Z[i][j] = D - Y[j] (nao ferra (1) diminuir o Z tbm)
    // logo, 1 vira: 
    // -C[i] <= \sum_j Y[j] - (R[i] - L[i] + 1) * D + X[i]
    // (R[i] - L[i] + 1) * D - C[i] <= \sum_j Y[j] + X[i]
    for (int i = 0; i < m; ++i) {
        A[i][i] = -1;
        for (int j = l[i] + m; j <= r[i] + m; ++j) A[i][j] = -1;
        B[i] = -cprime[i];
    }
    for (int i = m; i < m+n; ++i) {
        A[i][i] = 1;
        B[i] = d;
    }
    int i = 0;
    for (auto x : A) {
        for (auto y : x) cout << y << ' ';
        cout << B[i++] << endl;
    }
    cout << endl;
    for (auto x : C) cout << x << ' ';
    cout << endl;
    auto [sol, cert] = Simplex::simplex(A, B, C);
    sol *= -1;
    cout << fixed << setprecision(10) << sol << endl;
    for (auto x : cert) cout << x << ' ';
    cout << endl;
}

int32_t main() {_
    int t = 1; //cin >> t;
    while(t--) solve();
}
