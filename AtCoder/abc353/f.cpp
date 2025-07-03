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
    int k, a, b, c, d; cin >> k >> a >> b >> c >> d;
    if (k == 1) {
        cout << abs(a-c) + abs(b-d) << endl;
        exit(0);
    }
    auto get = [&] (int x1, int y1, int x2, int y2) {
        x1 /= k, y1 /= k, x2 /= k, y2 /= k;
        int d1 = abs(x1+y1-(x2+y2));
        int d2 = abs(x1-y1-(x2-y2));
        if (k != 2) return d1+d2;
        return max(d1, d2) + min(d1, d2)/2;
    };
    auto process = [&] (int x, int y) {
        int coord = (x/k + y/k);
        if (coord % 2 == 1) return vector<ii>(1, pair(x, y));
        x /= k, y /= k; 
        vector<ii> sexo{pair(x-1, y), pair(x+1, y), pair(x, y-1), pair(x, y+1)};
        for (auto& [aa, bb] : sexo) aa *= k, bb *= k;
       return sexo;
    };
    auto get2 = [&] (int x1, int y1, int x2, int y2) {
        if (x1 == x2 and y1 == y2) return 0LL;
        int ans = 9e18;
        int subir = k - y2 % k;
        int descer = y2 % k + 1;
        int esq = x2 % k + 1;
        int dir = k - x2 % k;
        int ex = x2/k, ey = y2/k; ex *= k, ey *= k;
        ckmin(ans, get(ex, ey+k, x1, y1) + subir);
        ckmin(ans, get(ex, ey-k, x1, y1) + descer);
        ckmin(ans, get(ex-k, ey, x1, y1) + esq);
        ckmin(ans, get(ex+k, ey, x1, y1) + dir);
        return ans;
    };
    vector<ii> p1 = process(a, b), p2 = process(c, d);
    int ans = abs(a-c)+abs(b-d);
    for (auto [x1, y1] : p1) {
        for (auto [x2, y2] : p2) {
            ckmin(ans, get(x1, y1, x2, y2) + get2(x1, y1, a, b) + get2(x2, y2, c, d));
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
