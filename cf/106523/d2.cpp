#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    ll n; int q; cin >> n >> q;
    // Division Trick
    //
    // Gera o conjunto n/i, pra todo i, em O(sqrt(n))
    // copiei do github do tfg50
    // penis
    vector<ll> vals;
    vector<int> a(n+1);
    vector<array<ll, 5>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][4] >> queries[i][0] >> queries[i][1];
        if (queries[i][4] == 2) cin >> queries[i][2] >> queries[i][3];
        vals.pb(queries[i][0]);
        vals.pb(queries[i][1]);
        int l = queries[i][0], r = queries[i][1];
        if (queries[i][4] == 1) {
            int ans = 0;
            for (int j = l; j <= r; ++j) ans = (ans + a[j]) % mod;
            cout << ans << endl;
        } else {
            for (int j = l; j <= r; ++j) {
                if ((n / j) == queries[i][2]) a[j] = (a[j] + queries[i][3]) % mod;
            }
        }
    }

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
