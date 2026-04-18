#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
const int maxn = 2e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int nxt[maxn][10];

string solve(string s) {
    int n = sz(s);
    for (int i = 0; i <= n; ++i) for (int j = 0; j < 10; ++j) nxt[i][j] = n;
    vector<int> max_len(n+1, 1);
    for (int i = n-1; ~i; --i) {
        for (int j = 0; j < 10; ++j) nxt[i][j] = nxt[i+1][j];
        nxt[i][s[i]-'0'] = i;
        max_len[i] = n;
        for (int d = 0; d < 10; ++d) {
            int j = nxt[i][d];
            if (j == n) {
                max_len[i] = 1;
                break;
            }
            ckmin(max_len[i], 1 + max_len[j+1]);
        }
    }
    if (nxt[0][0] == n) return "0";
    int i = 0;
    string ans;
    while (i < n) {
        char choice;
        int opt = n+5;
        int ni;
		bool nice = 0;
        for (int d = (i == 0); d < 10; ++d) { 
            int j = nxt[i][d];
            if (j == n) {
                choice = char('0'+d);
				nice = 1;
                ni = n;
                break;
            }
            if (1 + max_len[j+1] < opt) {
                opt = 1 + max_len[j+1];
                choice = char('0'+d);
                ni = j+1;
            }
        }
        ans += choice;
        i = ni;
		if (i == n and !nice) ans += '0';
    }
    return ans;
}

string brute(string s) {
    int n = sz(s);
    map<int, int> mark;
    for (int i = 1; i < (1 << n); ++i) {
        string t;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                if (sz(t) == 1 and t[0] == '0') continue;
                t += s[j];
            }
        }
        int k = stoll(t);
        mark[k] = 1;
    }
    for (int i = 0; ; ++i) {
        if (!mark[i]) {
            return to_string(i);
        }
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        string s; cin >> s;
        cout << solve(s) << endl;
    }
#else
    int t = 1;
    while (true) {
        string s;
        int n = rnd(1, 15);
        for (int i = 0; i < n; ++i) {
            s += char('0' + rnd(i==0, 9));
        }
        string my = solve(s);
        string ans = brute(s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
