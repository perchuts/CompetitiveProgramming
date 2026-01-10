#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    string s, t; cin >> s >> t;
    int n = sz(s), m = sz(t);
    vector<vector<int>> cnt(2, vector<int>(26));
    for (auto x : s) cnt[0][x-'a']++;
    for (auto x : t) cnt[1][x-'a']++;
    for (int i = 0; i < 26; ++i) {
        if (cnt[0][i] > cnt[1][i]) {
            cout << "Impossible" << endl;
            return;
        }
    }
    // sempre poe a menor letra possivel, que ainda permite que eu consiga escrever tudo no fim.
    string z;
    int pos = 0;
    for (int i = 0; i < m; ++i) {
        char c = '$';
        for (int j = 0; j < 26; ++j) {
            if (cnt[1][j] == 0) continue;
            if (cnt[0][j] <= cnt[1][j]-1 or (pos != n and s[pos] == char('a' + j))) { 
                c = char('a' + j);
                break;
            }
        }
        cnt[1][c-'a']--;
        if (pos != n and s[pos] == c) cnt[0][c-'a']--, pos++;
        z += c;
    }
    cout << z << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
