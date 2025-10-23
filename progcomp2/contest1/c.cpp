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
    string s; cin >> s;
    int n = sz(s), waste = n - 1;
    map<char, int> freq;
    for (auto x : s) freq[x]++;
    vector<int> pp(n+1);
    pp[1] = 1;
    for (int i = n/2+1; i <= n; ++i) {
        bool ok = 1;
        for (int j = 2; j * j <= i; ++j) ok &= (i % j != 0);
        if (ok) waste--, pp[i] = 1;
    }
    
    char choice = '#';
    for (auto [x, y] : freq) {
        if (y >= waste) {
            choice = x; break;
        }
    }
    if (choice == '#') {
        cout << "NO" << endl;
        exit(0);
    }
    cout << "YES" << endl;
    string ss;
    for (int i = 0; i < freq[choice]; ++i) ss += choice;
    for (auto [x, y] : freq) {
        if (x == choice) continue;
        for (int i = 0; i < y; ++i) ss += x;
    }
    string ans(n, '#');
    for (int i = n; i; --i) {
        if (pp[i]) ans[i-1] = ss.back(), ss.pop_back();
    }
    for (int i = 1; i <= n; ++i) {
        if (pp[i] == 0) ans[i-1] = ss.back(), ss.pop_back();
    }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
