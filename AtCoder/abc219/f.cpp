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

int solve(string s, int k){
    set<ii> pr; pr.insert({0, 0});
    int a = 0, b = 0;
    vector<ii> v;
    for (auto x : s) {
        if (x == 'L') v.pb({-1, 0});
        if (x == 'R') v.pb({1, 0});
        if (x == 'U') v.pb({0, 1});
        if (x == 'D') v.pb({0, -1});
        a += v.back().first;
        b += v.back().second;
        pr.insert({a, b});
    }
    if (a == 0 and b == 0) return sz(pr);
    int c1 = 0, c2 = 0;
    if (a == 0) swap(a, b), c1 = 1;
    if (a < 0) a *= -1, b *= -1, c2 = 1;
    for (auto& [x, y] : v) {
        if (c1) swap(x, y);
        if (c2) x *= -1, y *= -1;
    }
    auto get = [&] (int x, int y) {
        int dx = x/a;
        if (x - dx*a < 0) dx--;
        return make_pair(x - dx*a, y - dx*b);
    };
    map<ii, set<int>> ss;
    int cx = 0, cy = 0, ans = 1;
    for (int i = sz(s)-1; ~i; --i) {
        auto h = get(-cx, -cy);
        ss[h].insert(-cx);
        cx += v[i].first, cy += v[i].second;
    }
    pr.clear(), pr.insert({0, 0});
    cx = cy = 0;
    for (auto [dx, dy] : v) {
        cx += dx, cy += dy;
        if (pr.find({cx, cy}) != end(pr)) continue;
        pr.insert({cx, cy});
        auto it = ss[get(cx, cy)].lower_bound(cx);
        int val = k;
        if (it != end(ss[get(cx, cy)])) {
            int z = 1;
            auto [aa, bb] = get(cx, cy);
            if (aa == 0 and bb == 0 and (*it) == 0) z = 0;
            ckmin(val, ((*it)-cx)/a+z);
        }
        ans += val;
    }
    //cout << endl;
    return ans;
}

int brute(string s, int k) {
    set<ii> vis;
    int n = sz(s);
    int cx = 0, cy = 0;
    vis.insert({cx, cy});
    vector<ii> v;
    for (int i = 0; i < n*k; ++i) {
        auto x = s[i%n];
        if (x == 'L') v.pb({-1, 0});
        if (x == 'R') v.pb({1, 0});
        if (x == 'U') v.pb({0, 1});
        if (x == 'D') v.pb({0, -1});
        cx += v.back().first, cy += v.back().second;
		vis.insert({cx, cy});
        v.pop_back();
    }
    return sz(vis);
}

int32_t main() {_
#ifndef gato
    string s; int k; cin >> s >> k;
    cout << solve(s, k) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20);
        string s(n, '#');
        vector<char> ch = {'L', 'R', 'U', 'D'};
        for (auto& x : s) x = ch[rnd(0, 3)];
        int k = rnd(1, 100);
        int my = solve(s, k);
        int ans = brute(s, k);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << s << endl << k << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
