#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

string solve(int n, int a, int b, vector<int> d) {
    int S = 0;
    for (auto x : d) S += x;
    if ((S+a+b+(1<<29))%2) return "";
    int D = *max_element(all(d));
    vector<vector<int>> plus;
    auto solve = [&] (int target) {
        if (abs(target) > S) return false;
		cout << target << " " << S << endl;
        if (target == S) { plus.pb(vector<int>(n, 1)); return true; }
		if (target == -S) {
			plus.pb(vector<int>(n));
			return true;
		}
        int need = (S - target) / 2;
		vector<int> sum(n+1);
		for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + d[i-1];
        int i = 0, z = 0;
        while (z+d[i] <= need) z += d[i++];
        int lb = need-D;
        vector<vector<int>> dp(n+1, vector<int>(2*D+1, -inf)), vals(n+1);
        dp[i][z-lb] = i, vals[i].pb(z-lb);
        for (int r = i; r <= n; ++r) {
            for (int l = r; l; --l) {
                for (auto j : vals[l]) {
                    if (dp[r][j] != l) continue;
                    for (int l2 = l; l2 > max(0, dp[r-1][j]); --l2) {
                        int nv = j-d[l2-1]+lb;
                        if (lb <= nv and nv <= lb+2*D and ckmax(dp[r][nv-lb], l2-1)) vals[l2-1].pb(nv-lb);
                    }
                }
            }
            for (int j = 0; j <= n; ++j) vals[j].clear();
            if (r == n) continue;
            for (int j = lb; j <= lb+2*D; ++j) {
                if (dp[r][j-lb] < 0) continue;
                if (ckmax(dp[r+1][j-lb], dp[r][j-lb])) vals[dp[r][j-lb]].pb(j-lb);
                if (j+d[r] <= lb+2*D and ckmax(dp[r+1][j+d[r]-lb], dp[r][j-lb]+(dp[r][j-lb]==r))) vals[dp[r+1][j+d[r]-lb]].pb(j+d[r]-lb);
            }
        }
        cout << "need = " << need << " lb = " << lb << endl;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= 2*D; ++j) {
                cout << (dp[i][j]==-inf?-1:dp[i][j]) << "\t";
            }
            cout << endl;
        }
        int cur = need - lb;
        vector<int> not_use(n);
        if (dp[n][cur] < 0) return false;
		int esq = dp[n][cur]+1, dir = n;
		while (esq <= dir) {
			// consigo decidir pela esquerda??
			cout << esq << " " << dir << ' ' << cur << endl;
			int nv = cur + d[esq-1];
			if (nv <= 2*D and dp[dir][nv] >= esq) {
				not_use[esq-1] = true;
				cur = nv;
				esq = dp[dir][cur]+1;
				continue;
			}
			// devo conseguir decidir pela direita!
			if (esq == dp[dir-1][cur]) {
				not_use[dir-1] = true;
				dir--;
				continue;
			}
			cur -= d[dir-1], dir--;
		}
        plus.pb(not_use);
        return true;
    };
    if (!solve(a+b) or !solve(a-b)) return "";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << plus[i][j] << " \n"[j==n-1];
        }
    }

    string ans;
    for (int i = 0; i < n; ++i) {
        if (plus[0][i] == plus[1][i]) {
            if (plus[0][i] == 1) {
                ans += 'R';
            } else {
                ans += 'L';
            }
        } else if (plus[0][i] == 1) {
            ans += 'U';
        } else {
            ans += 'D';
        }
    }
    return ans;
}

bool brute(int x, int y, vector<int> d) {
    int n = sz(d);
    auto go = [&] (auto&& self, int xi, int yi, int i) -> bool {
        if (i == n) {
            if (xi == x and yi == y) return true;
            return false;
        }
        if (self(self, xi + d[i], yi, i+1)) return true;
        if (self(self, xi - d[i], yi, i+1)) return true;
        if (self(self, xi, yi - d[i], i+1)) return true;
        if (self(self, xi, yi + d[i], i+1)) return true;
        return false;
    };
    return go(go, 0, 0, 0);
}

int32_t main() {_
#ifndef gato
    int n, a, b; cin >> n >> a >> b;
    vector<int> d(n);
    for (auto& x : d) cin >> x;
    auto ans = solve(n, a, b, d);
    if (ans.empty()) {
        cout << "No" << endl;
        exit(0);
    }
    cout << "Yes" << endl;
    cout << ans << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 4);
        vector<int> d(n);
        for (auto& x : d) x = rnd(1, 5);
        int x = rnd(-10, 10), y = rnd(-10, 10);
        bool ans = brute(x, y, d);
            cout << n << " " << x << " " << y << endl;
            for (auto z : d) cout << z << " ";
            cout << endl;
        auto my = solve(n, x, y, d);
        if (ans == true) {
            if (my.empty()) {
                cout << "Wrong answer on test " << t << endl;
                cout << n << " " << x << " " << y << endl;
                for (auto z : d) cout << z << " ";
                cout << endl;
                cout << "Solve: " << my << endl;
                cout << "Brute: " << ans << endl;
                exit(0);
            }
            int a = 0, b = 0;
            auto s = my;
            for (int i = 0; i < n; ++i) {
                if (s[i] == 'L') a -= d[i];
                if (s[i] == 'R') a += d[i];
                if (s[i] == 'D') b -= d[i];
                if (s[i] == 'U') b += d[i];
            }
            if (a != x or b != y) {
                cout << "Wrong answer on test " << t << endl;
                cout << n << " " << x << " " << y << endl;
                for (auto z : d) cout << z << " ";
                cout << endl;
                cout << "Solve: " << my << endl;
                cout << "Brute: " << ans << endl;
                exit(0);
            }
            cout << "Accepted on test " << t++ << endl;
            continue;
        }
        if (!my.empty()) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << x << " " << y << endl;
            for (auto z : d) cout << z << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
