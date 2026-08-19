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
    string s; cin >> s;
    if (sz(s) > 11) {
        cout << 0 << endl;
        return;
    }
    vector<string> ans;
    int n = sz(s);
    auto go = [&] (auto&& self, string t, int i) -> void {
        if (sz(t) >= 3) {
            if (t[0] != '1') return;
            if (t[1] == '0') return;
            if (t[2] != '9') return;
        }
        if (sz(t) == 11) {
            assert(i == n);
            ans.pb(t);
            return;
        }
        if (sz(t) + n - i < 11) {
            self(self, t + '9', i);
            self(self, t + '1', i);
        }
        if (i != n) self(self, t + s[i], i+1);
    };
    go(go, "", 0);
    sort(all(ans));
    ans.erase(unique(all(ans)), end(ans));
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << endl;
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
