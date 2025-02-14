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
    int t = sz(to_string(n))-1;
    int ans = 0, pot = 9;
    for (int i = 3; i <= t; ++i) {
        pot *= 3; 
        ans += pot - (3 << i) + 3;
    }
    string s = to_string(n);
    int s3 = 0, s5 = 0, s7 = 0;
    n = sz(s);
    auto need = [&] () {
        return (s3 == 0) + (s5 == 0) + (s7 == 0);
    };
    for (int i = 0; i < n; ++i) {
        if ('3' < s[i]) {
            s3++;
            int falta = n-i-1, x = need();
            int p = 1;
            for (int j = 1; j <= falta; ++j) p *= 3;
            if (x == 0) ans += p;
            else if (x == 1) ans += p - (1 << falta);
            else ans += p - (2 << falta) + 1;
            s3--;
        }
        if ('5' < s[i]) {
            s5++;
            int falta = n-i-1, x = need();
            int p = 1;
            for (int j = 1; j <= falta; ++j) p *= 3;
            if (x == 0) ans += p;
            else if (x == 1) ans += p - (1 << falta);
            else ans += p - (2 << falta) + 1;
            s5--;
        }
        if ('7' < s[i]) {
            s7++;
            int falta = n-i-1, x = need();
            int p = 1;
            for (int j = 1; j <= falta; ++j) p *= 3;
            if (x == 0) ans += p;
            else if (x == 1) ans += p - (1 << falta);
            else ans += p - (2 << falta) + 1;
            s7--;
        }
        if (s[i] == '3') s3++;
        else if (s[i] == '5') s5++;
        else if (s[i] == '7') s7++;
        else {
            cout << ans << endl;
            exit(0);
        }
    }
    cout << ans + (need()==0) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
