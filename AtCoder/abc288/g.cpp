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
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 3 * pot[i-1];
    vector<int> a(pot[n]), na = a;
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; ++i) {
        // fixing i-th bit
        for (int j = 0; j < pot[n]; ++j) {
            int x = (j / pot[i]) % 3;
            if (x == 0) {
                na[j] = a[j+pot[i]] - a[j+2*pot[i]];
            } else if (x == 1) {
                na[j] = a[j+pot[i]] + a[j-pot[i]] - a[j];
            } else {
                na[j] = a[j-pot[i]] - a[j-2*pot[i]];
            }
        }
        swap(a, na);
    }
    for (auto x : a) cout << x << ' ';
    cout << endl;
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
