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
    int n, m; cin >> n >> m;
    vector<int> freq(201);
    vector<int> v(n);
    for (auto& x : v) cin >> x, freq[x]++;
    // tenta par
    int qt_antes = 0, qt_depois = 0;
    for (int i = 1; i < m; ++i) qt_antes += freq[i];
    for (int i = m + 1; i <= 200; ++i) qt_depois += freq[i];
    int ans = qt_antes + qt_depois;
    for (int i = n-qt_antes-qt_depois+1; i <= n; ++i) {
        // quero ver se da pra deixar sobrando essa quantidade de bicho ai
        int need = (i-1)/2;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
