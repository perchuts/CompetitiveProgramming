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

void solve() {
    string s; cin >> s;
    int n = sz(s);
    vector<int> match(n, -1);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') st.push(i);
        else if (s[i] == ')') match[i] = st.top(), match[st.top()] = i, st.pop();
    } 
    auto go = [&] (auto&& self, int l, int r, int type = 0) -> void {
        if (l > r) return;
        if (type == 0) {
            if (match[l] == -1) {
                cout << s[l];
                self(self, l+1, r, 0);
            } else {
                self(self, l+1, match[l]-1, 1);
                self(self, match[l]+1, r, 0);
            }
        } else {
            if (match[r] == -1) {
                if ('a' <= s[r] and s[r] <= 'z') cout << char(s[r] + ('A' - 'a'));
                else cout << char(s[r] + ('a' - 'A'));
                self(self, l, r-1, 1);
            } else {
                self(self, match[r]+1, r-1, 0);
                self(self, l, match[r]-1, 1);
            }
        }
    };
    go(go, 0, n-1);
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
