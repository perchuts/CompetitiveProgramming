#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int b, int k, int x1, int y1, int x2, int y2){
    if (x1 > x2) swap(x1, x2), swap(y1, y2);
    auto coord = [&] (int x, int y) { return make_pair(b*(x/b), b*(y/b)); };
    auto calc2 = [&] (int A, int B, int C, int D) {
        return abs(A-C) + abs(B-D);
    };
    auto calc = [&] (int A, int B, int C, int D) {
        auto [cx1, cy1] = coord(A, B);
        auto [cx2, cy2] = coord(C, D);
        int ans = 9e18;
        if ((A == C and A % b == 0) or (B == D and B % b == 0)) return max(abs(A-C), abs(B-D));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int ccx1 = cx1 + (i % 2 ? b : 0), ccy1 = cy1 + (i < 2 ? b : 0);
                int ccx2 = cx2 + (j % 2 ? b : 0), ccy2 = cy2 + (j < 2 ? b : 0);
                ckmin(ans, abs(ccx1-ccx2) + abs(ccy1-ccy2) + calc2(A, B, ccx1, ccy1) + calc2(C, D, ccx2, ccy2));
            }
        }
        return ans;
    };
    auto get = [&] (int A, int B) {
        auto [cx, cy] = coord(A, B);
        vector<ii> resp;
        resp.pb({cx, B}), resp.pb({cx+b, B}), resp.pb({A, cy}), resp.pb({A, cy+b});
        return resp;
    };
    auto v1 = get(x1, y1); auto v2 = get(x2, y2);
    int ans = k*(abs(x1-x2)+abs(y1-y2));
    for (auto [xx1, yy1] : v1) for (auto [xx2, yy2] : v2) ckmin(ans, k * (abs(xx1-x1)+abs(yy1-y1)+abs(xx2-x2)+abs(yy2-y2)) + calc(xx1, yy1, xx2, yy2));
    return ans;
}

int brute(int b, int k, int x1, int y1, int x2, int y2) {
    map<ii, int> dist;
    priority_queue<iii, vector<iii>, greater<>> pq;
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    pq.push({0, x1, y1});
    dist[{x1, y1}] = 0;
    while (!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        if (d != dist[{x, y}]) continue;
        if (x == x2 and y == y2) return d;
        for (int i = 0; i < 4; ++i) {
            int xx = x + a[i], yy = y + a[i+4];
            int dd = k;
            if (x == xx and x % b == 0) dd = 1;
            if (y == yy and y % b == 0) dd = 1;
            if (!dist.count({xx, yy}) or ckmin(dist[{xx, yy}], d + dd)) dist[{xx, yy}] = d+dd, pq.push({d + dd, xx, yy});
        }
    }
    assert(false);
};

int32_t main(){_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        int b, k, x1, y1, x2, y2; cin >> b >> k >> x1 >> y1 >> x2 >> y2;
        cout << solve(b, k, x1, y1, x2, y2) << endl;
        //cout << brute(b, k, x1, y1, x2, y2) << endl;
    }
#else
    int t = 1;
    while (true) {
        int C = 5;
        int b = rnd(1, 5), k = rnd(1, 5), x1 = rnd(1, 10), y1 = rnd(1, C), x2 = rnd(1, C), y2 = rnd(1, C);
        int my = solve(b, k, x1, y1, x2, y2);
        int ans = brute(b, k, x1, y1, x2, y2);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << 1 << endl;
            cout << b << ' ' << k << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
