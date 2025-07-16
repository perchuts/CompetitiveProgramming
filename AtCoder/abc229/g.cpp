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
    int k; cin >> k;
    int n = sz(s);
    vector<int> pos;
    auto possible = [&] (int t) {
        // preciso calcular o custo de sortar cada janela
        int cost = 0;
        for (int i = 0; i < t-1; ++i) cost += (pos[i+1] - pos[i] - 1) * min(i+1, t - i - 1);
        if (cost <= k) return true;
        for (int i = t; i < sz(pos); ++i) {
            if (t&1) {
                // x....x....x....x......x
                cost -= pos[i-t+t/2+1] - pos[i-t] - t/2 - 1;
                cost += pos[i] - pos[i-t+t/2] - t/2 - 1;
            } else {
                // x....x....x......x
                cost -= pos[i-t+t/2] - pos[i-t] - t/2;
                cost += pos[i] - pos[i-t+t/2] - t/2;
            }
            if (cost <= k) return true;
        }
        return false;
    };
    for (int i = 0; i < n; ++i) if (s[i] == 'Y') pos.pb(i);
    int l = 2, r = sz(pos), ans = (sz(pos) > 0);
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, l = md+1;
        else r = md-1;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
