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
    int x, y, a, b, c; cin >> x >> y >> a >> b >> c;
    for (int __ = 0; __ < 2; ++__) {
        if ((a+x-1)/x + (b+x-1)/x + (c+x-1)/x <= y) {
            cout << "Yes" << endl;
            exit(0);
        }
        vector<int> v = {a, b, c};
        sort(all(v));
        do {
            // primeiro vai cobrir todo o x enquanto precisar
            int A = v[0], B = v[1], C = v[2];
            int nx = x - (A+y-1)/y;
            if (nx <= 0) continue;
            int sobra = y - (B+nx-1)/nx;
            if (sobra > 0 and sobra * nx >= C) {
                cout << "Yes" << endl;
                exit(0);
            }
        } while(next_permutation(all(v)));
        swap(x, y);
    }
    cout << "No" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
