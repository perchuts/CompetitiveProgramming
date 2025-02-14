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
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<int> freq(100050), freq2(100050);
    for (int i = 0; i < n; i += 2) freq[v[i]]++;
    for (int i = 1; i < n; i += 2) freq2[v[i]]++;
    vector<int> ord(100050), ord2(100050);
    iota(all(ord), 0); ord2 = ord;
    sort(all(ord), [&] (int x, int y) {
        return freq[x] > freq[y];
    });
    sort(all(ord2), [&] (int x, int y) {
        return freq2[x] > freq2[y];
    });
    int ans = n;
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
        if (ord[i] == ord2[j]) continue;
        ckmin(ans, n - freq[ord[i]] - freq2[ord2[j]]);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
