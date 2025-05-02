#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
template<std::size_t N>
bool operator<(const std::bitset<N>& x, const std::bitset<N>& y)
{
    for (int i = N-1; i >= 0; i--) {
        if (x[i] ^ y[i]) return y[i];
    }
    return false;
}

void solve(){
    int k, n, m; cin >> k >> n >> m;
    vector<ii> caras(k);
    for (auto& [x, y] : caras) cin >> x >> y;
    vector<vector<bitset<100>>> bicho(k, vector<bitset<100>>(2));
    int S = 0;
    for (int i = 0; i < k; ++i) {
        auto [ax, ay] = caras[i];
        S += ax * ay;
        for (int j = 0; j < 2; ++j) {
            for (int a = 0; a < ax; ++a) for (int b = 0; b < ay; ++b) bicho[i][j][m*a+b] = 1;
            swap(ax, ay);
        }
    }
    if (S < n*m) {
        cout << "No" << endl;
        exit(0);
    }
    vector<int> p(k); iota(all(p), 0);
    do {
        for (int mask = 0; mask < (1 << k); ++mask) {
            bitset<100> grid;
            int tot = 0;
            for (int ww = 0; ww < k; ++ww) {
                int idx = p[ww];
                int xx = 0, yy = 0, found = 0;
                for (int i = 0; i < n and !found; ++i) for (int j = 0; j < m; ++j) {
                    if (grid[m*i+j] == 0) {
                        found = 1;
                        xx = i, yy = j;
                        break;
                    }
                }
                auto [ax, ay] = caras[idx];
                if (mask >> ww & 1) swap(ax, ay);
                if (!(ax+xx <= n and ay+yy <= m)) break;
                auto rect = bicho[idx][mask>>ww&1];
                rect <<= (xx*m+yy); grid |= rect;
                tot += ax*ay;
                int cntt = grid.count();
                if (tot > n*m or cntt != tot) break;
                if (cntt == n*m) {
                    cout << "Yes" << endl;
                    exit(0);
                }
            }
        }
    } while (next_permutation(all(p)));
    cout << "No" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

