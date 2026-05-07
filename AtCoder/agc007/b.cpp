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
    vector<int> p(n), onde(n), a(n), b(n);
    for (auto& x : p) cin >> x, --x;
    set<int> exists;
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    exists.insert(onde[0]);
    for (int i = 1; i < n; ++i) {
        int my_pos = onde[i];
        a[i] = a[i-1]+1;
        b[i] = b[i-1]-1;
        int my_val = a[i] + b[i];
        auto it = exists.lower_bound(my_pos);
        int x;
        if (it == end(exists)) {
            int prv = *prev(it);
            x = a[p[prv]] + b[p[prv]] + my_pos - prv;
        } else {
            int nxt = *it;
            x = a[p[nxt]] + b[p[nxt]] + my_pos - nxt;
        }         
        if (my_val < x) a[i] += x - my_val;
        if (my_val > x) b[i] -= my_val - x;
        exists.insert(my_pos);
    }
    int x = a[0], y = b[n-1];
    for (int i = 0; i < n; ++i) a[i] -= x-1, b[i] -= y-1;
    for (auto x : a) cout << x << " ";
    cout << endl;
    for (auto x : b) cout << x << " ";
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
