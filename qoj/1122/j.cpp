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
    struct carta {
        char val, tipo;
    };
    vector<carta> v;
    string s;
    auto go = [&] () {
        int action = -1;
        for (int i = sz(v)-4; i >= 0; --i) {
            if (v[i].val == v[i+3].val) {
                action = i;
                break;
            }
        }
        if (action != -1) {
            v.erase(begin(v)+action, begin(v)+action+4);
            return true;
        }
        for (int i = sz(v)-4; i >= 0; --i) {
            if (v[i].tipo == v[i+3].tipo) {
                action = i;
                break;
            }
        }
        if (action != -1) {
            v.erase(begin(v)+action+3);
            v.erase(begin(v)+action);
            return true;
        }
        return false;
    };
    while (cin >> s) {
        carta c;
        c.val = s[0];
        c.tipo = s[1];
        v.pb(c);
        while (go()) { }
    }
    cout << sz(v) << ' ';
    for (auto x : v) cout << x.val << x.tipo << " ";
    cout << endl;
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
