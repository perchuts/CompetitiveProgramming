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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(all(a));
    reverse(all(a));
    vector<int> ans(n);
    int pl = 0, pr = n-1, p1 = 0, p2 = 0;
    for (int i = 0; i < n/2-1; ++i) {
        if (i&1) ans[pr] = a[n/2+p1], p1++, ans[pr-1] = a[p2], p2++, pr -= 2;
        else ans[pl] = a[n/2+p1], p1++, ans[pl+1] = a[p2], p2++, pl += 2;
    }
    if ((n/2-1)&1) ans[pl] = a[n/2+p1], ans[pr] = a[n/2+p1+1], ans[pl+1] = a[p2];
    else ans[pl] = a[n/2+p1+1], ans[pr] = a[n/2+p1], ans[pl+1] = a[p2];
    bool ok = 1;
    a = ans;
    for (int i = 1; i < n; i += 2) ok &= (a[i] > max(a[i-1], a[i+1]));
    cout << (ok ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
