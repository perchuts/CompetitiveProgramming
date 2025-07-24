#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
    vector<ii> qq(q);
    for (int j = 1; j <= q; ++j) {
        int a = -ra + (x1 % M1);
        int b = -rb + (x2 * M + x3) % M2;
        qq[j-1] = {-a, b};
        x1 = x1 * c % M, x2 = x2 * c % M, x3 = x3 * c % M;
    }
    sort(all(qq));
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
    vector<ii> upd;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (pt[i].first == pt[j].first) continue;
            upd.pb({i, j});
            //if (pt[i].first > pt[j].first) upd.pb({i, j});
            //else upd.pb({j, i});
        }
    }
    #define s second
    #define f first
    sort(all(upd), [&] (const ii& a, const ii& b) {
        if ((pt[a.s].s-pt[a.f].s) * (pt[b.f].f-pt[b.s].f) == (pt[b.s].s-pt[b.f].s) * (pt[a.f].f-pt[a.s].f)) {
            if (a.f == b.f) return a.s < b.s;
            return a.f < b.f;
        }
        return (pt[a.s].s-pt[a.f].s) * (pt[b.f].f-pt[b.s].f) < (pt[b.s].s-pt[b.f].s) * (pt[a.f].f-pt[a.s].f);
    });
    int ans = 0, p1 = 0, p2 = 0, m = sz(upd);
    while (p1 != q) {
        int quem = 0;
        if (p2 != m) {
            int i = pos[upd[p2].f], j = pos[upd[p2].s];
            int num = pt[j].s-pt[i].s, den = pt[i].f-pt[j].f;
            if (den < 0) num *= -1, den *= -1;
            if (num < qq[p1].f*den) quem = 1;
        }
        if (quem == 0) {
            int l = 0, r = n-1, tot = 0;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                if (qq[p1].s <= pt[md].first * qq[p1].f + pt[md].second) tot = n - md, r = md-1;
                else l = md+1;
            }
            ans += tot, p1++;
        } else {
            auto [a, b] = upd[p2++];
            assert(abs(pos[a]-pos[b]) == 1);
            swap(pos[a], pos[b]);
            swap(pt[pos[a]], pt[pos[b]]);
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

