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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    int a, b, c, d; cin >> a >> b >> c >> d;
    int k; cin >> k;
    vector<string> oo(k);
    for (auto& x : oo) cin >> x;
    priority_queue<iii, vector<iii>, greater<>> pq;
    vector<vector<int>> dist(n, vector<int>(m, inf));
    dist[a][b] = 0;
    pq.push({0, a, b});
    while (!pq.empty()) {
        auto [dd, i, j] = pq.top(); pq.pop();
        if (dd != dist[i][j]) continue;
        for (auto s : oo) {
            int px = i, py = j, tot = dd;
            for (auto cc : s) {
                if (cc == 'U' and px and grid[px-1][py] == '0') px--, tot++;
                else if (cc == 'D' and px != n-1 and grid[px+1][py] == '0') px++, tot++;
                else if (cc == 'L' and py and grid[px][py-1] == '0') py--, tot++;
                else if (cc == 'R' and py != m-1 and grid[px][py+1] == '0') py++, tot++;
            }
            if (ckmin(dist[px][py], tot)) pq.push({tot, px, py});
        }
    }
    cout << (dist[c][d] == inf ? -1 : dist[c][d]) << endl;

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
