#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
const int mod = 1e9+9;
const int maxn = 1e5+10;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

//template<typename T> vector<int> pi(T s) {
//	vector<int> p(s.size());
//	for (int i = 1, j = 0; i < s.size(); i++) {
//		while (j and s[j] != s[i]) j = p[j-1];
//		if (s[j] == s[i]) j++;
//		p[i] = j;
//	}
//	return p;
//}
vector<int> multis[maxn];
int solve(int n, vector<vector<int>> g, string s){
    int ans = 0;
    vector<int> tam(n+1);
    for (int i = 2; i <= n; ++i) tam[i] = 1 + tam[i/2];
    string act = "";
    vector<unordered_map<int, int>> sexo(n);
    int P = rnd(256, mod-1);
    vector<int> h(n), p(n+1, 1);
    for (int i = 1; i <= n; ++i) p[i] = p[i-1] * P % mod;
    auto get = [&] (int l, int r) {
		ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%mod : 0);
		return hash < 0 ? hash + mod : hash;
    };
    auto dfs = [&] (auto&& self, int u, int t) -> void {
        if (u) {
            act += s[u-1];
            if (sz(act) == 1) h[t-1] = act[t-1];
            else h[t-1] = (h[t-2] * P + act.back()) % mod;
            sexo[t].clear();
            int eu = inf;
            for (auto divi : multis[t]) {
                if (get(t-divi, t-1) == h[divi-1] and (divi*2 == t or sexo[t-divi].count(divi))) sexo[t][divi] = 1, ckmin(eu, divi);
            }
            if (eu == inf) eu = 0;
            ckmax(ans, eu);
        }
        for (auto v : g[u]) self(self, v, t+1);
        act.pop_back();
    };
    dfs(dfs, 0, 0);
    return ans;
}

int correct(int n, vector<vector<int>> g, string s) {
    int ans = 0;
    vector<int> pi;
    string act = "";
    auto dfs = [&] (auto&& self, int u) -> void {
        if (u) {
            act += s[u-1];
            if (pi.empty()) {
                pi.pb(0);
            } else {
                int j = pi.back();
                while (j and act[j] != act.back()) j = pi[j-1];
                if (act[j] == act.back()) j++;
                pi.pb(j);
                if (j and sz(act) % (sz(act)-j) == 0) ckmax(ans, sz(act) - j);
            }
        }
        for (auto v : g[u]) self(self, v);
        pi.pop_back();
        act.pop_back();
    };
    dfs(dfs, 0);
    return ans;
}

int32_t main(){_
    for (int i = 1; i < maxn; ++i) {
        for (int j = 2*i; j < maxn; j += i) {
            multis[j].pb(i);
        }
    }
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p; cin >> p;
        --p;
        g[p].pb(i);
    }
    string s; cin >> s;
    cout << solve(n, g, s) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 30);
        vector<vector<int>> g(n);
        vector<int> p(n-1);
        for (int i = 1; i < n; ++i) {
            p[i-1] = rnd(0, i-1);
            g[p[i-1]].pb(i);
        }
        string s; 
        for (int i = 0; i < n-1; ++i) s.pb(char('a'+rnd(0, 1)));
        int my = solve(n, g, s), ans = correct(n, g, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x+1 << ' ';
            cout << endl;
            cout << s << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
