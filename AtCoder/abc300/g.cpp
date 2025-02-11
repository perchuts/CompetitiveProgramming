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
    int n, p; cin >> n >> p;
    map<ii, int> dp;
    vector<int> primes;
    for (int i = 2; i <= p; ++i) {
        bool ok = 1;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                ok = false;
                break;
            }
        }
        if (ok) primes.pb(i);
    }
    vector<int> caras = {1};
    vector<int> caras2 = {1};
    vector<int> caras3 = {1};
    for (auto x : primes) {
        int cur = n, tot = 0;
        while (cur >= x) tot++, cur /= x;
        if (x <= 17) {
            vector<int> ncaras = caras;
            for (int i = 1, pot = x; i <= tot; ++i, pot *= x) {
                for (auto y : caras) {
                    if (y > n/pot) break;
                    ncaras.pb(y*pot);
                }
            }
            swap(caras, ncaras);
            sort(all(caras));
        } else if (x <= 50) {
            vector<int> ncaras = caras2;
            for (int i = 1, pot = x; i <= tot; ++i, pot *= x) {
                for (auto y : caras2) {
                    if (y > n/pot) break;
                    ncaras.pb(y*pot);
                }
            }
            swap(caras2, ncaras);
            sort(all(caras2));
        } else {
            vector<int> ncaras = caras3;
            for (int i = 1, pot = x; i <= tot; ++i, pot *= x) {
                for (auto y : caras3) {
                    if (y > n/pot) break;
                    ncaras.pb(y*pot);
                }
            }
            swap(caras3, ncaras);
            sort(all(caras3));
        }
    }
    int ans = 0;
    for (auto x : caras2) {
        for (auto y : caras3) {
            if (y > n/x) break;
            int l = 0, r = sz(caras)-1, tot = 0;
            int eu = x*y;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                if (caras[md] <= n/eu) tot = md, l = md+1;
                else r = md-1;
            }
            ans += tot+1;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
