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
    int n, m, k; cin >> n >> m >> k;
    vector<int> mp(256);
    mp['o'] = 0, mp['x'] = 1;
    vector<array<int, 3>> adj;
    adj.pb({-1, -1, 0});
    vector<string> caras(n);
    string t; cin >> t;
    int h = 1;
    auto add = [&] (string x, int z = 1) {
        int cur = 0;
        for (auto c : x) {
            if (adj[cur][mp[c]] == -1) adj[cur][mp[c]] = h++, adj.pb({-1, -1, 0});
            cur = adj[cur][mp[c]];
            adj[cur][2] += z;
        }
    };
    auto rem = [&] (string x) {
        int cur = 0;
        for (auto c : x) {
            cur = adj[cur][mp[c]];
            adj[cur][2]--;
        }
    };
    add(t, 0);
    for (auto& x : caras) cin >> x, add(x);
    int q; cin >> q;
    while (q--) {
        int i, j; cin >> i >> j; --i, --j;
        rem(caras[i]);
        if (caras[i][j] == 'o') caras[i][j] = 'x';
        else caras[i][j] = 'o';
        add(caras[i]);
        bool ok = 0;
        int cur = 0, qual = 0;
        for (int w = 0; w < k; ++w) {
            assert(cur != -1);
            if (adj[cur][mp[t[w]]] == -1 or qual + adj[adj[cur][mp[t[w]]]][2] <= m) {
                if (t[w] == caras[i][w]) { ok = 1; break; }
                if (adj[cur][mp[t[w]]] != -1) qual += adj[adj[cur][mp[t[w]]]][2];
            } else {
                if (t[w] != caras[i][w]) break;
            }
            cur = adj[cur][mp[caras[i][w]]];
        }
        cout << (ok ? "Yes" : "No") << endl;
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
