#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    auto convert = [&] (string t) {
        // t is an integer
        for (auto c : t) assert('0' <= c and c <= '9');
        if (sz(t) <= 4) return t;
        int n = sz(t);
        int fim = n-1;
        while (t[fim] == '0') fim--;
        if (fim >= n-4) return t;
        if (fim == 0 and t[0] == '1') {
            string dec = "10^{";
            dec += to_string(n-1);
            dec += "}";
            return dec;
        }
        string dec; dec += t[0]; 
        if (fim != 0) dec += ".";
        for (int i = 1; i <= fim; ++i) dec += t[i];
        dec += "\\cdot10^{";
        dec += to_string(n-1);
        dec += "}";
        return dec;
    };
    string s; getline(cin, s);
    string result;
    int inside_braces = 0;
    int tam = sz(s);
    for (int i = 0; i < tam; ++i) {
        if (s[i] == '{') {
            if (i != 0 and (s[i-1] == '_' or s[i-1] == '^')) inside_braces = 1;
            result += s[i];
        } else if (s[i] == '}') {
            inside_braces = 0;
            result += s[i];
        } else if ('0' <= s[i] and s[i] <= '9') {
            // comecei um numero!!
            int efeito = (inside_braces == 0 and (i == 0 or (s[i-1] == '{' or s[i-1] == '}' or s[i-1] == ' ')));
            string t;
            while (i < tam and '0' <= s[i] and s[i] <= '9') t += s[i++];
            efeito &= (i == tam or (s[i] == ' ' or s[i] == '{' or s[i] == '}'));
            if (efeito) t = convert(t);
            result += t;
            i--;
        } else result += s[i];
    }
    cout << result << endl;
}

int32_t main() {_
#ifndef gato
    int n; string penis; getline(cin, penis);
    n = stoi(penis);
    while (n--) solve();
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
