#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

int solve(string s, string t) {
    int n = s.size();
    if (s == t) return 0;

    s = " " + s;
    t = " " + t;

    queue<int> q;
    int ans = 0;
    int pos = n;

    for (int i = n; i >= 1; --i) {
        if (i > 1 && t[i - 1] == t[i]) continue; // only run starts

        pos = min(pos, i);
        while (pos >= 1 && s[pos] != t[i]) --pos;
        if (pos == 0) return -1;

        while (!q.empty() && q.front() - (int)q.size() + 1 > i)
            q.pop();

        if (pos != i) q.push(pos);

        ans = max(ans, (int)q.size());
        --pos;
    }

    return ans + 1;
}

int brute(int n, string s, string t) {

    vector<vector<int>> prox(n, vector<int>(26, n));


    prox[n-1][s[n-1]-'a'] = n-1;
    for (int i = n-2; i >= 0; --i) prox[i] = prox[i+1], prox[i][s[i]-'a'] = i;

    vector<int> dp(n+1, n);

    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) continue;
        int ult = (i == 0 ? 0 : dp[i-1]);
        ckmin(dp[i], ult);
        int j = i + 1, ptr = i, cost = 1;
        while (j < n) {
            ptr = prox[ptr][t[j]-'a'];
            if (ptr > j) break;
            cost += (t[j] != t[j-1]);
            ckmin(dp[j], max(ult, cost));
            j++;
        }
		//cout << "i = " << i << ", j = " << j << endl;
    }
	//for (auto x : dp) cout << x << " ";
	//cout << endl;

    return (dp[n-1] == n ? -1 : dp[n-1]);
}

int32_t main() {_
#ifndef gato
    int n; string s, t; cin >> n >> s >> t;
    cout << solve(s, t) << endl;
#else
    int T = 1;
	using ld = long double;
    string penis = "ab";
    while (true) {
        int n = rnd(2, 6);
        string s(n, 'a'), t(n, 'a');
        int lim = 1;
        s[0] = t[0] = penis[rnd(0, sz(penis)-1)];
        for (int i = 1; i < n; ++i) {
            s[i] = penis[rnd(0, sz(penis)-1)];
            t[i] = penis[rnd(0, sz(penis)-1)];
        }
        int my = solve(s, t), ans = brute(n, s, t);
		//cout << "n = " << n << ", nodes visited = " << my << endl;
        if (my != ans) {
            cout << "Wrong answer on test " << T << endl;
            cout << n << endl << s << endl << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << T++ << endl;
    }
#endif
}
