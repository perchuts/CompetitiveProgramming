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

bool brute(vector<int> A, int K) { 
    sort(all(A));
    map<vector<int>, bool> state;
    auto go = [&state] (auto&& self, vector<int> a, int g) -> bool {
        if (a.empty()) return false;
        for (int i = 0; i < sz(a); ++i) {
            int gg = gcd(a[i], g);
            if (gg == 1) continue;
            auto b = a; b.erase(begin(b)+i);
            if (!self(self, b, gg)) return state[a] = true;
        }
        return state[a] = false;
    };
    return go(go, A, K);
}

vector<int> solve(vector<int> a){
	int mx = *max_element(all(a));
    vector<int> cnt(mx+1), f(mx+1);
    vector<vector<int>> div(mx+1);
    for (auto x : a) cnt[x]++;
    for (int i = 2; i <= mx; ++i) {
        for (int j = i; j <= mx; j += i) {
            f[i] += cnt[j];
            if (j != i) div[j].pb(i);
        }
    }
    vector<vector<int>> dp(mx+1, vector<int>(2));
    vector<int> g(mx+1);
    for (int i = 2; i <= mx; ++i) {
		reverse(all(div[i]));
		g[i] = f[i];
		for (auto d : div[i]) {
			g[d] = f[d] - g[i];
			for (auto d2 : div[i/d]) g[d] -= g[d*d2];
		}
        for (auto d : div[i]) {
			int tot = f[d] - f[i];
            if (g[d]) dp[i][0] |= !dp[d][(tot^1)&1];
        }
        dp[i][1] = !dp[i][0];
        for (auto d : div[i]) {
			int tot = f[d] - f[i];
            if (g[d]) dp[i][1] |= !dp[d][tot&1];
        }
    }
    vector<int> ans;
    for (auto x : a) ans.pb(dp[x][(f[x]&1)^1]^1);
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto ans = solve(a);
    for (auto x : ans) cout << (x ? "Takahashi" : "Aoki") << endl;
#else
    int t = 1;
    vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 23, 29};
    while (true) {
        int n = rnd(2, 10), g = 0;
        vector<int> a(n);
        vector<string> aa;
        for (auto& x : a) {
            string s;
            x = 1;
            for (int j = 0; j < sz(pr); ++j) {
                int k = rnd(0, 1);
                if (k == 1 and x * pr[j] > 1000) k = 0;
                s += char('0' + k);
                if (k) x *= pr[j];
            }
            aa.pb(s);
            g = gcd(x, g);
        }
        if (g != 1 or (*min_element(all(a)) == 1)) continue;
        //sort(all(aa), [](string a1, string a2) {
        //    int c1 = 0, c2 = 0;
        //    for (int i = 0; i < sz(a1); ++i) c1 += a1[i] - '0', c2 += a2[i] - '0';
        //    return c1 < c2;
        //});
        auto my = solve(a);
        vector<int> ans;
        for (int i = 0; i < sz(a); ++i) {
            auto b = a; b.erase(begin(b)+i);
            ans.pb(brute(b, a[i])^1);
        }
        
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: ";
            for (auto x : my) cout << (x ? "Taka" : "Aoki") << " ";
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << (x ? "Taka" : "Aoki") << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
