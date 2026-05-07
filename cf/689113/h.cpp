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
    vector<vector<int>> a(3);
    vector<int> onde(n+1);
    for (int i = 0; i < 3; ++i) {
        int k; cin >> k;
        a[i].resize(k);
        for (auto& x : a[i]) cin >> x, onde[x] = i;
    }
    vector<pair<char, char>> ans;
    auto solve = [&] (auto&& self, int n, int target) -> void {
        // identifique onde esta o bicho. mova o bicho pro lugar que voce precisa.
        if (n == 0) return;
        //cout << "preciso mover piramide com " << n << " blocos pra pilha " << char('A'+target) << endl;
        if (onde[n] == target) return void(self(self, n-1, target));
        self(self, n-1, 3-onde[n]-target); 
        //cout << "movendo bloco " << n << " da pilha " << char('A'+onde[n]) << " para a pilha " << char('A'+target) << endl;
        ans.pb({char('A'+onde[n]), char('A'+target)});
        onde[n] = target;
        self(self, n-1, target);
    };
    solve(solve, n, 1);
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x << " " << y << endl;
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
