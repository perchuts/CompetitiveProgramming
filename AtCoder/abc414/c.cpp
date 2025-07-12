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
    int a, n; cin >> a >> n;
    int ans = 0;
    auto check = [&] (int k) {
        if (k > n) return false;
        vector<int> cara;
        while (k) cara.pb(k % a), k /= a;
        auto caraa = cara;
        reverse(all(caraa));
        return caraa == cara;
    };
    for (int i = 1; i < 1e6; ++i) {
        string sexo = to_string(i);
        if (i < 10) ans += check(i) * i;
        string rev = sexo; reverse(all(rev));
        string tt = sexo + rev;
        ans += check(stoll(tt)) * stoll(tt);
        string s2 = sexo + to_string(0) + rev;
        for (int j = 0; j < 10; ++j) {
            s2[sz(sexo)] = char('0' + j);
            int k = stoll(s2);
            ans += check(k) * k;
        }
    }
    cout << ans << endl;
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
