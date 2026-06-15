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
    int n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;
    int gg = gcd(vx, vy); vx /= gg, vy /= gg;
    int g1 = gcd(vx, n), g2 = gcd(vy, n);
    if ((n-x) % g1 or (n-y) % g2) { cout << -1 << endl; return; }
    auto ext_gcd = [&] (auto&& self, int b1, int b2) -> ii {
        if (b2 == 0) return {1LL, 0LL};
        auto [kp, lp] = self(self, b2, b1%b2);
        return {lp, kp - lp * (b1/b2)};
    };
    auto mod_inv = [&] (int b, int m) -> int {
        auto [k, l] = ext_gcd(ext_gcd, b, m);
        k %= m;
        k = (k + m) % m;
        return k;
    };
    int b1 = n/g1, b2 = n/g2;
    int a1 = -(x/g1) * mod_inv(vx/g1, b1) % b1; a1 = (a1 + b1) % b1;
    int a2 = -(y/g2) * mod_inv(vy/g2, b2) % b2; a2 = (a2 + b2) % b2;
    int L = lcm(b1, b2);
    int g3 = gcd(b1, b2);
    int D = (a1 - a2) % L; D = (D + L) % L;
    if (D % g3) {
        cout << -1 << endl;
        return;
    }
    auto [k, l] = ext_gcd(ext_gcd, b1, b2); 
    assert(k * b1 + l * b2 == g3);
    k *= -(D/g3), l *= (D/g3);
    int z = (a2 + l * b2) % L; z = (z + L) % L;
    if (z == 0) z += L;
    int px = x + vx*z, py = y + vy*z;
    px /= n, py /= n;
    if (px+py == 1) {
        cout << 0 << endl;
        return;
    }
    int ppx = px+py, ppy = px-py;
    int ans = px + py - 2 + (ppx+1)/2 + (abs(ppy)+1)/2;
    if (abs(ppx) % 2) ans -= 2;
    cout << ans << endl;

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
