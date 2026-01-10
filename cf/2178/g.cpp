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

string solve(int n, vector<int> a, vector<int> b) {
    string ans;
    int hsh = 4;
    vector<vector<int>> vals(n, vector<int>(hsh));
    for (int i = 0; i < n; ++i) for (int j = 0; j < 4; ++j) vals[i][j] = rnd(0, (1LL<<60)-1);
    vector<vector<int>> bit_freq(2, vector<int>(2*n+1)), bit_ini(hsh, vector<int>(2*n+1)), bit_fim = bit_ini;
    auto add = [&] (int intr_id, int freq) {
        int l = a[intr_id], r = b[intr_id];
        l++, r++;
        int cur = l;
        while (cur <= 2*n) bit_freq[0][cur] ^= freq, cur += cur & (-cur);
        cur = r;
        while (cur <= 2*n) bit_freq[1][cur] ^= freq, cur += cur & (-cur);
        for (int i = 0; i < hsh; ++i) {
            cur = l;
            while (cur <= 2*n) bit_ini[i][cur] ^= vals[intr_id][i], cur += cur & (-cur);
            cur = r;
            while (cur <= 2*n) bit_fim[i][cur] ^= vals[intr_id][i], cur += cur & (-cur);
        }
    };
    auto query_freq = [&] (int i, int j) {
        int r = 0;
        while (i) r ^= bit_freq[j][i], i -= i & (-i);
        return r;
    };
    auto Query_freq = [&] (int l, int r) { return query_freq(r, 0) ^ query_freq(l, 0) ^ query_freq(r, 1) ^ query_freq(l, 1); };
    vector<int> ret(hsh);
    auto query = [&] (int x, bool type) {
        if (type) {
            while (x) {
                for (int i = 0; i < hsh; ++i) ret[i] ^= bit_fim[i][x];
                x -= x & (-x);
            }
        } else {
            while (x) {
                for (int i = 0; i < hsh; ++i) ret[i] ^= bit_ini[i][x];
                x -= x & (-x);
            }
        }
    };
    auto Query = [&] (int l, int r) {
        for (int i = 0; i < hsh; ++i) ret[i] = 0;
        query(r, 1), query(l, 1), query(r, 0), query(l, 0);
    };
    vector<int> acum(hsh);
    for (int i = 0; i < n; ++i) {
        int l = a[i], r = b[i];
        int tot = Query_freq(l, r) ^ 1;
        Query(l, r);
        bool ok = 1;
        for (int j = 0; j < hsh; ++j) {
            vals[i][j] = ret[j] ^ (tot ? vals[i][j] : 0);
            acum[j] ^= vals[i][j];
            ok &= (acum[j] == 0);
        }
        add(i, tot);
        ans += char('0' + ok);
    }
    return ans;
}
string brute(int n, vector<int> a, vector<int> b) {
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n));
    vector<vector<int>> ini_deg(2, vector<int>(n));
    string ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] and a[i] < b[j] and b[j] < b[i]) {
                g[0][i].pb(j);
                g[1][j].pb(i);
                ini_deg[0][j]++;
                ini_deg[1][i]++;
            } else if (a[i] < a[j] and a[j] < b[i] and b[i] < b[j]) {
                g[0][i].pb(j);
                g[1][j].pb(i);
                ini_deg[0][j]++;
                ini_deg[1][i]++;
            }
        }
        vector<int> ok(n);
        for (int turn = 0; turn < 2; ++turn) {
            auto deg = ini_deg[turn];
            vector<int> dp(n);
            queue<int> q;
            for (int j = 0; j <= i; ++j) {
                if (deg[j] == 0) q.push(j);
            }
            while (!q.empty()) {
                int u = q.front(); q.pop();
                dp[u] ^= 1;
                ok[u] |= (dp[u] == 0);
                for (auto v : g[turn][u]) {
                    deg[v]--;
                    dp[v] ^= dp[u];
                    if (deg[v] == 0) q.push(v);
                }
            }

        }
        char r = '1';
        for (int j = 0; j <= i; ++j) if (ok[j] == 0) r = '0';
        ans += r;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
        cout << solve(n, a, b) << endl;
    }
#else
    int t = 0;
    while (true) {
        int n = rnd(2, 10);
        vector<int> a(n), b(n), p(2*n); iota(all(p), 0);
        shuffle(all(p), rng);
        for (int i = 0; i < 2*n; i += 2) a[i/2] = min(p[i], p[i+1]), b[i/2] = max(p[i], p[i+1]);
        string my = solve(n, a, b), ans = solve(n, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) cout << a[i] + 1 << " " << b[i] + 1 << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;

    }
#endif
}
