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
    // n+i -> n+i+1, 1 <= i < n
    // i -> a[i] + n
    // n + i -> i
    // path starting at 1 which visits every node
    // always, doing n+i -> i means doing n+i->i->n+a[i]
    // then you discard all first n nodes and simply add a edge n+i -> n+a[i] painted blue
    // edges n+i -> n+i+1 are painted red
    // question: is there a circuit that passes through every blue edge exactly once?
    // give me some order.
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;
    vector<vector<int>> g(2*n);
    for (int i = 0; i < n; ++i) g[i+n].pb(i), g[i].pb(a[i]+n);
    for (int i = n; i < n+n-1; ++i) g[i].pb(i+1);

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
