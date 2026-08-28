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
    int n; cin >> n;
    vector<int> v((1<<n));
    for (int i = 1; i < (1 << n); ++i) cin >> v[i];
    // conte as mascaras M tais que:
    // popcount(M & i) eh um bit ligado de V_i, pra  1<=i<2^n
    // entao V_i representa quais os tamanhos de intersecao que M pode ter com i
    vector<int> tudo = v;
    tudo[0] = (1 << (n+1))-1;
    for (int i = (1<<n)-1; ~i; --i) {
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {}
            else tudo[i] &= tudo[i + (1 << j)];
        }
    }
    for (int i = 0; i < (1 << n); ++i) {
        cout << bitset<6>(tudo[i]) << ' ';
    }
    cout << endl;
    vector<int> nice(1<<n), ans;
    for (int i = 0; i < (1 << n); ++i) {
        int t = __builtin_popcount(i);
        if (tudo[i] >> t & 1) nice[i] += (1 << t);
        if (t > 1) {
            int other = (1 << t) - 1;
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) other &= nice[i - (1 << j)];
            }
            nice[i] |= other;
        }
        if (nice[i] == (1 << (t+1)) - 1) ans.pb(i);
        cout << bitset<6>(nice[i]) << " ";
    }
    cout << endl;
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << endl;
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
