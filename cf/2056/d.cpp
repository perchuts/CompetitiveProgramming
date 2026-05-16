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

int solve(int n, vector<int> a) {
    int ans = (n+1)*n/2;

    vector<vector<int>> ps(11, vector<int>(n));

    for (int i = 1; i <= 10; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) ps[i][j] = ps[i][j-1];
            ps[i][j] += (a[j] <= i ? 1 : -1);
        }
    }
    //for (int m = 1; m <= 10; ++m) {
    //    for (int i = 0; i < n; ++i) cout << ps[m][i] << " ";
    //    cout << endl;
    //}

    for (int m = 1; m < 10; ++m) {
        for (int i = 0; i < 2; ++i) {
            map<ii, int> mp;
            map<int, int> mp2;
            if (i == 1) mp[{0, 0}] = 1, mp2[0] = 1;
            for (int j = 0; j < n; ++j) {
                if ((j & 1) == i) {
                    ans += mp[{ps[m][j], ps[m+1][j]}];
                    ans -= mp2[ps[m][j]];
                    mp[{ps[m][j], ps[m+1][j]}]++;
                    mp2[ps[m][j]]++;
                }
            }
        }
    }
    return ans;
}

int brute(int n, vector<int> a) {
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        vector<int> b;
        for (int r = l; r < n; ++r) {
            b.pb(a[r]);
            sort(all(b));
            ans += (b[(r-l+1)/2] == b[(r-l)/2]);
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 40);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 10);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
