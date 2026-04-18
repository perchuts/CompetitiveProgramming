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
    string s, t; cin >> s >> t;
    auto trs = [&] (string z) {
        string ans;
        for (auto x : z) if (x != 'A') ans += x;
        return ans;
    };
    if (trs(s) != trs(t)) {
        cout << -1 << endl;
        return;
    }
    auto trs2 = [&] (string z) {
        vector<int> ans;
        int n = sz(z);
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (z[i] != 'A') {
                ans.pb(cnt), cnt = 0;
            }
            else cnt++;
        }
        ans.pb(cnt);
        return ans;
    };
    auto v1 = trs2(s);
    auto v2 = trs2(t);
    int ans = 0;
    for (int i = 0; i < sz(v1); ++i) ans += abs(v1[i]-v2[i]);
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
