#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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

int solve(int n, int k, int m, vector<vector<ii>> intr) {
	map<int, int> mp;
    for (int i = 0; i < k; ++i) {
        for (auto [l, r] : intr[i]) {
            mp[l] ^= (1 << i);
            mp[r+1] ^= (1 << i);
        }
    }
    vector<int> cnt(1<<k);
    int cm = 0, lst = 0;
	for (auto [x, y] : mp) {
		cnt[cm] += x - lst;
		cm ^= y;
		lst = x;
	}
	cnt[cm] += n-lst;
    vector<vector<int>> sos(k+1, vector<int>(1<<k));
    sos[k] = cnt;
    for (int i = k-1; ~i; --i) {
        for (int j = 0; j < (1 << k); ++j) {
            sos[i][j] = sos[i+1][j];
            if (j >> i & 1) sos[i][j] += sos[i+1][j-(1<<i)];
        }
    }
    int z = (1 << k) - 1, ans = 0;
    for (int i = 1; i < (1 << k); ++i) {
        int bad = sos[0][z ^ i];
        for (int j = 0; j < k; ++j) {
            if (i >> j & 1) {
                int bicho = (z ^ i) + (1 << j);
                bad += sos[0][bicho];
                bad -= sos[0][bicho - (1 << j)];
            }
        }
        if (bad <= n-m) ans++;
    }

    // dado um subset S, ele é bom se:
    // m <= \sum {S \cap i > 1} cnt[i]
    // => 
    // n-m >= \sum {S \cap i <= 1} cnt[i]
    // = sos[compl(S)][0] + \sum {S \cap i = 1} cnt[i]
    // S \cap i = 1 iff i = (1 << j) + some subset of compl(S).
    // wnat about a sos dp with forced bit 1?
    return ans;
}
int brute(int n, int k, int m, vector<vector<pair<int, int>>> intr) {
    int ans = 0;
    for (int i = 1; i < (1 << k); ++i) {
        vector<int> p(n+1);
        for (int j = 0; j < k; ++j) {
            if (i >> j & 1) {
                for (auto [x, y] : intr[j]) p[x]++, p[y+1]--;
            }
        }
        int z = 0, x = 0;
        for (int j = 0; j < n; ++j) {
            x += p[j];
            if (x >= 2) z++;
        }
        ans += (z >= m);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, k, m; cin >> n >> k >> m;
    vector<vector<pair<int, int>>> intr(k);
    for (int i = 0; i < k; ++i) {
        int c; cin >> c;
        intr[i].resize(c);
        for (auto& [x, y] : intr[i]) cin >> x >> y, --x, --y;
    }
    cout << solve(n, k, m, intr) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10), k = rnd(1, 10), m = rnd(1, k);
        vector<vector<pair<int, int>>> intr(k);
        for (auto& v : intr) {
            int z = rnd(1, (1<<n)-1);
            int st = -1;
            for (int w = 0; w <= n; ++w) {
                int b = z >> w & 1;
                if (st == -1 and b) st = w;
                if (st != -1 and b == 0) v.push_back({st, w-1}), st = -1;
            }
        }
        int my = solve(n, k, m, intr);
        int ans = brute(n, k, m, intr);
        if (my != ans) {
            cout << "WA " << t << endl;
            cout << n << " " << k << " " << m << endl;
            for (int i = 0; i < k; ++i) {
                cout << intr[i].size() << endl;
                for (int j = 0; j < intr[i].size(); ++j) cout << intr[i][j].first+1 << " " << intr[i][j].second+1 << endl;
            }
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "AC " << t++ << endl;
    }
#endif
}

