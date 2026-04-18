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
// Para FFT
void get_roots(bool f, int n, vector<complex<double>>& roots) {
    const static double PI = acosl(-1);
    for (int i = 0; i < n/2; i++) {
        double alpha = i*((2*PI)/n);
        if (f) alpha = -alpha;
        roots[i] = {cos(alpha), sin(alpha)};
    }
}
void fft(vector<complex<double>>& a, bool f, int N, vector<int>& rev) {
    for (int i = 0; i < N; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    int l, r, m;
    vector<complex<double>> roots(N);
    for (int n = 2; n <= N; n *= 2) {
        get_roots(f, n, roots);
        for (int pos = 0; pos < N; pos += n) {
            l = pos + 0, r = pos + n/2, m = 0;
            while (m < n/2) {
                auto t = roots[m] * a[r];
                a[r] = a[l] - t;
                a[l] = a[l] + t;
                l++, r++, m++;
            }
        }
    }
    if (f) {
        auto invN = 1.0 / N;
        for (int i = 0; i < N; i++) a[i] = a[i] * invN;
    }
}

using T = complex<double>;

vector<T> convolution(vector<T>& a, vector<T>& b) {
    vector<T> l(a.begin(), a.end()), r(b.begin(), b.end());
    int N = l.size()+r.size()-1;
    int n = 1, log_n = 0;
    while (n <= N) n *= 2, log_n++;
    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = 0;
        for (int j = 0; j < log_n; j++) if (i>>j&1)
            rev[i] |= 1 << (log_n-1-j);
    }
    assert(N <= n);
    l.resize(n);
    r.resize(n);
    fft(l, false, n, rev);
    fft(r, false, n, rev);
    for (int i = 0; i < n; i++) l[i] *= r[i];
    fft(l, true, n, rev);
    l.resize(N);
    return l;
}
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> deg(n), foi(n), q;
    for (int i = 0; i < n; ++i) {
        deg[i] = sz(g[i]);
        if (deg[i] == 1) q.pb(i);
    }
    int score = 0;
    while (sz(q) > 2) {
        score++;
        vector<int> qq;
        for (auto u : q) {
            foi[u] = 1;
            for (auto v : g[u]) {
                if (foi[v]) continue;
                deg[v]--;
                if (deg[v] == 1) qq.pb(v);
            }
        }
        swap(q, qq);
    }
    vector<int> par(n), lvl(n), cur;
    int d = 0;
    for (int i = 0; i < n; ++i) d += (!foi[i]);
    auto dfs = [&] (auto&& self, int u, int p, int h) -> void {
        cur.pb(h);
        for (auto v : g[u]) {
            if (v == p or foi[v] == 0) continue;
            self(self, v, u, h+1);
        }
    };
    vector<vector<int>> mult;
    if (sz(q) == 1) {
        for (auto v : g[q[0]]) {
            dfs(dfs, v, v, 1);
            int h = *max_element(all(cur));
            vector<int> cnt(h+1);
            for (auto x : cur) cnt[x]++;
            mult.pb(cnt), cur.clear();
        }
    } else {
        for (int i = 0; i < 2; ++i) {
            dfs(dfs, q[i], q[i], 0);
            int h = *max_element(all(cur));
            vector<int> cnt(h+1);
            for (auto x : cur) cnt[x]++;
            mult.pb(cnt), cur.clear();
        }
    }
    // faça (tudo) - ruins
    auto conv = [&] (vector<int> a, vector<int> b) {
        vector<complex<double>> A(all(a));
        vector<complex<double>> B(all(b));
        auto C = convolution(A, B);
        vector<ll> res(sz(C));
        for (int i = 0; i < sz(C); ++i) res[i] = llround(C[i].real());
        return res;
    };
    vector<int> v(n+1);
    for (auto x : mult) {
        for (int i = 0; i < sz(x); ++i) v[i] += x[i];
    }
    auto ans = conv(v, v);
    if (sz(q) == 1) {
        ans[0] += 2;
        for (int i = 1; i <= n; ++i) ans[i] += 2*v[i];
    }
    for (auto x : mult) {
        //for (auto y : x) cout << y << " ";
        //cout << endl;
        auto z = conv(x, x);
        //cout << "conv: ";
        //for (auto y : z) cout << y << " ";
        //cout << endl;
        for (int i = 0; i < sz(z); ++i) ans[i] -= z[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (i < d) cout << 0 << endl;
        else cout << ans[i-d]/2 << endl;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
