#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define gato
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
typedef long long ll;

void chmin(int& a, int b) { a = min(a, b); }

vector<int> kmp(string s) {
	vector<int> p(s.size());
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j and s[j] != s[i]) j = p[j-1];
		if (s[j] == s[i]) j++;
		p[i] = j;
	}
	return p;
}

int solve(int n, int m, string s, string t) {

	const int INF = 1e9;
	vector dp(n + 1, vector(m + 1, INF));
	for (int i = n - 1; i >= 0; --i) {
		for (int j = m - 1; j >= 0; --j) {
			string st = s.substr(i) + "#" + t.substr(j);
			auto v = kmp(st);

			int pos = n-i+1, ini = pos;
			chmin(dp[i][j], dp[i+1][j]);
			for (int k = i + 1; k <= n; k++) {
				while (pos < v.size() && v[pos] < k-i) pos++;
				int to = j+pos-ini + 1;
				if (to < m + 1) {
					if (k == n) {
						if (v.back() < k-i) chmin(dp[i][j], k-i);
					} else {
						if (to == m) chmin(dp[i][j], (k-i) + (k==n-1?1:2));
						else chmin(dp[i][j], dp[k][to] + (k-i) + 1);
					}
				} else {
					chmin(dp[i][j], (k-i) + (k!=n));
				}
			}

			//	if (to - j == k - i && to != m + 1) {
			//		if (k == n) {
			//			if (to != m) dp[i][j][0] = min(dp[i][j][0], (k-i));
			//		} else {
			//			if (to == m) dp[i][j][0] = min(dp[i][j][0], (k-i) + (k==n-1?1:2));
			//			else dp[i][j][0] = min(dp[i][j][0], dp[k][to][0] + (k-i));
			//		}
			//	} else {
			//		dp[i][j][0] = min(dp[i][j][0], (k-i) + (k!=n));
			//	}
			//}
			//dp[i][j][0] = min(dp[i][j][0], dp[i][j][1] + 1);
		}
	}

	int ans = min(dp[0][0] + 1, n);
	int i = 0, j = 0;
	string st = s.substr(i) + "#" + t.substr(j);
	auto v = kmp(st);
	int pos = n-i+1, ini = pos;
	for (int k = 1; k < n; k++) {
		while (pos < v.size() && v[pos] < k-i) pos++;
		int to = j+pos-ini + 1;

		if (to - j == k - i && to != m + 1) {
			if (k == n) {
				if (to != m) chmin(ans, (k-i));
			} else {
				if (to == m) chmin(ans, (k-i) + (k==n-1?1:2));
				else chmin(ans, dp[k][to] + (k-i) + 1);
			}
		} else {
			chmin(ans, (k-i) + (k!=n));
		}
	}

    return ans;
}

int brute(int n, int m, string s, string t) {
    int ans = n;
    auto go = [&] (auto&& self, string cur) -> void {
        if (cur.size() >= ans) return;
        auto solvar = [] (string cur, string t) {
            int m = t.size(), k = cur.size();
            vector<vector<int>> dp(m+1, vector<int>(k+1));
            dp[0][0] = 1;
            if (k and cur[0] == '*') {
                for (int i = 0; i <= m; ++i) dp[i][1] = 1;
            }
            for (int i = 1; i <= m; ++i) for (int j = 1; j <= k; ++j) {
                if (cur[j-1] == '*') dp[i][j] |= dp[i-1][j], dp[i][j] |= dp[i][j-1], dp[i][j] |= dp[i-1][j-1];
                else dp[i][j] = (dp[i-1][j-1] && (cur[j-1] == t[i-1]));
            }
            return dp[m][k];
        };
        if (solvar(cur, s) and !solvar(cur, t)) {
            ans = min(ans, (int)cur.size());
            return;
        }
        for (int i = 0; i < 3; ++i) {
            cur += char('a'+i);
            self(self, cur);
            cur.pop_back();
        }
        cur += '*';
        self(self, cur);
    };
    go(go, "");
    return ans;
}
int32_t main() {
    fast_io;
#ifndef gato
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    cout << solve(n, m, s, t) << endl;
#else
    int test = 1;
    while (true) {
        srand(test);
        int n = rand() % 5 + 1, m = rand() % 5 + 1;
        string s, t;
        for (int i = 0; i < n; ++i) s += char('a' + rand()%3);
        for (int i = 0; i < m; ++i) t += char('a' + rand()%3);
        if (s == t) { test++; continue; }
        int my = solve(n, m, s, t);
        int ans = brute(n, m, s, t);
        if (my != ans) {
            cout << "Wrong answer on test " << test << endl;
            cout << n << ' ' << m << endl;
            cout << s << endl << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << test++ << endl;
    }
#endif
}

