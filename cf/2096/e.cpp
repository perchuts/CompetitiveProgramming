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


int solve(int n, string s){
    int inv = 0, q1 = 0, q2 = 0;
    for (auto x : s) {
        if (x == 'B') inv += q2, q1++;
        else q2++;
    }
    string ss = s;
    sort(all(ss));
    vector<vector<vector<int>>> c(2, vector<vector<int>>(2, vector<int>(2)));
    for (int i = 0; i < n; ++i) {
        c[0][i&1][(s[i]=='P')]++;
        c[1][i&1][(ss[i]=='P')]++;
    }
    int ans = abs(c[0][0][0]-c[1][0][0]);
    ans += (inv-ans)/2;
    return ans;
}

pair<int, vector<ii>> brute(int n, string s) {
    vector<int> dp(1<<n, -1);
    vector<ii> tr(1<<n, {-1, -1});
    vector<int> v(n);
    int target = 0, cp = 0, ini = 0;
    for (int i = 0; i < n; ++i) v[i] = (s[i] == 'P'), cp += v[i], ini += (v[i]<<i);
    for (int i = n-cp; i < n; ++i) target += 1<<i;
    auto bit = [&] (int m, int k) { return m>>k&1; };
    auto go = [&] (auto&& self, int mask) -> int {
        assert(__builtin_popcount(mask) == cp);
        if (mask == target) return 0LL;
        if (dp[mask] != -1) return dp[mask];
        dp[mask] = inf;
        for (int i = 0; i < n-1; ++i) {
            if (bit(mask, i) > bit(mask, i+1)) {
                if (ckmin(dp[mask], self(self, mask-(1<<i)+(1<<(i+1)))+1)) tr[mask] = {mask-(1<<i)+(1<<(i+1)), 1};
            }
            if (i < n-2 and bit(mask, i) > bit(mask, i+2)) {
                if (ckmin(dp[mask], self(self, mask-(1<<i)+(1<<(i+2)))+1)) tr[mask] = {mask-(1<<i)+(1<<(i+2)), 2};
            }
        }
        return dp[mask];
    };
    int ans = go(go, ini);
    vector<ii> states = {{ini, 0}};
    while (ini != target) {
        states.pb(tr[ini]);
        ini = tr[ini].first;
    }
    states.pb({target, -1});
    return {ans, states};
}
int32_t main(){_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        cout << solve(n, s) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(25, 28);
        string s;
        int c = 0, inv = 0;
        for (int i = 0; i < n; ++i) {
            s += (rnd(0, 1) ? "P" : "B");
            if (s.back() == 'P') c++;
            else inv += c;
        }
        int my = solve(n, s);
        auto [ans, cert] = brute(n, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl << s << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            cout << "Certificate: " << endl;
            for (auto [x, y] : cert) {
                for (int i = 0; i < n; ++i) cout << (x>>i&1);
                cout << " " << y << endl;
            }
            cout << "inversions: " << inv << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
