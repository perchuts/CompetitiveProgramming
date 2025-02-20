#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n, l, r; cin >> n >> l >> r;
    vector<int> dp(n+1);
    vector<vector<ii>> tr(n+1, vector<ii>(n+1));
    vector<ii> lst(n+1, make_pair(-inf, 0));
    for (int tam = l; tam <= n; ++tam) {
        // posso pegar dp[i] ^ dp[j], onde tam-R <= i+j <= tam-L
        // sempre posso adicionar tam-L
        for (int i = (tam-l+1)/2; i <= tam-l; ++i) {
            int x = dp[i] ^ dp[tam-l-i];
            if (x <= n) lst[x] = make_pair(tam-l, i);
        }
        for (int i = 0; ; ++i) {
            if (lst[i].first < tam - r) { dp[tam] = i; break; }
            tr[tam][i] = lst[i];
        }
    }
    vector<ii> v = {{1, n}};
    int state = dp[n];
    cout << (state ? "First" : "Second") << endl;
    for (int turn = (state != 0); ; turn ^= 1) {
        int x = -1, y = -1, id = -1;
        if (turn) {
            assert(state);
            int msb = 0;
            while ((2 << msb) <= state) ++msb;
            for (int i = 0; i < sz(v); ++i) {
                auto [lx, rx] = v[i];
                int t = rx-lx+1;
                if (dp[t] >> msb & 1) {
                    int want = state ^ dp[t];
                    auto [ntam, esq] = tr[t][want];
                    x = lx + esq, y = t - ntam, id = i;
                    break;
                }
            }
            assert(x != -1);
            state = 0;
            cout << x << ' ' << y << endl;
        } else {
            cin >> x >> y;
            assert(x >= 0);
            if (x == 0) return;
            for (int i = 0; i < sz(v); ++i) {
                auto [lx, rx] = v[i];
                if (lx <= x and x <= rx) {
                    id = i;
                    break;
                }
            }
            assert(id != -1);
            auto [lx, rx] = v[id];
            state ^= dp[rx-lx+1];
            state ^= dp[x-lx];
            state ^= dp[rx-x-y+1];
        }
        auto [lx, rx] = v[id];
        v.erase(begin(v) + id);
        if (x != lx) v.pb({lx, x-1});
        if (x + y <= rx) v.pb({x + y, rx});
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
