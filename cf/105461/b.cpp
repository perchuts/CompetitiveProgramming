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
vector<string> manos[20];
void solve(){
    string n; cin >> n;
    int ans = (sz(n) > 1) + 1;
    for (int i = 1; i < sz(n); ++i) ans += sz(manos[i]);
    int x = upper_bound(begin(manos[sz(n)]), end(manos[sz(n)]), n) - begin(manos[sz(n)]);
    cout << ans + x << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    int lim = 28; 
    for (int i = 0; (i+2)/3 <= lim; ++i) {
        for (int j = 0; (i+2)/3 + (j+1)/2 <= lim; ++j) {
            int qtmx = (i+2)/3 + (j+1)/2;
            for (int k = 0; qtmx + k <= lim; ++k) {
                for (int l = 0; qtmx + k + l <= lim; ++l) {
                    vector<int> caras;
                    for (int w = 0; w < k; ++w) caras.pb(5);
                    for (int w = 0; w < l; ++w) caras.pb(7);
                    for (int w = 0; w < i/3; ++w) caras.pb(8);
                    for (int w = 0; w < j/2; ++w) caras.pb(9);
                    int f2 = i % 3, f3 = j % 2;
                    if (f2 and f3) {
                        caras.pb(6);
                        f2--, f3--;
                    }
                    if (f2 == 1) caras.pb(2);
                    if (f2 == 2) caras.pb(4);
                    if (f3) caras.pb(3);
                    sort(all(caras));
                    string s;
                    for (auto x : caras) s += char('0' + x);
                    if (sz(s) < 20) manos[sz(s)].pb(s);
                }
            }
        }
    }
    for (int i = 0; i < 20; ++i) sort(all(manos[i]));
    while(t--) solve();
}
