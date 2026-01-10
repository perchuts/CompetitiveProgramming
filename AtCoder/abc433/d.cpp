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
    int n, m; cin >> n >> m;
    vector<int> v(n);
    vector<unordered_map<int, int>> mods(11);
    vector<int> pot(11, 1);
    for (int i = 1; i <= 10; ++i) pot[i] = 10 * pot[i-1] % m;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        string s = to_string(v[i]);
        for (int j = 1; j <= 10; ++j) {
            mods[j][(v[i] * pot[j]) % m]++;
        }
        int eu = (m - v[i]) % m; eu = (eu + m) % m;
        ans += mods[sz(s)][eu];
    }
    for (int i = 1; i <= 10; ++i) mods[i].clear();
    for (int i = n-1; ~i; --i) {
        string s = to_string(v[i]);
        int eu = (m - v[i]) % m; eu = (eu + m) % m;
        ans += mods[sz(s)][eu];
        for (int j = 1; j <= 10; ++j) {
            mods[j][(v[i] * pot[j]) % m]++;
        }
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
