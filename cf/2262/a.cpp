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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (a[n-1] == 0) {
        cout << 1 << endl;
        return;
    }
    set<int> B;
    for (int i = 0; i < n; ++i) B.insert(i);
    vector<ii> bichos;
    for (int i = 1; i <= n; ++i) {
        for (int val = 0; val <= a[i-1]; ++val) {
            int l = 0, r = n, menor = 10*n;
            while (l <= r) { 
                int md = l + (r-l+1)/2;
                if (md / i >= val) menor = md, r = md-1;
                else l = md+1;
            }
            l = 0, r = n-1;
            int maior = 10*n;
            while (l <= r) { 
                int md = l + (r-l+1)/2;
                if (md / i <= val) maior = md, l = md+1;
                else r = md-1;
            }
            if (val == a[i-1]) {
                if (maior == 10*n) continue;
                while (true) {
                    auto it = B.lower_bound(menor);
                    if (it == end(B)) break;
                    int x = (*it);
                    if (x > maior) break;
                    B.erase(x);
                }
            } else {
                bichos.pb({menor+1, maior+1});
            }
        }
    }
    vector<int> pode(n+1);
    for (auto x : B) pode[x+1] = 1;
    vector<int> dp(n+1), sdp(n+1);
    dp[0] = sdp[0] = 1;
    int ans = 0;
    sort(all(bichos), [&] (ii p1, ii p2) {
        return p1.second < p2.second;
    });
    int ptr = 0, mxL = 0;
    //for (auto [x, y] : bichos) cout << x << " " << y << endl;
    for (int i = 1; i <= n; ++i) {
        while (ptr < sz(bichos) and bichos[ptr].second < i) ckmax(mxL, bichos[ptr++].first);
        if (pode[i]) dp[i] = (sdp[i-1] - (mxL == 0 ? 0 : sdp[mxL-1]) + mod) % mod;
        //cout << dp[i] << " ";
        sdp[i] = (sdp[i-1] + dp[i]) % mod;
    }
    while (ptr < sz(bichos)) ckmax(mxL, bichos[ptr++].first);
    for (int i = mxL; i <= n; ++i) ans = (ans + dp[i]) % mod;
    cout << ans << endl;
    // quero conhecer apenas segmentos que TERMINAM antes de mim. dentre eles, pegue o com o maior R
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
