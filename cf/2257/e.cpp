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
    int n, x; cin >> n >> x;
    vector<vector<int>> a(n), b(n);
    //vector<vector<int>> seta(n), ps_a(n), ps_b(n);
    vector<int> height(n), seta(n);
    priority_queue<array<int, 4>, vector<array<int,4>>, greater<>> pq;
    auto recalc = [&] (int i, int j) {
        int ptr = j, sa = 0, sb = 0, max_needed = 0;
        bool nice = 0;
        while (ptr < height[i]) {
            sa += a[i][ptr];
            ckmax(max_needed, sa - sb);
            sb += b[i][ptr];
            ptr++;
            if (sb >= sa) {
                nice = 1;
                break;
            }
        }
        array<int, 4> ans;
        if (!nice) ans[0] = -1;
        else ans[0] = max_needed, ans[1] = ptr, ans[2] = sb-sa, ans[3] = i;
        return ans;
    };
    for (int i = 0; i < n; ++i) {
        cin >> height[i];
        a[i].resize(height[i]);
        b[i].resize(height[i]);
        //ps_a[i].resize(height[i]+1);
        //ps_b[i].resize(height[i]+1);
        //seta[i].resize(height[i]+1);
        for (auto& x : a[i]) cin >> x;
        for (auto& x : b[i]) cin >> x;
        auto z = recalc(i, 0);
        if (z[0] != -1) pq.push(z);
        // overcomplicated!
        //for (int j = 1; j <= height[i]; ++j) ps_a[i][j] = ps_a[i][j-1] + a[i][j-1];
        //for (int j = 1; j <= height[i]; ++j) ps_b[i][j] = ps_b[i][j-1] + b[i][j-1];
        //vector<int> order(height[i]+1); iota(all(order), 0);
        //sort(all(order), [&] (int x, int y) {
        //    int px = ps_a[i][x] - ps_b[i][x];
        //    int py = ps_a[i][y] - ps_b[i][y];
        //    if (px == py) return x > y;
        //    return px < py;
        //});
        //set<int> vals;
        //for (auto j : order) {
        //    if (j != height[i]) {
        //        auto it = vals.lower_bound(j);
        //        if (it == end(vals)) seta[i][j+1] = -1;
        //        else seta[i][j+1] = (*it)+1;
        //    }
        //}
        // to calculate arrow[i][j]:
        // want minimum k such that:
        // b[i][k] - b[i][j-1] >= a[i][k] - a[i][j-1]
        // a[i][j-1] - b[i][j-1] >= a[i][k] - b[i][k]

    }
    while (!pq.empty()) {
        auto z = pq.top(); pq.pop();
        if (z[0] > x) break;
        // max_needed, ptr, ganho, onde
        x += z[2];
        seta[z[3]] = z[1];
        auto z2 = recalc(z[3], seta[z[3]]);
        if (z2[0] != -1) pq.push(z2);
    }
    ii ans = {0, 0};
    for (int i = 0; i < n; ++i) {
        int optimal = seta[i], cx = x;
        while (optimal < height[i]) {
            if (cx < a[i][optimal]) break;
            cx += b[i][optimal] - a[i][optimal];
            optimal++;
        }
        if (optimal > ans.first) ans = {optimal, i};
    }
    cout << ans.first << " " << ans.second+1 << endl;

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
