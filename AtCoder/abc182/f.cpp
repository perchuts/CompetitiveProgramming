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
    int n, X; cin >> n >> X;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // comprei algo que custa X ienes
    // vou entregar Y ienes pro bicho.
    // n vou receber de troco nenhuma das moedas que eu entreguei pro bicho
    // tudo eh usado de forma a minimizar a quantidade de moedas necessarias.
    // como a[i] | a[j] pra todo i <= j, ent o guloso certamente serve pra representar uma moeda.
    // entao f(K) = maneira gulosa de escrever K como combinacao linear dos v[i]
    // quero a quantidade de Y tal que f(Y-X) eh disjunto de f(X)
    vector<int> digits(n);
    int cur = X, msb = 0;
    for (int i = n-1; ~i; --i) digits[i] = cur / v[i], cur %= v[i];
    for (int i = 0; i < n; ++i) if (digits[i]) msb = i+1;
    int ans = 0;
    vector<vector<int>> dp(n+1, vector<int>(2));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        // posso ser um a mais do que o cara, ser zero, ou me matar com o cara
        int lim = (i == n ? 1e18 : v[i]/v[i-1]-1);
        // um estado q eh 1 so pode ser anulado por um estado 1 a mais
        if (digits[i-1] == 0) {
            // colocar zero e n tava precisando + colocar 1 e tava precisando
            dp[i][0] = dp[i-1][0]+dp[i-1][1];
            // colocar zero e tava precisando
            dp[i][1] = dp[i-1][1];
        } else {
            // igual
            dp[i][0] = dp[i-1][0];
            // zero
            dp[i][1] += dp[i-1][0] + dp[i-1][1];
            // um a mais
            if (digits[i-1] != lim) 
                dp[i][0] += dp[i-1][1];
        }
        if (i == msb) ans += dp[i][0];
        else if (i > msb) ans += dp[i][1];
        // colocar zero
        // colocar igual
        // colocar +1
        // cout << dp[i][0] << ' ' << dp[i][1] << endl;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
