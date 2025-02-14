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

pair<vector<int>, vector<string>> solve(int n, vector<ii> v){
    int par = (v[0].first & 1) ^ (v[0].second & 1);
    for (int i = 1; i < n; ++i) {
        if (((v[i].first & 1) ^ (v[i].second & 1)) != par) {
            return {{}, {}};
        }
    }
    vector<int> a(31);
    vector<string> resp;
    for (int j = 0; j <= 30; ++j) a[j] = (1 << j);
    if (par == 0) a.pb(1);
    for (auto [x, y] : v) {
        string ans(sz(a), 'R');
        if (par == 0) x--;
        int change = 31;
        for (int i = 30; ~i; --i) {
            int K = abs(x) + abs(y);
            assert(K < (1LL<<(i+1)));
            if (K >= (1 << i)) {
                if (abs(x) >= abs(y)) {
                    for (int j = change-1; j >= i; --j) {
                        if (j == change-1) {
                            if (x < 0) ans[j] = 'L';
                            else ans[j] = 'R';
                        } else {
                            if (x > 0) ans[j] = 'L';
                            else ans[j] = 'R';
                        }
                    }
                    if (x > 0) x -= (1 << i);
                    else x += (1 << i);
                    change = i;
                } else {
                    for (int j = change-1; j >= i; --j) {
                        if (j == change-1) {
                            if (y < 0) ans[j] = 'D';
                            else ans[j] = 'U';
                        } else {
                            if (y > 0) ans[j] = 'D';
                            else ans[j] = 'U';
                        }
                    }
                    if (y > 0) y -= (1 << i);
                    else y += (1 << i);
                    change = i;
                }
            }
        }
        assert(change == 0);
        resp.pb(ans);
    }
    return make_pair(a, resp);
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<ii> v(n);
    for (auto& [x, y] : v) cin >> x >> y;
    auto [a, ans] = solve(n, v);
    if (a.empty()) {
        cout << -1 << endl;
        exit(0);
    }
    cout << sz(a) << endl;
    for (auto x : a) cout << x << ' ';
    cout << endl;
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 1000);
        vector<ii> v(n);
        for (auto& [x, y] : v) x = rnd(-1000, 1000), y = rnd(-1000, 1000);
        auto [a, resp] = solve(n, v);
        if (a.empty()) continue;
        for (int j = 0; j < n; ++j) { 
            auto [x, y] = v[j];
            auto ans = resp[j];
            int X = 0, Y = 0;
            assert(sz(ans) == sz(a));
            for (int i = 0; i < sz(ans); ++i) {
                if (ans[i] == 'R') X += a[i];
                else if (ans[i] == 'L') X -= a[i];
                else if (ans[i] == 'U') Y += a[i];
                else Y -= a[i];
            }
            if (X != x or Y != y) {
                cout << "Wrong answer on test " << t << endl;
                cout << n << endl;
                for (auto [z, zz] : v) cout << z << ' ' << zz << endl;
                cout << "Your output: " << endl;
                cout << sz(a) << endl;
                for (auto x : a) cout << x << ' ';
                cout << endl;
                for (auto x : ans) cout << x; 
                cout << endl;
                cout << "got wrong in j = " << j << endl;
                cout << X << ' ' << Y << endl;
                exit(0);
            }
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
