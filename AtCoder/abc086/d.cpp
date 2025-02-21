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

void solve(){
    int n, k; cin >> n >> k;
    vector<iii> v(n);
    for (auto& [x, y, z] : v) {
        char c; cin >> x >> y >> c;
        x %= (2*k);
        y %= (2*k);
        z = (c == 'B');
    }
    int ans = 0;
    for (int col = k; ~col; --col) {
        vector<int> events(k+1);
        int cur = 0;
        for (auto [x, y, z] : v) {
            // aqui estou basicamente
            x += (k - col);
            if (x >= 2*k) x -= 2*k;
            int cor = 0;
            if ((x < k) == (y < k)) cor = 1;
            if (cor == z) {
                cur++; 
                if (y < k) events[y+1]--;
                else events[y-k+1]--;
            } else {
                if (y < k) events[y+1]++;
                else events[y-k+1]++;
            }
        }
        for (int i = 0; i <= k; ++i) cur += events[i], ckmax(ans, max(cur, n-cur));
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
