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
    int x = 0;
    for (int i = 2; i < n; ++i) x ^= v[i];
    int ambos = v[0] + v[1] - x;
    if (ambos % 2 or ambos < 0) {
        cout << -1 << endl;
        exit(0);
    }
    ambos /= 2;
    vector<int> bits;
    int X = ambos, Y = ambos;
    for (int i = 50; ~i; --i) if (x >> i & 1) {
        if (ambos >> i & 1) continue;
        if (X + (1LL << i) <= v[0]) X += (1LL << i);
        else Y += (1LL << i);
    }
    int ans = v[0] - X;
    if (ans >= v[0] or ans < 0 or ((X ^ Y) != x)) {
        cout << -1 << endl;
        exit(0);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
