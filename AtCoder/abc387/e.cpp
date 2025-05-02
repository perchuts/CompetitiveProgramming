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
    if (sz(s) <= 7) {
        int n = stoi(s);
        auto get = [] (int k) {
            int s = 0;
            while (k) s += k % 10, k /= 10;
            return s;
        };
        for (int a = n; a < 2*n; ++a) {
            int sa = get(a), sb = get(a+1);
            if (a % sa == 0 and (a+1) % sb == 0) {
                cout << a << endl;
                exit(0);
            }
        }
        cout << -1 << endl;
        exit(0);
    }
    if ('2' <= s[0] and s[0] <= '7') {
        cout << char(s[0]+1);
        for (int i = 1; i <= sz(s)-5; ++i) cout << '0';
        cout << char('0'+abs(s[0]-'0'-7));
        cout << "000" << endl;
        exit(0);
    } else if ('8' <= s[0]) {
        cout << "1";
        for (int i = 1; i <= sz(s)-2; ++i) cout << "0";
        cout << "11";
    } else {
        bool ok = 1;
        for (int j = 1; j < sz(s); ++j) ok &= (s[j] == '0');
        if (ok) {
            cout << "1";
            for (int i = 1; i <= sz(s)-3; ++i) cout << "0";
            cout << "11";
        } else {
            cout << "2";
            for (int i = 1; i <= sz(s)-1; ++i) cout << "0";
        }
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
