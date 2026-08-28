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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(string s, string t) {
    if (s == t) return 0;
    int n = sz(s);
    swap(s, t);
    vector<int> rx = {0};
    for (int i = 1; i < n; ++i) if (s[i] != s[i-1]) rx.pb(i);
    auto possible = [&] (int x) {
        deque<array<int, 3>> pts;
        int pos = 0;
        for (int i = 0; i < sz(rx); ++i) {
            while (pos <= rx[i] and s[rx[i]] != t[pos]) pos++;
            if (pos > rx[i]) return false;
            while (!pts.empty() and pts.front()[1] + i-pts.front()[2]+1 <= pos) pts.pop_front();
            if (!pts.empty()) pts.front()[0] = pos+1;
            if (i != sz(rx)-1 and rx[i+1] != rx[i]+1) pts.push_back({rx[i]+(i!=0), rx[i+1]-1, i});
            while (!pts.empty() and i-pts.front()[2]+1 == x) pos = pts.front()[1]+x, pts.pop_front();
        }
        return true;
    };
    int l = 1, r = sz(rx), ans = -1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    return ans;
}

// wrong brute lol
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
    string penis = "abcde";
    while (true) {
        int n = rnd(2, 10);
        string s(n, 'a'), t(n, 'a');
        int lim = 1;
        s[0] = t[0] = penis[rnd(0, sz(penis)-1)];
        for (int i = 1; i < n; ++i) {
            s[i] = penis[rnd(0, sz(penis)-1)];
            t[i] = penis[rnd(0, sz(penis)-1)];
        }
        int my = solve(s, t), ans = brute(n, s, t);
		//cout << "n = " << n << ", nodes visited = " << my << endl;
        if (my > ans) {
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
