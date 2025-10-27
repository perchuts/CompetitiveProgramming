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
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int ptr[maxn][2], dep[maxn];

void solve() {
    // Seja n o menor tamanho de uma string que nao viole a propriedade. (n <= L)
    int n, l; cin >> n >> l;
    int cur = 0;
    dep[0] = l;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int x = 0;
        for (auto c : s) {
            int choice = (c - '0');
            if (ptr[x][choice] == 0) ptr[x][choice] = ++cur, dep[cur] = dep[x] - 1;
            x = ptr[x][choice];
        }
    }
    int xx = 0;
    for (int i = 0; i < cur; ++i) {
        if (dep[i] == 0) continue;
        int tot = 0;
        if (!ptr[i][0]) tot++;
        if (!ptr[i][1]) tot++;
        if (tot & 1) {
            int h = 0, z = dep[i]-1;
            while (z >> h & 1) h++;
            xx ^= (1LL << h);
        }
    }
    cout << (xx ? "Alice" : "Bob") << endl;
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
