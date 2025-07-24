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
    vector<ii> pt(n);
    for (auto& [x, y] : pt) cin >> x >> y;
    int g0, ra, rb, q; cin >> q >> g0 >> ra >> rb;
    const int M = (1LL<<31)-1;
    const int c = 48271LL * 48271LL * 48271LL % M;
    const int M1 = 2 * ra + 1;
    const int M2 = 2 * rb + 1;
    int x1 = g0 * 48271LL % M, x2 = x1 * 48271LL % M, x3 = x2 * 48271LL % M;
    vector<array<int, 4>> ev;
    for (int j = 1; j <= q; ++j) {
        int a = -ra + (x1 % M1);
        int b = -rb + (x2 * M + x3) % M2;
        ev.pb({-a, 1, -1, b});
        x1 = x1 * c % M, x2 = x2 * c % M, x3 = x3 * c % M;
    }
    // yi >= aj * xi + bj
    // bj <= yi - aj * xi
    // point (-aj, bj), function f(x) = xi * x + yi
    // - C * xi + yi <= - C * xj + yj
    //
    vector<int> pos(n); iota(all(pos), 0);
    auto comp = [&] (ii a, ii b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    };
    sort(all(pt), comp);
    // events: query type, reverse inversion type
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (pt[i].first == pt[j].first) continue;
            // A1x + B1 = A2x + B2
            // x (A1 - A2) = B2 - B1
            // x = (B2 - B1) / (A1 - A2)
            auto [a1, b1] = pt[i];
            auto [a2, b2] = pt[j];
            int num = b2-b1, den = a1-a2, g = gcd(num, den);
            num /= g, den /= g;
            ev.pb({num, den, i, j});
        }
    }
    sort(all(ev), [&] (auto x1, auto x2) {
        if (x1[0]*x2[1] == x1[1]*x2[0]) {
            if (min(x1[2], x2[2]) == -1) return x1[2] < x2[2];
            return pair(x1[2], x1[3]) < pair(x2[2], x2[3]);
        }
        return x1[0]*x2[1] < x1[1]*x2[0];
    });
    int ans = 0;
    for (auto [num, den, x1, x2] : ev) {
        if (x1 == -1) {
            int l = 0, r = n-1, tot = 0;
            cout << num << ' ' << x2 << endl;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                if (x2 <= pt[md].first * num + pt[md].second) tot = n - md, r = md-1;
                else l = md+1;
            }
            ans += tot;
        } else {
            cout << x1 << ' ' << x2 << endl;
            assert(abs(pos[x1]-pos[x2]) == 1);
            swap(pos[x1], pos[x2]);
            swap(pt[pos[x1]], pt[pos[x2]]);
        }
    }
    cout << ans << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

