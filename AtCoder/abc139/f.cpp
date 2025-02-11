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

void solve(){
    int n; cin >> n;
    vector<ii> v(n);
    for (auto& [x, y] : v) cin >> x >> y;
    auto dist = [&] (ii x) {
        return x.first * x.first + x.second * x.second;   
    };
    ii ans = {0, 0};
    auto V = v;
    for (int w = 0; w < n; ++ w) {
        for (int ww = 0; ww < n; ++ww) {
            v = V;
            auto cur = v[w];
            v[w].first *= -1, v[w].second *= -1;
            if (ww != w) {
                cur.first += v[ww].first, cur.second += v[ww].second;
                v[ww].first *= -1, v[ww].second *= -1;
            }
            while (true) {
                ii best = cur;
                int id = -1;
                for (int i = 0; i < n; ++i) {
                    auto [x, y] = v[i];
                    ii z = {x + cur.first, y + cur.second};
                    if (dist(z) > dist(best)) best = z, id = i;
                }
                if (best == cur) break;
                cur = best;
                v[id].first *= -1, v[id].second *= -1;
            }
            v[w].first *= -1, v[w].second *= -1;
            if (dist(ans) < dist(cur)) ans = cur;
        }
    }
    cout << fixed << setprecision(15) << hypot(ans.first, ans.second) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
