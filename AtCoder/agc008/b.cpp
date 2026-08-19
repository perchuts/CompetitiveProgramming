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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> pref(n+1), suf(n+2), pref2(n+1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + max(0LL, a[i-1]), pref2[i] = pref2[i-1] + a[i-1];
    for (int i = n; i; --i) suf[i] = suf[i+1] + max(0LL, a[i-1]);
    int ans = 0;
    for (int i = 0; i <= n - k; ++i) {
        ckmax(ans, pref[i] + suf[i + k + 1] + max(0LL, pref2[i + k] - pref2[i]));
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
