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
    int n, k; cin >> n >> k;
    vector<int> a(n), setinha(n);
    for (auto& x : a) cin >> x;
    int l = 1, r = inf, ans = 1;
    auto possible = [&] (int x) {
        int S = 0, qnt = 0;
        while (S < x and qnt < n) S += a[qnt++];
        if (S < x) return false;
        setinha[0] = qnt;
        for (int i = 1; i < n; ++i) {
            S -= a[i-1], qnt--;
            while (S < x) S += a[(qnt+i)%n], qnt++;
            setinha[i] = qnt;
        }
        int cur = 0;
        for (int i = 0; i < n; ++i) cur = (cur + setinha[cur]) % n;
        int tot = 0;
        for (int i = 0; i < k; ++i) tot += setinha[cur], cur = (cur + setinha[cur]) % n;
        return (tot <= n);
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, l = md+1;
        else r = md-1;
    }
    // get setinhas updated
    possible(ans);
    vector<vector<int>> bl(n, vector<int>(20));
    for (int j = 0; j < 20; ++j) {
        for (int i = 0; i < n; ++i) {
            if (j == 0) bl[i][j] = setinha[i];
            else {
                int x = (i + bl[i][j-1]) % n;
                bl[i][j] = bl[i][j-1] + bl[x][j-1];
            }
        }
    }
    int ans2 = 0;
    for (int i = 0; i < n; ++i) {
        int tot = 0, cur = i;
        for (int j = 0; j < 20; ++j) {
            if (k >> j & 1) {
                tot += bl[cur][j];
                cur = (cur + bl[cur][j]) % n;
            }
        }
        ans2 += (tot > n);
    }
    cout << ans << ' ' << ans2 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
