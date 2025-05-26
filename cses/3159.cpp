#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<ii> solve(int n, vector<int> v){
    int maxval = *max_element(all(v));
    shuffle(all(v), rng);
    int lim = maxval * (1.7*sqrt(n) + 1), sum = 0;
    //cout << "Lim: ";
    //cout << lim << endl;
    vector<vector<bool>> can(n+1, vector<bool>(2*lim+10)), tr = can;
    can[0][lim] = 1;
    for (int i = 1; i <= n; ++i) {
        sum += v[i-1];
        for (int j = max(-lim, -sum); j <= min(lim, sum); ++j) {
            int o1 = j - v[i-1];
            if (-lim <= o1 and can[i-1][o1+lim]) can[i][j+lim] = 1, tr[i][j+lim] = 1;
            int o2 = j + v[i-1];
            if (o2 <= lim and can[i-1][o2+lim]) can[i][j+lim] = 1, tr[i][j+lim] = 0;
        }
    }
    if (can[n][lim] == false) return vector<ii>();
    int val = 0, S = 0;
    vector<int> plus, minus;
    for (int cur = n; cur >= 1; --cur) {
        if (tr[cur][val+lim]) plus.pb(v[cur-1]), val -= v[cur-1], S += v[cur-1];
        else minus.pb(v[cur-1]), val += v[cur-1], S -= v[cur-1];
    }
    //cout << "Sum: " << S << endl;
    //cout << "+: ";
    //for (auto x : plus) cout << x << ' ';
    //cout << endl;
    //cout << "-: ";
    //for (auto x : minus) cout << x << ' ';
    //cout << endl;
    int zero = -1;
    vector<ii> sol;
    while (!plus.empty() and !minus.empty()) {
        int a = plus.back(); plus.pop_back();
        int b = minus.back(); minus.pop_back();
        sol.pb({a, b});
        if (a == b) zero++;
        if (a > b) plus.pb(a-b);
        if (a < b) minus.pb(b-a);
    }
    while (zero) --zero, sol.pb({0, 0});
    return sol;
}

pair<int, vector<ii>> smart_brute(vector<int> v) {
    int n = sz(v);
    for (int i = 0; i < (1 << n); ++i) {
        int s = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) s += v[j];
            else s -= v[j];
        }
        if (s == 0) {
            return {true, vector<ii>(1)};
        }
    }
    return {false, {}};
}

vector<ii> brute(int n, vector<int> v) {
    auto ans = smart_brute(v).second;
    reverse(all(ans));
    return ans;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    auto ans = solve(n, v);
	//auto ans2 = brute(n, v);
    if (ans.empty()) cout << -1 << endl;
    else {
        for (auto [x, y] : ans) cout << x << ' ' << y << endl;
    }
#else
    int t = 1;
    while (t) {
        int n = rnd(1, 15);
        vector<int> v(n);
        for (auto& x : v) x = rnd(1, 1000);
		cout << n << endl;
		for (auto x : v) cout << x << ' ';
		cout << endl;
        auto my = solve(n, v);
        auto ans = brute(n, v);
        if (my.empty() != ans.empty()) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
            cout << "Certificate: ";
            cout << endl;
            for (auto [x, y] : ans) cout << x << ' ' << y << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
