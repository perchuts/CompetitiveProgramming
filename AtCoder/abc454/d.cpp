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
    string a, b; cin >> a >> b;
    auto process = [&] (string s) {
        string t;
        int tam = sz(s);
        vector<int> foi(tam);
        for (int i = 3; i < tam; ++i) {
            if (s[i] == ')' and s[i-1] == 'x' and s[i-2] == 'x' and s[i-3] == '(') {
                foi[i] = foi[i-1] = foi[i-2] = foi[i-3] = 1;
                foi[i-1] = foi[i-2] = 0;
                for (int j = 1; ; ++j) {
                    if (i+j == tam or i-3-j == -1) break;
                    if (s[i+j] != ')' or s[i-3-j] != '(') break;
                    foi[i+j] = foi[i-3-j] = 1;
                }
            }
        }
        for (int i = 0; i < tam; ++i) if (!foi[i]) t += s[i];
        return t;
    };
    cout << (process(a) == process(b) ? "Yes" : "No") << endl;
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
