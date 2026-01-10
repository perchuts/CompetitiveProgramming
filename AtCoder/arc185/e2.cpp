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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int N = 1e5+1;
    vector<int> phi(N), jump(N), mark(N);
    jump[1] = phi[1] = 1;
    for (int i = 2; i < N; ++i) {

        if (!mark[i]) {
            for (int j = i * i; j < N; j += i) if (!mark[j]) mark[j] = i;
            jump[i] = 1;
            phi[i] = i-1;
            continue;
        }

        if (i % (mark[i]*mark[i])) jump[i] = i/mark[i];
        else jump[i] = jump[i/mark[i]];

        if (jump[i] == 1) phi[i] = i - i/mark[i];
        else phi[i] = phi[jump[i]] * phi[i/jump[i]];
    }
    vector<vector<int>> div(N);
    for (int i = 1; i < N; ++i) for (int j = i; j < N; j += i) div[j].pb(i);
    int n; cin >> n;
    int ans = 0, pw = 1;
    vector<int> sexo(N);
    for (int __ = 0; __ < n; ++__) {
        ans = (ans + ans) % mod;
        int x; cin >> x;
        for (auto d : div[x]) ans = (ans + phi[d] * sexo[d]) % mod;
        // gcd(x, y) = sum phi(d) * [d|n] * [d|m] = sum{d|n} phi(d) * [d|m]
        // entao temos 2^{j-1} sum{d|x} phi(d) * [d|a[j]]
        // phi(d) 2^{j-1} [d|a[j]]
        cout << ans << endl;
        for (auto d : div[x]) sexo[d] = (sexo[d] + pw) % mod;
        pw = (pw + pw) % mod;
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
