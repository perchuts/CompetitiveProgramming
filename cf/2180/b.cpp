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

string solve(int n, vector<string> sexo) {
    // well, the first one obviously will be
    string ans = sexo[0];
    for (int i = 1; i < n; ++i) {
        string o1 = sexo[i] + ans;
        string o2 = ans + sexo[i];
        ans = min(o1, o2);
    }
    return ans;
}

string brute(int n, vector<string> sexo) {
    vector<int> p(n); iota(all(p), 0);
    string ans;
    for (int i = 0; i < (1 << n); ++i) {
        string cur;
        vector<int> frente, tras;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) frente.pb(j);
            else tras.pb(j);
        }
        reverse(all(frente));
        for (auto x : frente) cur += sexo[x];
        for (auto x : tras) cur += sexo[x];
        if (ans.empty() or cur < ans) ans = cur;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
    int n; cin >> n;
    vector<string> sexo(n);
    for (auto& x : sexo) cin >> x;
    auto ans = solve(n, sexo);
    cout << ans << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 10);
        vector<string> sexo;
        for (int i = 0; i < n; ++i) {
            int t = rnd(1, 10);
            string s;
            for (int j = 0; j < t; ++j) s += char('a' + rnd(0, 10));
            sexo.pb(s);
        }
        auto my = solve(n, sexo);
        auto ans = brute(n, sexo);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : sexo) cout << x << ' ';
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
