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
    int n; cin >> n;
    vector<int> l(n), r(n), ps(2*n+2);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        ps[l[i]]++, ps[r[i]+1]--;
    }
    for (int i = 2; i <= 2*n; ++i) ps[i] += ps[i-1];
    for (int i = 1; i <= 2*n; ++i) {
        if (ps[i] > 2) {
            cout << 0 << endl;
            return;
        }
    }
    vector<int> is_end(2*n+1);
    for (int i = 0; i < n; ++i) is_end[r[i]] = l[i];
    int ans = 1;
    for (int i = 1; i <= 2*n; ++i) {
        if (is_end[i] and ps[i] == 1) {
            ans = (2 * ans) % mod;
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
