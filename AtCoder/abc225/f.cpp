#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

string solve(int n, int k, vector<string> s){
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
		if (s[x] + s[y] == s[y] + s[x]) return s[x] < s[y];
        return s[x] + s[y] < s[y] + s[x];
    });
	vector<vector<string>> dp(k+1, vector<string>(k*50+1));
	string ans;
	for (int i = 0; i < n; ++i) {
		string cur = s[ord[i]];
		for (int j = min(k, i+1); j >= 1; --j) {
			for (int w = sz(cur); w <= j * 50; ++w) {
				if (dp[j-1][w-sz(cur)].empty()) continue;
				string t = dp[j-1][w-sz(cur)] + cur;
				if (dp[j][w].empty() or t < dp[j][w]) dp[j][w] = t;
			}
		}
		if (dp[1][sz(cur)].empty() or cur < dp[1][sz(cur)]) dp[1][sz(cur)] = cur;
	}
	for (int j = 1; j <= k * 50; ++j) {
		if (ans.empty() or (!dp[k][j].empty() and dp[k][j] < ans)) ans = dp[k][j];
	}
    return ans;
}

string brute(int n, int k, vector<string> s) {
    vector<int> p(n); iota(all(p), 0);
    string ans;
    do {
        string cur;
        for (int i = 0; i < k; ++i) cur += s[p[i]];
        if (ans.empty() or cur < ans) ans = cur;
    } while (next_permutation(all(p)));
    return ans;
}

int32_t main(){_
#ifndef gato
    int n, k; cin >> n >> k;
    vector<string> s(n);
    for (auto& x : s) cin >> x;
    cout << solve(n, k, s) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 8), k = rnd(1, n);
        vector<string> s(n);
        for (auto& x : s) {
            while (true) {
                char c = rnd('a', 'e');
                if ((c == 'd' and !x.empty()) or sz(x) > 8) break;
                x += c;
            }
        }
        auto my = solve(n, k, s);
        auto ans = brute(n, k, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            for (auto x : s) cout << x << endl;
            cout << "Your output: " << my << endl;
            cout << "Correct answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
