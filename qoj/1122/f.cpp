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
    int r, s, h; cin >> r >> s >> h;
    using ld = long double;
    ld dist = 2.0 * acos(-1.0) * r; 
    ld hours_per_year = dist / s;
    ld days_per_year  = hours_per_year / h;
    cout << fixed << setprecision(10);
    ld rounded = round(days_per_year);
    vector<iii> bichos;
    for (int i = 2; i <= 250; ++i) {
        for (int j = 2; i * j <= 500; ++j) {
            for (int k = 2; i * j * k <= 1000; ++k) {
                bichos.pb({i, i*j, i*j*k});
            }
        }
    }
    double opt = 100000;
    double diff = days_per_year - rounded;
    iii ans;
    for (auto [n1, n2, n3] : bichos) {
        double z = ld(1.0/n1) - ld(1.0/n2) + ld(1.0/n3);
        if (rounded > days_per_year) z *= -1;
        if (ckmin(opt, abs(diff-z))) ans = {n1, n2, n3};
    }
    auto [n1, n2, n3] = ans;
    cout << n1 << " " << n2 << " " << n3 << endl;
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
