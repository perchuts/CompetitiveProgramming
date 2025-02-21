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
    string s; cin >> s;
    int n = sz(s);
    int l = n/2, r = n, ans = l;
    auto possible = [&] (int k) {
        // do k+1 then k
        // i + k <= n
        // first n-k characters are good to go
        // last n-k characters are good to go
        // n - 2*n+ 2k
        // 2k - n characters left!
        // n
        bool ok = 1;
        for (int i = n-k; i < k; ++i) ok &= (s[i] == s[n-k]);
        return ok;
        // (n - k) OK (2k-n) X (n - k) OK
        //
        return true;
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, l = md+1;
        else r = md-1;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
