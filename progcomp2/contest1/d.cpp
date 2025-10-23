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

const int inf = 1e9+115;
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
    int a, b, x1, y1, x2, y2; cin >> a >> b >> x1 >> y1 >> x2 >> y2;
    auto get = [&] (int x, int y) {
        return pair(x+y, x-y);
    };
    auto [a1, b1] = get(x1, y1);
    auto [a2, b2] = get(x2, y2);
    auto conta = [&] (int l, int r, int M) {
        if (l > r) swap(l, r);
        int ans = 0;
        l += inf * M, r += inf * M; 
        ans = (r / M) - (l / M);
        if (l % M == 0) ans++;
        return ans;
    };
    cout << max(conta(a1, a2, 2*a), conta(b1, b2, 2*b)) << endl;
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
