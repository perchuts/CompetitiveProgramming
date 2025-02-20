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
    string s; cin >> s;
    int cnt = 0;
    for (auto x : s) cnt += (x == '1');
    vector<ii> pref(n+1), suf(n+2);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1];
        if (s[i-1] == '0') pref[i].first++, pref[i].second += i; 
    }
    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i+1];
        if (s[i-1] == '0') suf[i].first++, suf[i].second += i;
    }
    auto z = [&] (int l, int r) {
        if (l > r) return 0LL;
        int tot = ((r+1)*r/2) - ((l-1)*l/2);
        return tot - (pref[r].second-pref[l-1].second);
    };
    auto qt = [&] (int l, int r) {
        return pref[r].first - pref[l-1].first;
    };

    auto qt2 = [&] (int l, int r) {
        if (l > r) return 0LL;
        return r-l+1-(pref[r].first - pref[l-1].first);
    };
    int ans = 1e18;
    for (int i = 1; i <= n - cnt + 1; ++i) {
        int ri = qt2(i+cnt, n);
        int le = qt2(1, i-1);
        int l = i, r = i+cnt-1, posr = i+cnt, posl = i-1;   
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (qt(md, i+cnt-1) <= ri) posr = md, r = md-1;
            else l = md+1;
        }
        l = i, r = i+cnt-1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (qt(i, md) <= le) posl = md, l = md+1;
            else r = md-1;
        }
        int cur = (pref[posl].second-pref[i-1].second) - z(1, i-1);
        cur += z(i+cnt, n) - (pref[i+cnt-1].second - pref[posr-1].second);
        ckmin(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
