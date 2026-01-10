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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    string s; cin >> s;
    int n = sz(s), ans = 0;
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = n-1; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
    auto ncr = [&] (int a, int b) {
        if (a < b or min(a, b) < 0) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    vector<int> inv(n+1);
    for (int i = 1; i <= n; ++i) inv[i] = fat[i-1] * ifat[i] % mod;
    for (int d = 0; d < 9; ++d) {
        string t;
        int cnt1 = 0;
        for (auto x : s) {
            if (x - '0' == d) t += '0';
            if (x - '0' == d + 1) t += '1', cnt1++;
        }
        if (cnt1 == 0) continue;
        int m = sz(t), cnt0 = 0;
        for (int i = 0; i < m; ++i) {
            if (t[i] == '1') {
                cnt1--;
            } else {
                // ncr(cnt0, i) * ncr(cnt1, i+1)
                // cnt0 <= cnt1-1
                if (cnt0 <= cnt1-1) {
                    // ncr(cnt0, cnt0-i) * ncr(cnt1, i+1)
                    // (cnt0+cnt1 cnt0+1)
                    ans = (ans + ncr(cnt0+cnt1, cnt0+1)) % mod;
                } else {
                    // ncr(cnt0, i) * ncr(cnt1, cnt1-i-1)
                    // (cnt0+cnt1 cnt1-1)
                    ans = (ans + ncr(cnt0+cnt1, cnt1-1)) % mod;
                }
                cnt0++;
            }
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
