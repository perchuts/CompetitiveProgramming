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
    int n, d; cin >> n >> d;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    queue<int> q;
    vector<int> matou(10*n+10), matar(10*n+10);
    vector<vector<int>> venceu(n);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a[i]; ++j) {
            q.push(h + j);
            if (i + d < n) venceu[i+d].pb(h+j);
        }
        h += a[i];
        while (b[i]) {
            assert(!q.empty());
            int x = q.front(); q.pop();
        
            if (matar[x]) continue;
            b[i]--;
        }
        for (auto x : venceu[i]) matar[x] = 1;
    }
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans += (matar[u] == 0);
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
