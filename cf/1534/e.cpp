#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> A;

int solve(int n, int k) {
    vector<vector<int>> dist(n+1, vector<int>(n+1, -1)), move = dist;
    queue<ii> q;
    q.push({n, 0});
    dist[n][0] = 0;
    while (!q.empty()) {
        auto [a, b] = q.front(); q.pop();
        // k-i <= b
        // k-b <= i
        for (int i = max(0, k-b); i <= min(a, k); ++i) {
            int na = (a - i) + (k - i);
            int nb = n - na;
            if (dist[na][nb] == -1) dist[na][nb] = 1 + dist[a][b], q.push({na, nb}), move[na][nb] = i;
        }
    }
    if (dist[0][n] == -1) return -1;
    array<vector<int>, 2> ids; 
    for (int i = 0; i < n; ++i) ids[0].pb(i);
    int um = 0, zero = n, ans = 0;
    auto ask = [&] (vector<int> qry) {
#ifndef gato
        cout << "? ";
        for (auto x : qry) cout << x+1 << " ";
        cout << endl;
        int x; cin >> x;
        return x;
#else
        int x = 0;
        for (auto i : qry) x ^= A[i];
        return x;
#endif
    };
    while (um != n) {
        int q0 = move[um][zero];
        vector<int> qry;
        for (int i = 0; i < q0; ++i) qry.pb(ids[0].back()), ids[0].pop_back();
        for (int i = 0; i < k-q0; ++i) qry.pb(ids[1].back()), ids[1].pop_back();
        for (int i = 0; i < k; ++i) ids[i < q0].pb(qry[i]);
        ans ^= ask(qry);
        zero = zero - q0 + (k - q0);
        um = n - zero;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        int ans = solve(n, k);
        if (ans == -1) cout << -1 << endl;
        else cout << "! " << ans << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), k = rnd(1, n);
        A.resize(n);
        int ans = 0;
        for (auto& x : A) x = rnd(1, (1<<30)-1), ans ^= x;
        int my = solve(n, k);
        if (my != -1 and my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << endl;
            cout << "hidden: ";
            for (auto x : A) cout << x << " ";
            cout << endl;
            cout << "guessed: " << my << endl;
            exit(0);
        } else if (my == ans) {
            cout << "ok guessed correctly " << t++ << endl;
        }         
    }
#endif
}
