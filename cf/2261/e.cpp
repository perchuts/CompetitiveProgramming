#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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
std::string balanced_bracket_sequence_v1(int n) {
    auto res = std::string(n, '(') + std::string(n + 1, ')');
    shuffle(res.begin(), res.end(), rng);
    std::vector<int> pref(2 * n + 2, 0);
    for (int x = 0; x < 2 * n + 1; x++)
        pref[x + 1] = pref[x] + (res[x] == '(' ? 1 : -1);
    int idx =
        int(std::min_element(pref.begin(), pref.end()) - pref.begin());
    std::rotate(res.begin(), res.begin() + idx, res.end());
    return res.substr(0, 2 * n);
}
int solve(int n, int k, string s) {
    int ans = 0, cur = 0, uses = 0;
    stack<int> st;
    vector<int> link(n), right(n, n/2), qtd(n);
    for (int i = 0; i < n; ++i) {
        if (i) right[i] = right[i-1];
        if (s[i] == '(') st.push(i), right[i]--;
        else {
            int j = st.top(); st.pop();
            link[i] = j, link[j] = i;
        }
    }
    for (int i = n-2; ~i; --i) {
        if (s[i+1] == ')') qtd[i] = 0;
        else qtd[i] = 1 + qtd[i+1];
    }
    for (int i = 0; i < n; ++i) {
        ckmax(ans, cur + min(k-uses, right[i]));
        if (s[i] == '(') {
            cur++;
        } else {
            if (uses == k) break;
            uses++;
        }
    }

    k *= 2;

    deque<ii> rg;

    int ptr = 0, checkpoint = 0;

    uses = 0;

    for (int start = 0; start < n; ++start) {
        if (!rg.empty() and rg.front().first <= start) {
            uses -= rg.front().second - rg.front().first + 1;
            start = rg.front().second;
            rg.pop_front();
        }
        if (s[start] == ')') continue;
        ckmax(ptr, start);
        ckmax(checkpoint, start);
        ckmax(ans, qtd[start]+1);
        int i = start;
        while (ptr < n) {
            while (s[ptr] == '(') ptr++;
            int j = link[ptr];
            if (j <= start) { start = ptr; uses = 0; rg.clear(); break; }
                //cout << "start = " << i << " checkpoint = " << checkpoint << " ptr = " << ptr << " uses = " << uses << endl;
            while (!rg.empty() and rg.back().second >= link[ptr]) uses -= rg.back().second - rg.back().first + 1, rg.pop_back();
            if (uses + ptr - link[ptr] + 1 <= k) {
                //cout << "nice" << endl;
                rg.pb({link[ptr], ptr});
                uses += ptr - link[ptr] + 1;
                checkpoint = ptr++;
                ckmax(ans, checkpoint - i + 1 - uses + qtd[checkpoint]);
            } else {
                break;
            }
        }
    }
    return ans;
}

int T;
int brute(int n, int k, string s) {
    int ans = 0, cur = 0, uses = 0;
    stack<int> st;
    vector<int> link(n), right(n, n/2), qtd(n);
    for (int i = 0; i < n; ++i) {
        if (i) right[i] = right[i-1];
        if (s[i] == '(') st.push(i), right[i]--;
        else {
            int j = st.top(); st.pop();
            link[i] = j, link[j] = i;
        }
    }
    for (int i = n-2; ~i; --i) {
        if (s[i+1] == ')') qtd[i] = 0;
        else qtd[i] = 1 + qtd[i+1];
    }
    for (int i = 0; i < n; ++i) {
        ckmax(ans, cur + min(k-uses, right[i]));
        if (s[i] == '(') {
            cur++;
        } else {
            if (uses == k) break;
            uses++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == ')') continue;
        for (int j = i; j < n; ++j) {
            int ptr = j, cur = 0, cost = 0;
            while (ptr >= i) {
                if (s[ptr] == '(') ptr--, cur++;
                else if (link[ptr] <= i) { cur = 0; break; }
                else cost += ptr - link[ptr]+1, ptr = link[ptr]-1;
            }
            if (T == 10451 and cur == 6 and ans != 6 and cost <= 2*k) {
                //cout << i << " " << j << endl;
            }
            if (cost <= 2*k) ckmax(ans, cur);
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << solve(n, k, s) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), k = rnd(1, n);
        string s = balanced_bracket_sequence_v1(n);
        n *= 2;
        T = t;
        int my = solve(n, k, s), ans = brute(n, k, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << endl;
            cout << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
