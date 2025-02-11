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
    vector<int> a(n), b(n), c(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], sum += a[i], c[i] = b[i] - a[i];
    sort(all(c));
    vector<ii> d;
    for (int i = 0, j = 0; i < n; i = j) {
        d.emplace_back(c[i], 0);
        while (j != n and c[j] == c[i]) d.back().second++, j++;
    }
    int shift = m+1;
    vector<int> dp(2*m+3, n+1);
    dp[shift] = 0;
    auto work = [&] (int qnt) {
        vector<int> bits;
        int soma = 0;
        while (soma+1 <= qnt) bits.pb(soma+1), qnt -= soma+1, soma += soma+1;
        if (qnt != 0) bits.pb(qnt); 
        return bits;
    };
    for (auto [val, qnt] : d) {
        vector<int> bits = work(qnt);
        for (auto usar : bits) {
            vector<int> ndp = dp;
            for (int i = min(m, m+usar*val); i >= max(-m, -m+usar*val); --i) ckmin(ndp[i+shift], dp[i+shift-usar*val] + usar);
            swap(dp, ndp);
        }
    }
    for (int i = 0; i <= m; ++i) {
        int falta = i - sum;
        cout << (dp[falta+shift] > n ? -1 : dp[falta+shift]) << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
