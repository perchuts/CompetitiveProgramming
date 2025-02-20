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
    vector<int> v(4);
    for (int i = 0; i < 4; ++i) {
        char c; cin >> c;
        v[i] = c - '0';
    }
    for (int i = 0; i < 8; ++i) {
        int ans = v[0];
        for (int j = 0; j < 3; ++j) {
            if (i >> j & 1) ans += v[j+1];
            else ans -= v[j+1];
        }
        if (ans == 7) {
            cout << v[0];
            for (int j = 0; j < 3; ++j) {
                if (i >> j & 1) cout << "+";
                else cout << "-";
                cout << v[j+1];
            }
            cout << "=7" << endl;
            exit(0);
        }
    }
    assert(false);
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
