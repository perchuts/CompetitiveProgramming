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
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    int mod5 = 1, cur = n, p5 = 0;
    while (cur) {
        p5 += cur / 5;
        int k = cur % 5;
        cur /= 5;
        for (int i = 1; i <= k; ++i) mod5 = mod5 * i % 5;
    }
    for (int i = 0; i < p5%4; ++i) mod5 = mod5 * 3 % 5;
    if (p5 & 1) mod5 = 4 * mod5 % 5;
    if (mod5 % 2) mod5 += 5;
    cout << mod5 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
