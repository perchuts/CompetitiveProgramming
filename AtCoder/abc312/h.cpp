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
    int n; cin >> n;
    auto kmp = [] (string s) {
        int n = sz(s);
        vector<int> pi(n);
        for (int i = 1, j = 0; i < n; ++i) {
            while (j and s[i] != s[j]) j = pi[j-1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    };
    map<string, vector<ii>> mp;
    vector<int> ans(n, 1);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        auto pi = kmp(s);
        int p = sz(s) - pi.back();
        if (sz(s) % p == 0) mp[s.substr(0, p)].pb({sz(s), i});
        else mp[s].pb({sz(s), i});
    }
    vector<int> mex(maxn);
    iota(all(mex), 0);
    for (auto [sx, v] : mp) {
        map<int, int> mark;
        for (auto [x, y] : v) {
            while (mark[mex[x]]) mex[x] += x;
            ans[y] = mex[x] / x;
            mark[mex[x]] = true;
        }
        for (auto [x, y] : v) mex[x] = x;
    }
    for (auto x : ans) cout << x << endl;
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
