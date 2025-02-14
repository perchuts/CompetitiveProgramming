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
    int n, a, b, c; cin >> n >> c >> b >> a;
    vector<int> sexo = {a, b, c};
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    int ans = 1e18;
    for (int i = 0; i < (1 << (2*n)); ++i) {
        int cur = i;
        vector<int> groups(4), cnt(4);
        for (int j = 0; j < n; ++j) {
            groups[cur%4] += v[j], cnt[cur%4]++; 
            cur /= 4;
        }
        if (min({cnt[0], cnt[1], cnt[2]}) == 0) continue;
        cur = (cnt[0] + cnt[1] + cnt[2] - 3) * 10;
        vector<int> p(3); iota(all(p), 0);
        do {
            int cur2 = cur;
            for (int j = 0; j < 3; ++j) cur2 += abs(sexo[p[j]] - groups[j]);
            ckmin(ans, cur2);
        } while (next_permutation(all(p)));
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
