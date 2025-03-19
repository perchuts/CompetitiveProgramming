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
    int p = 7; cin >> p;
    //vector<int> a(p);
    //for (auto& x : a) cin >> x;
    vector<int> poly(p);
    vector<vector<int>> pot(p, vector<int>(p, 1));
    for (int i = 0; i < p; ++i) for (int j = 1; j < p; ++j) pot[i][j] = i * pot[i][j-1] % p;
    auto brute = [&] (auto&& self, int id) -> void {
        if (id == p) {
            vector<int> val(p);
            for (int i = 0; i < p; ++i) {
                for (int j = 0; j < p; ++j) val[i] = (val[i] + pot[i][j] * poly[j]) % p;
            }
            bool nice = 0;
            for (int i = 0; i < p; ++i) {
                bool ok = 1;
                for (int j = 0; j < p; ++j) {
                    if (i == j) ok &= (val[j] == 1);
                    else ok &= (val[j] == 0);
                }
                nice |= ok;
            }
            if (nice) {
                cout << "P[x] = ";
                for (auto x : poly) cout << x << ' ';
                cout << endl;
                for (int i = 0; i < p; ++i) {
                    cout << "f("<<i<<") = " << val[i];
                    if (i < p-1) cout << ", ";
                    else cout << endl;
                }
            }
            return;
        }
        for (int i = 0; i < p; ++i) poly[id] = i, self(self, id+1);
    };
    brute(brute, 0);
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
