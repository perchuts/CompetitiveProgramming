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
    auto convert = [&] (string s) {
        vector<int> cnt(10);
        for (auto c : s) cnt[c-'0']++;
        string t;
        for (int i = 0; i < 10; ++i) {
            if (cnt[i] != 0) {
                t += to_string(cnt[i]);
                t += to_string(i);
            }
        }
        return t;
    };
    string s, t; cin >> s >> t;
    vector<string> sexo = {""};
    sexo.pb(s);
    for (int i = 1; i <= 100; ++i) sexo.pb(convert(sexo.back()));
    set<string> strs;
    for (auto x : sexo) strs.insert(x);
    if (sz(strs) == sz(sexo)) {
        cout << "I'm bored" << endl;
        return;
    }
    for (int i = 1; i <= 100; ++i) {
        if (sexo[i] == t) {
            cout << i << endl;
            return;
        }
    }
    cout << "Does not appear" << endl;
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
