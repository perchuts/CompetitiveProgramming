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
    vector<vector<int>> a(n);
    int st = 0;
    for (int i = 0; i < n; ++i) {
        int lx; cin >> lx;
        st += lx;
        a[i].resize(lx);
        for (auto& y : a[i]) cin >> y;
        // avaliar o mex original de cada bicho
    }
    vector<int> help(st+4), mex(n), tot_freq(st+4);
    vector<vector<int>> freq(n);
    for (int i = 0; i < n; ++i) {
        int m = sz(a[i]);
        freq[i].resize(m+3);
        for (auto x : a[i]) {
            if (x <= m) help[x] = 1, freq[i][x]++;
            if (x <= st) tot_freq[x]++;
        }
        for (int j = 0; ; ++j) {
            if (help[j] == 0) {
                mex[i] = j;
                break;
            }
        }
        for (int j = 0; j <= m; ++j) help[j] = 0;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        // queries que eu mando algo pra algum bicho
        int m = sz(a[i]), tot_eu = m * (n-1);
        for (int j = 0; j < mex[i]; ++j) {
            if (freq[i][j] == 1) {
                ans += (n-1) * j;
                tot_eu -= (n-1);
            }
        }
        ans += tot_eu * mex[i];
        int nmex;
        for (int j = mex[i]+1; ; ++j) {
            if (freq[i][j] == 0) {
                nmex = j;
                break;
            }
        }
        ans += nmex * tot_freq[mex[i]];
        ans += (st-m-tot_freq[mex[i]]) * mex[i];
        // queries que nao me afetam
        ans += (n-2) * (st-m) * mex[i];
    }
    cout << ans << endl;
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
