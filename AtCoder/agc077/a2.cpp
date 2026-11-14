#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

vector<ii> solve(string s, string t) {
    if (s == t) return {};
    int n = sz(s);
    {
        auto s2 = s; auto t2 = t;
        sort(all(s2)), sort(all(t2));
        if (s2 != t2) return {{-1, -1}};
    }
    if (s > t) return {{-1, -1}};
    reverse(all(s)), reverse(all(t));
    if (s < t) return {{-1, -1}};
    reverse(all(s)), reverse(all(t));
    vector<ii> ans;
    int i = 0, j = n-1;
    while (s != t) {
        while (s[i] == t[i]) i++;
        while (s[j] == t[j]) j--;
        cout << "i = " << i << " j = " << j << endl;
        cout << s << endl << t << endl;
        cout << flush;
        int t1 = 1, t2 = 1;
        while (i + t1 < j and t[i + t1] == 'A') t1++;
        while (j - t2 > i and t[j - t2] == 'B') t2++;
        if (i + t1 == j or j - t2 == i) {
            reverse(begin(s)+i, begin(s)+j+1);
            ans.pb({i, j});
            break;
        }
        cout << "t1 = " << t1 << " t2 = " << t2 << endl;
        int p1 = 0, p2 = 0;
        while (true) {
            while (s[i + p2 + 1] == 'B') p2++;
            while (s[j - p1 - 1] == 'A') p1++;
            if (p1 >= t1 and p2 >= t2) break;
            if (i + p2 + 1 == j - p1) break;
            ans.push_back({i + p2 + 1, j - p1 - 1});
            reverse(begin(s) + i + p2 + 1, begin(s) + j - p1);
            cout << "p1 = " << p1 << " p2 = " << p2 << endl;
            cout << s << endl;
            cout << flush;
			//if (p2 != 0) exit(0);
        }
        ans.push_back({i, j});
        reverse(begin(s)+i, begin(s)+j+1);
    }
    return ans;
}

bool brute(string s, string t) {
    map<string, int> ss;
    int n = t.size();
    queue<string> q;
    ss[s] = 0;
    q.push(s);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int eu = ss[cur];
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (cur[i] == 'A' and cur[j] == 'B') {
                    reverse(begin(cur)+i, begin(cur)+j+1);
                    if (ss.count(cur) == false) {
                        q.push(cur);
                        ss[cur] = 1 + eu;
                    }
                    reverse(begin(cur)+i, begin(cur)+j+1);
                }
            }
        }
    }
    return ss.count(t);
}

vector<ii> cubic(string s, string t) {
    int n = s.size();
    string ss = s, tt = t; sort(all(ss)), sort(all(tt));
    if (ss != tt) return vector<ii>(1, {-1, -1});
    vector<pair<int, int>> ops;
    for (int i = 0; i < n; ++i) {
        if (s[i] == t[i]) continue;
        if (s[i] == 'B') return vector<ii>(1, {-1, -1});
        bool foi = 0;
        for (int j = i + 1; j < n; ++j) {
            if (s[j] == 'B') {
                reverse(begin(s)+i, begin(s)+j+1);
                bool nice = 1;
                for (int k = i + 1; k < j; ++k) {
                    if (s[k] != t[k]) {
                        nice = (s[k] == 'A');
                        break;
                    }
                }
                if (nice) {
                    foi = 1;
                    ops.pb({i, j});
                    break;
                }
                reverse(begin(s)+i, begin(s)+j+1);
            }
        }
        if (!foi) return vector<ii>(1, {-1, -1});
    }
    return ops;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        string a, b; cin >> a >> b;
        auto ans = solve(a, b);
        if (sz(ans) == 1 and ans[0].first == -1) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        cout << sz(ans) << endl;
        for (auto [x, y] : ans) cout << x+1 << " " << y+1 << endl;
    }
#else
    int T = 1;
    while (true) {
        int n = rnd(2, 12);
        string s(n, 'A');
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        for (auto& x : s) if (rnd(0, 1)) x = 'B';
        string t = s;
        for (int i = 0; i < n; ++i) t[i] = s[p[i]];
        bool possible = brute(s, t);
        cout << n << endl << s << endl << t << endl;
        cout << flush;
        auto ans = solve(s, t);
        if (possible) {
            if ((!ans.empty() and ans[0].first == -1)) {
                cout << "Wrong answer on test " << T << endl;
                cout << "False negative!" << endl;
                cout << n << endl;
                cout << s << endl << t << endl;
                exit(0);
            }
            if (2 * sz(ans) > n) {
                cout << "Wrong answer on test " << T << endl;
                cout << "Big answer!" << endl;
                cout << s << endl << t << endl;
                cout << n << endl;
                cout << "Answer: " << endl;
                for (auto [x, y] : ans) cout << x + 1 << " " << y + 1 << endl;
                exit(0);
            }
            auto ss = s;
            bool ok = 1;
            for (auto [x, y] : ans) {
                ok &= (ss[x] == 'A' and ss[y] == 'B');
                reverse(begin(ss)+x, begin(ss)+y+1);
            }
            if (!ok) {
                cout << "Wrong answer on test " << T << endl;
                cout << "Swapped other thing" << endl;
                cout << n << endl;
                cout << s << endl << t << endl;
                exit(0);
            }
            if (ss != t) {
                cout << "Wrong answer on test " << T << endl;
                cout << "Wrong construction" << endl;
                cout << n << endl;
                cout << s << endl << t << endl;
                exit(0);
            }
        } else {
            if (sz(ans) != 1 or ans[0].first != -1) {
                cout << "Wrong answer on test " << T << endl;
                cout << "false positive!" << endl;
                cout << n << endl;
                cout << s << endl << t << endl;
                exit(0);
            }
        }
        cout << "Accepted on test " << T++ << endl;
    }
#endif
}
