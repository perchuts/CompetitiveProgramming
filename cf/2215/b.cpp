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
vector<vector<int>> divs;
const int L = 10000;
const int N = 1e12;

int d[50];

map<int, int> rec;

void solve() {
    int n; cin >> n;
    int ans = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i) continue;
        int a = i, b = n / i;
        if (a <= b-2) ans++;
        int z = rec[b];
        if (a < z and z > L) ans++;
    }
    for (int b = 2; b <= L; ++b) {
        int cur = n, t = 0;
        while (cur) d[t++] = cur % b, cur /= b;
        if (t <= 2) break;
        bool mark = 0;
        for (auto p : divs[t]) {
            int repr = 0;
            bool ok = 1;
            for (int i = 0; i < t; i += p) {
                for (int j = 0; j < p; ++j) {
                    ok &= d[i] == d[i+j];
                }
            }
            ans += ok;
        }
    }
    cout << ans << endl;
}

int32_t main() {_
    divs.resize(L+1);
    int S = 0;
    //for (int i = 1; i <= L; ++i) {
    //    for (int j = 1; j <= i; ++j) {
    //        d[i] += (i % j == 0);
    //    }
    //    ckmax(d[i], d[i-1]);
    //}
    for (int i = 1; ; ++i) {
        int T = i * i + i + 1;
        if (T > N) break;
        rec[T] = i;
    }
    for (int i = 2; i <= L; ++i) {
        //tot += d[sz(pw[i])] * sz(pw[i]);
        for (int j = 1; j * j <= i; ++j) {
            if (i % j) continue;
            if (j != 1) divs[i].pb(j);
            if (j * j != i) divs[i].pb(i/j);
        }
    }
    //cout << tot*1000/1e8 << endl;
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
