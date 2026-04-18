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

int dp[2002][2002];

void solve() {
    int n, h; cin >> n >> h;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (n == 1) {
        cout << h - a[0] << endl;
        return;
    }
    int ans = 0;
    vector<int> antes(n), depois(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] < h) {
            int mx = a[i];
            for (int j = i-1; j >= 0; --j) {
                ckmax(mx, a[j]);
                antes[i] += h - mx;
            }
            mx = a[i];
            for (int j = i + 1; j < n; ++j) {
                ckmax(mx, a[j]);
                depois[i] += h - mx;
            }
            ckmax(ans, antes[i] + depois[i] + h - a[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        int mx = a[i], S_esq = h - mx;
		dp[i][i] = h - mx;
        for (int j = i + 1; j < n; ++j) {
            dp[i][j] = dp[i][j-1];
			if (ckmax(mx, a[j])) {
				S_esq += h - mx;
				dp[i][j] = S_esq;
			} else S_esq += h - mx;
        }
    }
    for (int j = n-1; ~j; --j) {
        int mx = 0, S_dir = 0, cur_add = 0;
        for (int i = j; i >= 0; --i) {
            if (mx <= a[i]) {
                cur_add = S_dir;
                mx = a[i];
            }
            dp[i][j] += cur_add;
            S_dir += h - mx;
            ckmax(ans, dp[i][j] + antes[i] + depois[j]);
        }
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
