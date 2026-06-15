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

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i];
    // can do binary search
    // each person is going to be assigned a day to be killed
    // this person is going to consume b[1], b[2], ..., b[D], where D is the day this person dies
    // an additional c[D] is consumed at day D
    // after each person is assigned, need net medals to be non negative
    // what is fixed is what i earn at each step:
    // W[i] = A[1] + A[2] + ... + A[i]
    // qt[1] + qt[2] + ... + qt[N] = K
    // L[i] = K * B[1] + (K - qt[1]) * B[2] + (K - qt[1] - qt[2]) * B[2] + ... + (K - qt[1] - ... - q[i]) * B[i] - C[1] * qt[1] - C[2] * qt[2] -...-C[i]*qt[i]
    // need L[i] <= W[i]
    // in other words, ps[i] is a non increasing array (qt. of people alive at step i)
    // ps[0] = K, ps[N+1] = 0
    // se C[i] >= C[i+1] + B[i+1], entao ninguem morre no round C[i]
    // isso fica bem claro na 3a igualdade do L[i]
    // L[i] = ps[1] * B[1] + ps[2] * B[2] + ... + ps[i] * B[i] + (ps[1] - ps[2]) * C[1] + (ps[2] - ps[3]) * C[2] + ... + (ps[i] - ps[i+1]) * C[i]
    // L[i] = ps[1] * B[1] + ps[2] * B[2] + ... + ps[i] * B[i] + ps[1] * C[1] + ps[2] * (C[2] - C[1]) + ps[3] * (C[3] - C[2]) + ... + ps[i] * (C[i] - C[i-1]) - ps[i+1] * C[i]
    //
    //
    // L[i] = ps[1] * (B[1] + C[1]) + ps[2] * (B[2] + C[2] - C[1]) + ps[3] * (B[3] + C[3] - C[2]) + ... + ps[i] * (B[i] + C[i] - C[i-1]) - ps[i+1] * C[i]
    // L[i] = ps[1] * D[1] + ps[2] * D[2] + ... + ps[i] * D[i] - ps[i+1] * C[i]
    // L[0] >= 0
    // so notice that L[i] = \sum_{j=1}^{i+1} ps[j] * x[j]
    // we want W[i] >= \sum_{j=1}^{i+1} ps[j] * x[j] (y[i])
    // ps[N+1] >= 0 (z1[i])
    // -ps[N+1] >= 0 (z2[i])
    // ps[i] >= ps[i+1], => ps[i+1] - ps[i] <= 0 1 <= i <= N (dec[i])
    // maximize ps[1]
    // this is an integer linear program with variables ps[1], ps[2], ... ps[N+1]. what if we look at the dual?
    // minimize \sum (W[i] * y[i])
    // subject to 1 <= (B[1] + C[1]) * \sum(y[i]) - dec[1]
    //            0 <= dec[1] - dec[2]
    //            0 <= dec[2] - dec[3]
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
