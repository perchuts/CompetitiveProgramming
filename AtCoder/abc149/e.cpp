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
    vector<int> a(n), ps(n);
    for (auto& x : a) cin >> x;
    sort(rbegin(a), rend(a));
    for (int i = 0; i < n; ++i) ps[i] = (i ? ps[i-1] : 0) + a[i];
    auto qnt = [&] (int x) {
        int tot = 0, j = n-1;
        for (int i = 0; i < n; ++i) {
            while (j >= i and a[i] + a[j] < x) j--;
            if (j < i) break;
            tot += 2 * (j-i) + 1;
        }
        return tot;
    };
    int l = 0, r = 200001, ans = 0;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (qnt(md) <= m) ans = md, r = md-1;
        else l = md+1;
    }
    int tot = (m-qnt(ans)) * (ans-1), j = n-1;
    for (int i = 0; i < n; ++i) {
        while (j >= i and a[i] + a[j] < ans) j--;
        if (j < i) break;
        tot += 2*(j-i+1) * a[i] + 2*(ps[j] - ps[i]);
    }
    cout << tot << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
