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
const int mod = (441<<21)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, k; cin >> n >> k;
    int qt_max = (n + 2*k - 1) / (2 * k) + 1;
    // na inicializacao da dp, posso colocar alguem antes? (mod >= k)
    // no fim da dp, posso colocar alguem depois? (last pos + k <= n)
    int q1 = (n + 2*k - 1) / (2 * k), q2 = q1-1;
    vector peq(2, vector(2, vector<int>()));
    vector gra(2, vector(2, vector<int>()));
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    //cout << "q1 = " << q1 << endl;
    for (int t1 = 0; t1 < 2; ++t1) { 
        for (int t2 = 0; t2 < 2; ++t2) {
            vector dp(qt_max, vector(2, 0LL));
            // [usados][usei o de tras][usei a aresta de tras]
            dp[0][0] = 1;
            if (t1) dp[1][1]++;
            if (q1 == 1) {
                auto ndp = dp;
                if (t2) for (int i = 1; i <= q1; ++i) add(ndp[i][1], dp[i-1][0]);
                vector<int> v(q1+1);
                for (int j = 0; j <= q1; ++j) v[j] = (ndp[j][0] + ndp[j][1]) % mod;
                peq[t1][t2] = v;
            }
            for (int round = 1; round < q1; ++round) {
                if (round == q1-1) {
                    auto ndp = dp;
                    if (t2) for (int i = 1; i <= q1; ++i) add(ndp[i][1], dp[i-1][0]);
                    vector<int> v(q1+1);
                    for (int j = 0; j <= q1; ++j) v[j] = (ndp[j][0] + ndp[j][1]) % mod;
                    peq[t1][t2] = v;
                }
                vector ndp(qt_max, vector(2, 0LL));
                // usar essa aresta no bicho de tras
                for (int i = 0; i <= round; ++i) add(ndp[i+1][0], dp[i][0]);
                // usar essa aresta nesse bicho
                for (int i = 0; i <= round; ++i) add(ndp[i+1][1], dp[i][0]), add(ndp[i+1][1], dp[i][1]);
                // nao usar essa aresta
                for (int i = 0; i <= round; ++i) add(ndp[i][0], dp[i][0]), add(ndp[i][0], dp[i][1]);
                swap(dp, ndp);
            }
            if (t2) for (int i = 1; i <= q1; ++i) add(dp[i][1], dp[i-1][0]);
            vector<int> v(q1+1);
            for (int j = 0; j <= q1; ++j) v[j] = (dp[j][0] + dp[j][1]) % mod;
            gra[t1][t2] = v;
        }
    }
    //for (int i = 0; i < 2; ++i) {
    //    for (int j = 0; j < 2; ++j) {
    //        cout << "i = " << i << " j = " << j << endl;
    //        for (auto x : gra[i][j]) cout << x << " ";
    //        cout << endl;
    //    }
    //}
    vector<int> tot(n+1);
    tot[0] = 1;
    for (int i = 0; i < min(2*k, n); ++i) {
        vector<int> ntot(n+1);
        int qt = 0, z;
        for (int j = i; j < n; j += 2*k) qt++, z = j;
        assert(qt == q1 or qt == q2);
        int t1 = (i >= k), t2 = (z + k < n); 
        vector<int> v;
        if (qt == q1) v = gra[t1][t2];
        else v = peq[t1][t2];
        //cout << "i = " << i << endl;
        //for (auto x : v) cout << x << " ";
        //cout << endl;
        for (int x = 0; x <= min(n, i * q1); ++x) {
            for (int y = 0; y < sz(v) and x + y <= n; ++y) {
                ntot[x+y] += tot[x] * v[y];
                ntot[x+y] %= mod;
            }
        }
        swap(tot, ntot);
    }
    int ans = 0;
    vector<int> fat(n+1, 1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    for (int i = 0, c = 1; i <= n; ++i, c *= -1) {
        ans += tot[i] * c * fat[n-i];
        ans %= mod;
        ans = (ans + mod) % mod;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
