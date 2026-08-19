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
    int x, y; cin >> x >> y;
    int S = 0;
    string ans;
    while (S + sz(ans) + 1 <= x + y) {
        ans += 'X';
        S += sz(ans);
    }
    int want = (x + y - S + 1) / 2;
    if (x <= y) {
        int target = y - want;
        for (int i = sz(ans); i; --i) {
            if (i <= target) target -= i, ans[sz(ans)-i] = 'Y';

        }
    } else {
        for (auto& a : ans) a = 'Y';
        int target = x - want;
        for (int i = sz(ans); i; --i) {
            if (i <= target) target -= i, ans[sz(ans)-i] = 'X';
        }
    }
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
