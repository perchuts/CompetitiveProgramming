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
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;
    auto dist = [&] (string s, string t) {
        vector<int> pos(2*n), qt(2*n);
        int tt = 0, qt1 = 0;
        for (int i = 0; i < 2*n; ++i) {
            if (s[i] == '0') qt[tt] = qt1, pos[tt++] = i+1;
            else qt1++;
        }
        int ans = 0;
        tt = 0, qt1 = 0;
        for (int i = 0; i < 2*n; ++i) {
            if (t[i] == '0') {
                ans += abs(qt[tt] - qt1);
                tt++;
            } else qt1++;
        }
        return ans;
    };
    int p1 = 0, p2 = 0, p3 = 0;
    string ans(2*n, '0');
    for (int i = 0; i < n; ++i) {
        while (a[p1] == '0') p1++;
        while (b[p2] == '0') p2++;
        while (c[p3] == '0') p3++;
        vector<int> sexo = {p1, p2, p3}; sort(all(sexo));
        ans[sexo[1]] = '1';
        p1++, p2++, p3++;
    }
    int resp = dist(ans, a) + dist(ans, b) + dist(ans, c);
    cout << resp << endl << ans << endl;
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
