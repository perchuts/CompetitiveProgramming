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
    int n, m; cin >> n >> m;
    int ans = n * m;
    for (int ww = 0; ww < 2; ++ww) {
        for (int i = 1; i < m; ++i) {
            // posso cortar aqui
            int h1 = n/2;
            vector<int> ar = {i * n, h1 * (m-i), (n-h1) * (m-i)};
            sort(all(ar));
            ckmin(ans, ar.back() - ar.front());
            if (m-i >= 2) {
                h1 = (m-i)/2;
                ar.clear();
                ar = {i * n, h1 * (n), (m-i-h1) * n};
                sort(all(ar));
                ckmin(ans, ar.back() - ar.front());
            }

        }
        swap(n, m);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
