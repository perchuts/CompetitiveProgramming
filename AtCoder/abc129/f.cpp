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
    int l, a, b, m; cin >> l >> a >> b >> m;
    vector<ii> ranges(19, make_pair(-1, -1));
    vector<int> ten(19, 1);
    for (int i = 1; i <= 18; ++i) ten[i] = 10 * ten[i-1];
    for (int i = sz(to_string(a)); i <= 18; ++i) {
        int prim = max(0LL, (ten[i-1] - a + b - 1) / b);
        int ult = min(l-1, (ten[i] - a + b - 1) / b - 1);
        if (prim <= ult) ranges[i] = {prim, ult};
        if (ult == l-1) break;
    }
    using matrix = vector<vector<int>>;
    auto mult = [&] (matrix a, matrix b) {
        matrix res(4, vector<int>(4));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % m;
                }
            }
        }
        return res;
    };
    auto fexp2 = [&] (matrix x, int e) {
        matrix ans(4, vector<int>(4));
        for (int i = 0; i < 4; ++i) ans[i][i] = 1;
        while (e) {
            if (e&1) ans = mult(ans, x);
            x = mult(x, x), e /= 2;
        }
        return ans;
    };
    int c_i = 0, b_i = ((-b)%m+m)%m;
    assert(b_i >= 0);
    for (int i = 1; i <= 18; ++i) {
        auto [lx, rx] = ranges[i];
        if (lx == -1) continue;
        matrix mat(4, vector<int>(4));
        mat[0][0] = ten[i] % m;
        mat[0][1] = mat[0][2] = mat[0][3] = mat[1][1] = mat[1][2] = mat[2][2] = mat[3][3] = 1;
        auto M = fexp2(mat, rx-lx+1);
        int c_rx = (M[0][0] * (c_i%m) + M[0][1] * (b_i%m) + M[0][2] * (b%m) + M[0][3] * (a%m)) % m;
        int b_rx = (M[1][0] * (c_i%m) + M[1][1] * (b_i%m) + M[1][2] * (b%m) + M[1][3] * (a%m)) % m;
        c_i = c_rx, b_i = b_rx;
    }
    cout << c_i << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
