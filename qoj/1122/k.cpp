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
    auto type = [] (char c) {
        return (c == '(' or c == ')');
    };
    vector<vector<vector<int>>> grafos;
    auto parse = [type] (string s) {
        int n = sz(s);
        vector<int> match(n);
        stack<int> st;
       for (int i = 0; i < n; ++i) {
            if (s[i] == '(') st.push(i);
            else if (s[i] == ')') {
                int j = st.top(); st.pop();
                match[i] = j, match[j] = i;
            }
        }
        const int lim = 1000005;
        vector<int> pai(lim, -1);
        auto go = [&] (auto&& self, int l, int r) -> int {
            // ler o que esta dentro daqui
            int num = 0, ptr = l;
            while (ptr <= r and !type(s[ptr])) num = 10 * num + (s[ptr++] - '0');
            while (ptr < r) {
                assert(type(s[ptr]));
                int fim = match[ptr]; 
                int w = self(self, ptr+1, fim-1);
                pai[w] = num;
                ptr = fim+1;
            }
            return num;
        };
        int raiz = go(go, 0, n-1);
        pai[raiz] = raiz;
        return pai;
    };
    auto clear_spaces = [] (string s) {
        string t;
        for (auto c : s) if (c != ' ') t += c;
        return t;
    };
    string s, t;  getline(cin, s); getline(cin, t); s = clear_spaces(s), t = clear_spaces(t);
    auto z1 = parse(s);
    auto z2 = parse(t);
    cout << (z1 == z2 ? "Yes" : "No") << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
