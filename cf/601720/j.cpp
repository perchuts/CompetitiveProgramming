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
    vector<int> v(n), p(n), s(n);
    for (auto& x : v) cin >> x;
    for (int turn = 0; turn < 2; ++turn) {
        vector<ii> lista;
        for (int i = 0; i < n; ++i) {
            if (i) {
                if (!turn) p[i] += p[i-1];
                else s[n-i-1] += s[n-i];
            }
            for (auto& [x, y] : lista) x = gcd(x, v[i]);
            lista.pb({v[i], i});
            vector<ii> nlista;
            for (int j = 0; j < sz(lista); ++j) {
                if (nlista.empty() or nlista.back().first != lista[j].first) nlista.pb(lista[j]);
            }
            swap(lista, nlista);
            int ptr = i+1;
            for (int j = sz(lista)-1; ~j; --j) {
                auto [x, y] = lista[j];
                if (!turn) p[i] += x * (ptr-y);
                else s[n-i-1] += x * (ptr-y);
                ptr = y;
            }
        }
        reverse(all(v));
    }
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    int ans = min(p[n-2], s[1])+n;
    for (int i = 1; i < n-1; ++i) ckmin(ans, p[i-1] + s[i+1] + (i+1)*(n-i));
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
