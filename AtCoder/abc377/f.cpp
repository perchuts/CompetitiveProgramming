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
    int n, m; cin >> m >> n;
    int ans = 0;
    vector<int> xi(n), yi(n);
    for (int i = 0; i < n; ++i) cin >> xi[i] >> yi[i];
    for (int i = 0; i < n; ++i) {
        int a = 1, b = 1, c = 1, d = 1;
        for (int j = 0; j < i; ++j) {
            if (xi[j] == xi[i]) a = 0;
            if (yi[j] == yi[i]) b = 0;
            if (xi[j] + yi[j] == xi[i] + yi[i]) c = 0;
            if (xi[j] - yi[j] == xi[i] - yi[i]) d = 0;
        }
        map<ii, int> caras;
        int tot = min({a, b, c, d}), pp = (xi[i] + yi[i]) % 2;
        // diversao garantida!
        if (a) {
            tot += m - 1;
            set<ii> sexo;
            for (int j = 0; j < i; ++j) {
                sexo.insert({xi[i], yi[j]});
                // xj, yj
                // xi + (k) == xj + yj
                // k = xj + yj - xi
                int k = xi[j] + yi[j] - xi[i];
                if (1 <= k and k <= m) sexo.insert({xi[i], k});
                // xi - (k) == xj - yj
                // k == xi - xj + yj
                k = xi[i] - xi[j] + yi[j];
                if (1 <= k and k <= m) sexo.insert({xi[i], k});
            }
            for (auto [x, y] : sexo) caras[{x, y}]++;
        }
        if (b) {
            tot += m - 1;
            set<ii> sexo;
            for (int j = 0; j < i; ++j) {
                sexo.insert({xi[j], yi[i]});
                // xj, yj
                // k + yi == xj + yj
                // k = xj + yj - yi
                int k = xi[j] + yi[j] - yi[i];
                if (1 <= k and k <= m) sexo.insert({k, yi[i]});
                // k - yi[i] == xj - yj
                // k == yi + xj - yj
                k = yi[i] + xi[j] - yi[j];
                if (1 <= k and k <= m) sexo.insert({k, yi[i]});
            }
            for (auto [x, y] : sexo) caras[{x, y}]++;
        }
        if (c) {
            tot += min(xi[i]+yi[i]-1, 2*m+1 - xi[i] - yi[i]) - 1;
            //cout << min(xi[i]+yi[i]-1, 2*m+1 - xi[i] - yi[i]) - 1 << endl;
            set<ii> sexo;
            for (int j = 0; j < i; ++j) {
                if (pp == (xi[j] + yi[j]) % 2) {
                    // xj, yj
                    // A + B == xi + yi
                    // A - B == xj - yj
                    // A == (xi + yi + xj - yj) / 2
                    int a = (xi[i] + yi[i] + xi[j] - yi[j]) / 2;
                    int b = xi[i] + yi[i] - a;
                    if (1 <= min(a, b) and max(a, b) <= m) sexo.insert({a, b});
                }
                // xj, B
                // xj + B == xi + yi
                // B = xi + yi - xj
                b = xi[i] + yi[i] - xi[j];
                if (1 <= b and b <= m) sexo.insert({xi[j], b});

                // a, yj
                // a+yj == xi + yi
                // a == xi + yi - yj
                a = xi[i] + yi[i] - yi[j];
                if (1 <= a and a <= m) sexo.insert({a, yi[j]});
            }
            for (auto [x, y] : sexo) caras[{x, y}]++;
        }
        if (d) {
            tot += m - abs(xi[i]-yi[i]) - 1;
            set<ii> sexo;
            for (int j = 0; j < i; ++j) {
                if (pp == (xi[j] + yi[j]) % 2) {
                    // xj, yj
                    // A + B == xj + yj
                    // A - B == xi - yi
                    // A == (xj + yj + xi - yi) / 2
                    int a = (xi[i] - yi[i] + xi[j] + yi[j]) / 2;
                    int b = xi[j] + yi[j] - a;
                    if (1 <= min(a, b) and max(a, b) <= m) sexo.insert({a, b});

                }
                // xj, B
                // xj - B == xi - yi
                // B = xj - xi + yi
                b = xi[j] - xi[i] + yi[i];
                if (1 <= b and b <= m) sexo.insert({xi[j], b});

                // a, yj
                // a-yj == xi - yi
                // a == xi - yi + yj
                a = xi[i] - yi[i] + yi[j];
                if (1 <= a and a <= m) sexo.insert({a, yi[j]});

            }
            for (auto [x, y] : sexo) caras[{x, y}]++;
        }
        for (auto [x, y] : caras) {
            if (x.first != xi[i] or x.second != yi[i]) tot -= y;
        }
        ans += tot;
    }
    cout << m*m-ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

