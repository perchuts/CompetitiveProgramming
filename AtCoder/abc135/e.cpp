#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+2;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(int k, int x, int y){
    if (abs(x) + abs(y) == k) {
        cout << 1 << endl << x << ' ' << y << endl;
        return;
    }
    auto dist = [] (int x1, int y1, int x2, int y2) { return abs(x1-x2) + abs(y1-y2); };
    auto solve = [&] (int x1, int y1, int x2, int y2, int k) {
        int d = dist(x1, y1, x2, y2);
        assert(d < 2*k);
        vector<ii> pts = {{x1-k, y1}, {x1, y1+k}, {x1+k, y1}, {x1, y1-k}};
        for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < 4; ++i) {
                auto [xx1, yy1] = pts[i];
                auto [xx2, yy2] = pts[(i+1)%4];
                if (dist(xx1, yy1, x2, y2) == k) return pts[i];
                if (dist(xx1, yy1, x2, y2) < k and dist(xx2, yy2, x2, y2) > k) {
                    // fez o w
                    int dx = (xx1 < xx2 ? 1 : -1);
                    int dy = (yy1 < yy2 ? 1 : -1);
                    int l = 1, r = abs(xx1-xx2), ans = 0;
                    while (l <= r) {
                        int md = l + (r-l+1)/2;
                        int xx3 = md*dx + xx1, yy3 = md*dy + yy1;
                        if (dist(xx3, yy3, x2, y2) <= k) ans = md, l = md+1;
                        else r = md-1;
                    }
                    return pair{ans*dx+xx1, ans*dy+yy1};
                }
            }
            reverse(all(pts));
        }
        assert(false);
        return pair{0LL, 0LL};
    };
    vector<ii> ans;
    if (k % 2 == 0) {
        if ((x + y + inf) % 2) {
            cout << -1 << endl;
            return;
        }
        int steps = (abs(x) + abs(y)) / k, xx = 0, yy = 0;
        while (steps > 1) {
            if (x-xx >= k) xx += k;
            else if (x-xx <= -k) xx -= k;
            else if (y-yy >= k) yy += k;
            else assert(y-yy <= -k), yy -= k;
            ans.pb({xx, yy}), steps--;
        }
        // solve in two steps
        // or one!
        if (dist(xx, yy, x, y) == k) {
            ans.pb({x, y});
        } else {
            auto last = solve(xx, yy, x, y, k);
            ans.pb(last), ans.pb({x, y});
        }
        cout << sz(ans) << endl;
        for (auto [x, y] : ans) cout << x << ' ' << y << endl;
        return;
    }
    int steps = (abs(x) + abs(y)) / k, xx = 0, yy = 0;
    // solve in two or three steps
    while (steps > 1) {
        if (x-xx >= k) xx += k;
        else if (x-xx <= -k) xx -= k;
        else if (y-yy >= k) yy += k;
        else assert(y-yy <= -k), yy -= k;
        ans.pb({xx, yy}), steps--;
    }
    if (dist(xx, yy, x, y) == k) {
        ans.pb({x, y});
    } else {
        if (dist(xx, yy, x, y) % 2) {
            // move to keep distance < 2*k
            if (abs(x-xx) >= abs(y-yy)) {
                if (x < xx) xx -= k;
                else xx += k;
            } else {
                if (y < yy) yy -= k;
                else yy += k;
            }
            ans.pb({xx, yy});
            assert(dist(xx, yy, x, y) < 2*k);
        }
        auto last = solve(xx, yy, x, y, k);
        ans.pb(last), ans.pb({x, y});
    }
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}

int32_t main(){_
#ifndef gato
    int k, x, y; cin >> k >> x >> y;
    solve(k, x, y);
#else
    while (true) {
        int k = rnd(1, 10), x = rnd(0, 10), y = rnd(0, 10);
        cout << "TEST CASE: ";
        cout << k << ' ' << x << " " << y << endl;
        solve(k, x, y);
    }
#endif
}
