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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, d; cin >> n >> d;
    d++;
    auto fexp = [&] (vector<vector<int>> m, int k) {
        int e = n-1;
        vector<vector<int>> res(2, vector<int>(2));
        res[0][0] = 1, res[1][1] = 1;
        while (e) {
            if (e&1) {
                vector<vector<int>> r(2, vector<int>(2));
                for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k) r[i][j] = (r[i][j] + res[i][k] * m[k][j]) % mod;
                res = r;
            }
            e /= 2;
            vector<vector<int>> m2(2, vector<int>(2));
            for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k) m2[i][j] = (m2[i][j] + m[i][k] * m[k][j]) % mod;
            m = m2;
        }
        return res;
    };
    int ans = 1;
    vector<int> fat(d+1, 1), ifat(d+1);
    auto inv = [&] (int b) {
        int ans = 1, e = mod-2;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    for (int i = 1; i <= d; ++i) fat[i] = i * fat[i-1] % mod;
    ifat.back() = inv(fat.back());
    for (int i = d-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto c = [&] (int a, int b) {
        if (b > a or min(a, b) < 0) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    for (int k = 1; k <= d; ++k) {
        vector<vector<int>> mat(2, vector<int>(2));
        mat[0][0] = c(d-2, k);
        mat[0][1] = mat[1][0] = c(d-2, k-1);
        mat[1][1] = c(d-2, k-2);
        auto m = fexp(mat, k);
        ans = (ans + m[0][0] * c(d-2, k)) % mod;
        ans = (ans + (m[1][0] + m[0][1]) * c(d-2, k-1)) % mod;
        ans = (ans + m[1][1] * c(d-2, k-2)) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
