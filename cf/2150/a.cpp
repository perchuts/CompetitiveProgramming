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
    int n, m; cin >> n >> m;
    string s; cin >> s;
    // tudo igual de menos o proximo comando
    set<int> ans;
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        ans.insert(x);
    }
    int pos = 1, lst = 0;
    for (int i = 0; i < n; ++i) {
        // se o ultimo comando foi um G, entao preciso andar mais ainda pra frente!!
        if (lst) {
            while (ans.find(pos) != end(ans)) pos++;
        }
        if (s[i] == 'A') pos++, lst = 0;
        else {
            lst = 1;
            pos++;
            while (ans.find(pos) != end(ans)) pos++;
        }
        ans.insert(pos);
    }
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
