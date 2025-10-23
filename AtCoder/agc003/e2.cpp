#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

vector<int> solve(int n, int q, vector<int> qu) {
    int N = n;
    vector<ii> chain = {{1, 0}};
    vector<int> tam = {n};
    int T = 1;
    for (auto& x : qu) {
        if (x == tam.back()) continue;
        if (x < tam.back()) {
            while (T > 1 and x < tam[T-2]) tam.pop_back(), chain.pop_back(), T--;
            if (x == tam[T-1]) continue;
            if (T == 1) n = tam[T-1] = x; 
            else chain.back() = {x / tam[T-2], x % tam[T-2]}, tam.back() = x;
        } else {
            chain.pb({x/tam[T-1], x % tam[T-1]});
            tam.pb(x);
            T++;
        }
    }
    vector<int> ans(N+1);
    for (int i = 1; i <= n; ++i) ans[i] = 1;
    vector<vector<int>> versions; vector<int> tams, adds; versions.pb(ans), tams.pb(n);
    vector<vector<ii>> g1; vector<vector<int>> g2;
    auto flush = [&] () {
        if (adds.empty()) return;
        // ai a vibe eh agr fazer uma generalizacao de prefix sum pra recuperar o todo
        auto ps = adds;
        int m = sz(adds), ct = tams.back();
        ps[0] += ct;
        for (int i = 1; i < m; ++i) ps[i] += ps[i-1];

        auto get_g1 = [&] (int k) {
            vector<ii> edges;
            while (k) {
                int z = upper_bound(all(tams), k) - begin(tams) - 1;
                if (z == -1) break;
                edges.pb({z, k/tams[z]});
                k %= tams[z];
            }
            if (k) edges.pb({-1, k});
            return edges;
        };

        auto get_g2 = [&] (int& k) {
            vector<int> edges;
            while (k > ct) {
                int z = upper_bound(all(ps), k) - begin(ps) - 1;
                if (z == -1) break;
                edges.pb(z);
                k -= ps[z];
            }
            return edges;
        };
        cout << "tamanho base: " << ct << endl;
        cout << "adds: ";
        for (auto x : adds) cout << x << ' ';
        cout << endl;
        for (int i = 0; i < m; ++i) {
            if (ct < adds[i]) {
                int k = adds[i];
                g2[i] = get_g2(k), g1[i] = get_g1(k%ct);
                g1[i].pb({sz(tams)-1, (k >= ct) + sz(g2[i])});
            } else g1[i] = get_g1(adds[i]);
        }
        cout << "g1:" << endl;
        for (int i = 0; i < m; ++i) {
            for (auto [j, k] : g1[i]) cout << j << ", " << k << " ## ";
            cout << endl;
        }
        cout << "g2:" << endl;
        for (int i = 0; i < m; ++i) {
            for (auto j : g2[i]) cout << j << ' ';
            cout << endl;
        }
        cout << "######" << endl;
        vector<int> dp(m, 1), dp2(sz(versions)), pref(n+1);
        for (int i = m-1; ~i; --i) {
            for (auto j : g2[i]) dp[j] += dp[i];
            for (auto [j, w] : g1[i]) {
                if (j != -1) dp2[j] += dp[i] * w;
                else pref[w] += dp[i];
            }
        }
        cout << "dp2: ";
        for (auto x : dp2) cout << x << ' ';
        for (int i = n-1; i; --i) pref[i] += pref[i+1];
        cout << "pref: ";
        for (int i = 1; i <= n; ++i) cout << pref[i] << ' ';
        cout << endl;
        for (int j = 0; j < sz(versions); ++j) {
            for (int i = 1; i <= n; ++i) ans[i] += versions[j][i] * dp2[j];
        }
        for (int i = 1; i <= n; ++i) ans[i] += pref[i];
        adds.clear();
    };
    for (int i = 0; i < sz(chain); ++i) {
        cout << chain[i].first << ' ' << chain[i].second << ' ' << tam[i] << endl;
    }
    for (int i = 1; i < sz(chain); ++i) {
        auto [ki, ri] = chain[i];
        cout << "processing operation ki = " << ki << ", ri = " << ri << endl;
        if (ki > 1) {
            flush();
            auto tp = ans;
            if (ri) {
                cout << "forgot to add " << ri << "!" << endl;
                int k = ri / tams.back(), rri = ri % tams.back();
                cout << "k = " << k << " rri = " << rri << endl;
                for (int j = 1; j <= n; ++j) ans[j] *= k;
                if (rri) adds.pb(rri), flush();
                for (int j = 1; j <= n; ++j) ans[j] += ki * tp[j];
            } else {
                for (int j = 1; j <= n; ++j) ans[j] *= ki;
            }
            versions.pb(ans);
            tams.pb(tam[i]);
            cout << "adding this version: {" << tam[i] << ", ";
            for (auto x : ans) cout << x << ' ';
            cout << "}\n";
        } else {
            if (ri) {
                cout << "must push " << ri << " units in the future" << endl;
                adds.pb(ri);
            }
        }
    }
    flush();
    return ans;
}

vector<int> brute(int n, int q, vector<int> qu) {
    vector<int> cur(n); iota(all(cur), 1);
    for (auto x : qu) {
        vector<int> nq;
        for (int i = 0; i < x; ++i) nq.pb(cur[i%sz(cur)]);
        swap(nq, cur);
    }
    vector<int> freq(n+1);
    for (auto x : cur) freq[x]++;
    return freq;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n >> q;
    vector<int> qu(q);
    for (auto& x : qu) cin >> x;
    auto ans = solve(n, q, qu);
    for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 6), q = rnd(1, 5);
        vector<int> qu(q);
        for (auto& x : qu) x = rnd(1, 10);
        auto my = solve(n, q, qu);
        auto ans = brute(n, q, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : qu) cout << x << ' ';
            cout << endl;
            cout << "Your output: ";
            for (int i = 1; i <= n; ++i) cout << my[i] << ' ';
            cout << endl;
            cout << "Answer: ";
            for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
