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
    int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
    int num = 0, dem = -1;
    vector<int> pode;
    for (int i = 0; i * c <= f; ++i) for (int j = 0; i * c + j * d <= f; ++j) pode.pb(i*c + j * d);
    sort(all(pode));
    pode.erase(unique(all(pode)), end(pode));
    for (int i = 0; i * a * 100 <= f; ++i) {
        for (int j = 0; i * a * 100 + j * b * 100 <= f; ++j) {
            if (i == 0 and j == 0) continue;
            int agua = i * a * 100 + 100 * j * b;
            int mx = min(f-agua, e * (i * a + j * b));
            int eu = upper_bound(all(pode), mx) - begin(pode) - 1;
            if (eu >= 0) {
                if (dem == -1) num = 100 * pode[eu], dem = agua + pode[eu];
                else if (num * (agua+pode[eu]) < dem * 100 * pode[eu]) num = 100 * pode[eu], dem = agua + pode[eu];
            }
        }
    }
    cout << dem << ' ' << num/100 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
