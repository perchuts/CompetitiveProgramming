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
    // numero de bits em cada fileira tem que ser par
    // ent eh basicamente soh isso
    // x+2 choose 3?
    int n; 
    vector<int> a;
    cin >> n;
    for (auto& x : a) cin >> x;
    int ans = (n+2) * (n+1) * n / 6;
    map<int, int> sexo;
    sexo[0] = 1;
    int x = 0;
    for (int i = 0; i < n; ++i) {
        x ^= a[i];
        sexo[x]++;
    }
    for (auto [x, y] : sexo) {
        ans -= y * (y+1) * (y-1) / 6;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
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
