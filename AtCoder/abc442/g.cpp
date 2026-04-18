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
    int n, c; cin >> n >> c;
    vector<vector<ii>> v(4);
    for (int i = 0; i < n; ++i) {
        int a, b, x; cin >> a >> b >> x; v[a].pb({b, x});
    }
    int t3 = sz(v[3]);
    vector<int> cost3(t3+1), val3(t3+1);

    auto solve = [&] (vector<ii> v2, int C) {
        sort(rbegin(v2), rend(v2));
        int opt = 0;
        for (int tira = 0; tira < 3 and 2 * tira <= C; ++tira) {
            int need = tira, base_win = 0, base_C = C;
            auto vv2 = v2; vector<int> cost2 = {0}, val2 = {0};
            for (auto& [val, qt] : vv2) { while (min(need, qt) > 0) base_win += val, --qt, --need, base_C -= 2; if (!need) break; }
            for (auto [val, qt] : vv2) cost2.pb(cost2.back() + 2 * qt), val2.pb(val2.back() + val * qt);
            // calcule o optimo pegando x do 2, o maximo q da do 3.
            auto calc = [&] (int x) {
                int pos = upper_bound(all(cost2), 2*x) - begin(cost2) - 1;
                int win = base_win + val2[pos];
                if (2*x < cost2.back()) win += vv2[pos].first * (2*x - cost2[pos]) / 2;

                int sobra = base_C - 2*x;
                assert(sobra >= 0);
                pos = upper_bound(all(cost3), sobra) - begin(cost3) - 1;
                win += val3[pos];
                if (sobra < cost3.back()) win += v[3][pos].first * ((sobra-cost3[pos])/3);
                return win;
            };
            ckmax(opt, calc(0));
            int l = 0, r = min((cost2.back() / 2) / 3, base_C / 6) - 1;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                int c1 = calc(3*md), c2 = calc(3*md+3);
                ckmax(opt, max(c1, c2));
                if (c1 <= c2) l = md+1;
                else r = md-1;
            }
        } 
        return opt;
    };

    sort(rbegin(v[1]), rend(v[1])), sort(rbegin(v[3]), rend(v[3]));

    for (int i = 1; i <= t3; ++i) cost3[i] = cost3[i-1] + 3 * v[3][i-1].second, val3[i] = val3[i-1] + v[3][i-1].first * v[3][i-1].second;

    auto transform = [&] (vector<ii> v1) {
        auto tv2 = v[2];
        int lst = -1;
        for (auto [val, qq] : v1) {
            if (lst != -1) qq--, tv2.pb({val+lst, 1});
            if (qq > 1) tv2.pb({2*val, qq/2});
            if (qq & 1) lst = val;
            else lst = -1;
        }
        return tv2;
    };

    int ans = solve(transform(v[1]), c);

    if (!v[1].empty()) v[1][0].second--, ckmax(ans, v[1][0].first + solve(transform(v[1]), c-1));

    cout << ans << endl;
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
