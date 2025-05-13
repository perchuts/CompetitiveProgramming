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

void solve(){
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    vector<int> big(n+1);
    for (int i = 0; i < n; ++i) {
        if (p[i] == -1) continue;
        int tam = 0, cur = i;
        while (p[cur] != -1) {
            int prox = p[cur];
            p[cur] = -1;
            cur = prox;
            tam++; 
        }
        cur = tam;
        map<int, int> factors;
        for (int j = 2; j * j <= tam; ++j) {
            while (cur % j == 0) factors[j]++, cur /= j;
        }
        if (cur != 1) factors[cur]++;
        for (auto [x, y] : factors) ckmax(big[x], y);
    }
    int ans = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < big[i]; ++j) ans = ans * i % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
