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
    vector<int> xs;
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        if (c == 'o') xs.pb(0);
        else xs.pb(1);
    }
    string sexo = "SW";
    for (int v1 = 0; v1 < 2; ++v1) {
        for (int v2 = 0; v2 < 2; ++v2) {
            vector<int> vals(n);
            vals[0] = v1, vals[1] = v2;
            for (int j = 1; j < n-1; ++j) vals[j+1] = vals[j-1] ^ xs[j] ^ vals[j];
            bool ok = 1;
            for (int i = 0; i < n; ++i) {
                int j = (i+n-1) % n;
                int k = (i+1) % n;
                int t = vals[j] ^ vals[k];
                ok &= (t == (vals[i] ^ xs[i]));
            }
            if (ok) {
                for (auto x : vals) cout << sexo[x];
                cout << endl;
                exit(0);
            }
        }
    }
    cout << -1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
