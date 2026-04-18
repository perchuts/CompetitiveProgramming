#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

string solve(int n, vector<vector<int>> a) {
    vector<int> state(n);
    while (true) {
        bool z = 0;
        for (int i = 0; i < n; ++i) {
            int val = 0;
            for (int j = 0; j < n; ++j) {
                if (state[i] == state[j]) val += a[i][j];
                else val -= a[i][j];
            }
            if (val < 0) {
                state[i] ^= 1;
                z = 1;
                break;
            }
        }
        if (z == 0) break;
    }
    string s;
    for (int i = 0; i < n; ++i) s += (state[i] ? "X" : "Y");
    return s;
}

string brute(int n, vector<vector<int>> a) {
    vector<int> tipos(n);
    string ans = "$";
    int ruim = 0, bom = 0;
    int mxs = 0, mxs2 = 0;
    vector<int> nice(1<<n), sum(1<<n);
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) tipos[j] = (i >> j) & 1;
        bool ok = 1;
        int ss = 0;
        for (int j = 0; j < n; ++j) {
            int s = 0;
            for (int k = 0; k < n; ++k) {
                if (tipos[j] == tipos[k]) s += a[j][k], ss += a[j][k];
                else s -= a[j][k], ss -= a[j][k];
            }
            ok &= (s >= 0);
        }

        nice[i] = ok;
        sum[i] = ss;
        ckmax(mxs, ss);
        if (ok) {
            ckmax(mxs2, ss);
            //ans.clear();
            //for (int j = 0; j < n; ++j) { ans += (tipos[j] ? "X" : "Y"); }
        } 

    }
    for (int i = 0; i < (1<<n); ++i) {
        if (sum[i] == mxs) {
            if (nice[i]) bom++;
            else ruim++;
        }
    }
    cout << mxs << endl;
    assert(ruim == 0);
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& x : a) for (auto& y : x) cin >> y;
    cout << solve(n, a) << endl;
#else
    int t = 10;
    while (true) {
        int n = rnd(1, 10);
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                a[i][j] = a[j][i] = rnd(-50, 50);
            }
        }
        auto my = solve(n, a);
        auto ans = brute(n, a);
        //if (my == "$") {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << n << endl;
        //    for (int i = 0; i < n; ++i) {
        //        for (int j = 0; j < n; ++j) cout << a[i][j] << " ";
        //        cout << endl;
        //    }
        //    cout << "Solve: " << my << endl;
        //    cout << "Brute: " << ans << endl;
        //    exit(0);
        //}
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
