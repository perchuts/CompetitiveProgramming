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
    vector<vector<int>> div(N);
    vector<int> meb(N);
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) div[j].pb(i);
    }
    vector<int> qt(N), tmp(N); 
    int ans = 0, pw = 0;
    int n; cin >> n;
    for (int z = 0; z < n; ++z) {
        int x; cin >> x;
        int S = 0;
        for (int i = sz(div[x])-1; ~i; --i) {
            int k = div[x][i];
            int w = x/k;
            tmp[k] = qt[k];
            for (int j = 1; j < sz(div[w]); ++j) tmp[k] -= tmp[div[w][j]*k];
            tmp[k] %= mod; 
            if (tmp[k] < 0) tmp[k] += mod;
            S += tmp[k] * k;
        }
        ans = (2*ans + S) % mod;
        cout << ans << endl;
        pw = max(1LL, (pw + pw) % mod);
        for (auto d : div[x]) {
            qt[d] += pw;
            if (qt[d] >= mod) qt[d] -= mod;
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
