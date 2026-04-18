#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    vector<int> pot(10, 1);
    for (int i = 1; i <= 9; ++i) {
        pot[i] = 10 * pot[i-1];
        cout << "? " << pot[i] << endl;
        string s; cin >> s;
        if (s[0] == 'Y') continue;
        else {
            int ans = 0;
            for (int digit = i-1; digit; --digit) {
                int l = (digit == i-1), r = 9, correct = -1;
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    cout << "? " << (ans + pot[digit] * md)/pot[digit] << endl;
                    cin >> s;
                    if (s[0] == 'Y') correct = md, l = md+1;
                    else r = md-1;
                }
                ans += pot[digit] * correct;
            }
            for (int z = (i==1); z <= 9; ++z) {
                cout << "? " << 10 * (ans+z) << endl;
                cin >> s;
                if (s[0] == 'Y') {
                    cout << "! " << ans+z << endl;
                    exit(0);
                }
            }
            assert(false);
        }
    }
    for (int i = 0; ; ++i) {
        cout << "? " << 2 * pot[i] << endl;
        string s; cin >> s;
        if (s[0] == 'Y') {
            cout << "! " << pot[i] << endl;
            exit(0);
        }
    }
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
