#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
const int maxn = 6e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<string> kernel(vector<string> s) {
    sort(all(s));
    s.erase(unique(all(s)), end(s));
    vector<string> ns = {s[0]};
    for (auto x : s) {
        if (sz(x) > sz(ns.back()) and x.substr(0, sz(ns.back())) == ns.back()) ns.pb(x);
    }
    return ns;
}
const int LOG = 24;
int trie[maxn][10], par[maxn][LOG], lvl[maxn];
char cc[maxn];

string solve(int n, int k, vector<string> s) {
    s = kernel(s), n = sz(s);
    auto ssx = s.back(); sort(all(ssx)), ssx.erase(unique(all(ssx)), end(ssx));
    vector<char> id(300);
    for (int i = 0; i < ssx.size(); ++i) id[ssx[i]] = i;
    int N = k * sz(s.back()), h = 0;
    vector<int> opt(N+1, -inf), where(N+1);
    opt[0] = 0; 
    for (int i = 0; i < LOG; ++i) par[0][i] = -1;
    auto lca = [&] (int u, int v) {
        int t = 0;
        if (lvl[u] < lvl[v]) swap(u, v), t = 1;
        for (int i = LOG-1; ~i; --i) {
            if (par[u][i] != -1 and lvl[par[u][i]] >= lvl[v]) u = par[u][i];
        }
        if (u == v) return pair(-1, -1);
        for (int i = LOG-1; ~i; --i) {
            if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
        }
        if (t) swap(u, v);
        return pair(u, v);
    };
    auto cmp = [&] (int u, int i, int v, int j) {
        auto [uu, vv] = lca(u, v);
        if (uu == -1) {
            if (i == -1) return (lvl[u] < lvl[v] ? -1 : 1);
            int t = 1;
            if (lvl[u] < lvl[v]) swap(u, v), swap(i, j), t = -1;
            string sx;
            while (u != v) sx += cc[u], u = par[u][0];
            reverse(all(sx)); sx += s[i];
            if (sx == s[j]) return 0;
            return t * (sx < s[j] ? -1 : 1);
        }
        return (cc[uu] < cc[vv] ? -1 : 1);
    };
    auto add = [&] (int u, int i) {
        for (auto c : s[i]) {
            if (trie[u][id[c]] == 0) {
                trie[u][id[c]] = ++h;
                lvl[h] = 1 + lvl[u], par[h][0] = u, cc[h] = c;
                for (int j = 1; j < LOG; ++j) {
                    if (par[h][j-1] == -1) par[h][j] = -1;
                    else par[h][j] = par[par[h][j-1]][j-1];
                }
            }
            u = trie[u][id[c]];
        }
        return u;
    };
    int ans = -1;
    for (int i = 1; i <= N; ++i) {
        ii best = {-1, -1};
        for (int w = 0; w < sz(s); ++w) {
            int j = sz(s[w]);
            if (j > i) break;
            if (opt[i-j] < 0) continue;
            if (best.first == -1) best = {where[i-j], w}, opt[i] = 1 + opt[i-j];
            else {
                int res = cmp(where[i-j], w, best.first, best.second);
                if (res < 0) opt[i] = 1 + opt[i-j], best = {where[i-j], w};
                else if (res == 0) ckmax(opt[i], 1 + opt[i-j]);
            }
        }
        if (best.first == -1) continue;
        where[i] = add(best.first, best.second);
        if (opt[i] == k) {
            if (ans == -1) ans = i;
            else if (cmp(where[i], -1, where[ans], -1) < 0) ans = i;
        }
    }
    string res;
    int cur = where[ans];
    while (cur) res += cc[cur], cur = par[cur][0];
    reverse(all(res));
    return res;
}

string brute(int n, int k, vector<string> s) {
    s = kernel(s), n = sz(s);
    int N = k * sz(s.back());
    vector<int> opt(N+1, -inf);
    vector<string> ss(N+1);
    opt[0] = 0;
    string ans;
    for (int i = 1; i <= N; ++i) {
        for (auto sx : s) {
            int j = sz(sx);
            if (j > i) break;
            if (opt[i-j] < 0) continue;
            if (ss[i].empty() or ckmin(ss[i], ss[i-j] + sx)) opt[i] = 1 + opt[i-j], ss[i] = ss[i-j] + sx;
            else if (ss[i] == ss[i-j] + sx) ckmax(opt[i], opt[i-j]);
        }
        if (opt[i] == k) {
            if (ans.empty()) ans = ss[i];
            else ckmin(ans, ss[i]);
        }
    }
    return ans;
}

string dumb(int n, int k, vector<string> s) {
	string best;
    string t;
    s = kernel(s); n = sz(s);
    auto go = [&] (auto&& self, int i) -> void {
        if (!best.empty() and best < t) return;
        if (i == k) {
			if (best.empty()) best = t;
			else ckmin(best, t);
            return;
        } 
        for (int j = 0; j < n; ++j) {
            t += s[j];
            self(self, i+1);
            for (int w = 0; w < sz(s[j]); ++w) t.pop_back();
        }
    };
    go(go, 0);
	return best;
}

int32_t main() {_
#ifndef gato
    int n, k; cin >> n >> k;
    vector<string> s(n);
    for (auto& x : s) cin >> x;
    cout << solve(n, k, s) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100), k = rnd(1, 100);
        vector<string> v(n);
        for (auto& x : v) {
            int m = rnd(1, 10);
            x = string(m, 'a');
            for (auto& y : x) y = char('a' + rnd(0, 25));
        }
        string my = solve(n, k, v), ans = brute(n, k, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            for (auto x : v) cout << x << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
