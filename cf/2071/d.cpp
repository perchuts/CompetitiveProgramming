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
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n+1);
    int xs = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i], xs ^= a[i];
    if (n % 2 == 0) {
        a.pb(0);
        for (int i = 1; i <= (n+1)/2; ++i) a.back() ^= a[i];
        xs ^= a.back();
        n++;
    }
    a.pb(0);
    for (int i = 1; i <= (n+1)/2; ++i) a.back() ^= a[i];
    for (int i = n+2; i <= 2*n+1; ++i) {
        a.pb(0);
        if (i % 2) a[i] = a[i-1];
        else a[i] = a[i-1] ^ a[i/2];
    }
    // just for reference:
    auto get = [&] (auto&& self, int x) -> int {
        if (x <= 2*n+1) return a[x];
        int y = x/2;
        if (y & 1) return xs;
        return self(self, y) ^ xs;
    };
    auto sum = [&] (int k) {
        int tot = 0;
        for (int i = 1; i <= min(k, 2*n+1); ++i) tot += a[i];
        if (k <= 2*n+1) return tot;
        int last = -1;
        //cout << "ini: " << tot << endl;
        if (xs) {
            for (int i = 59; ~i; --i) if (k >> i & 1) {
                if (last != -1 and last % 2 == 1) tot += 1 + (i != 0);
                for (int j = 1; j < i; j += 2) tot += (1LL << (i-j));
                //cout << i << ' ' << tot << endl;
                last = i;
            }
        }
        //cout << tot << endl;
        auto tr = [&] (int x) {
            int cur = xs; x /= 2;
            while (x % 2 == 0) x /= 2, cur ^= xs;
            return cur;
        };
        //cout << 0 << ' ';
        //for (int i = 2; i <= k; ++i) cout << tr(i) << ' ';
        //cout << endl;
        //cout << "0: " << tot << endl;
        for (int i = 2; i <= n; ++i) tot -= tr(i);  
        for (int i = n+1; i <= 2*n+1; ++i) { 
            int score = tr(i);
            tot -= score;
            if (i & 1) continue;
            for (int w = 0; w < 2; ++w) {
                for (int cur = 2*i, val = a[i] ^ xs, val2 = score ^ xs; cur+w <= k; cur *= 2, val ^= xs, val2 ^= xs) {
                    tot += val - val2;
                }
            }
        }
        //cout << "1: " << tot << endl;
        tot += tr(k);
        return tot;
    };
    //sum(9);
    //return;
    int sexo = 0;
    for (int i = 1; i <= 2*n+1; ++i) sexo += a[i];
    //for (int i = 2*n+2; i <= r; ++i) {
    //    a.pb(0);
    //    for (int j = 1; j <= i/2; ++j) a.back() ^= a[j];
    //    sexo += a.back();
    //    if (sexo != sum(i)) {
    //        cout << "Wrong at i = " << i << endl;
    //        cout << "Correct: " << sexo << endl;
    //        cout << "Mine: " << sum(i) << endl;
    //        return;
    //    }
    //}
    int ans = sum(r) - sum(l-1);
    //int cur = l;
    //for (int i = 1; i <= ans; ++i) {
    //    int lx = cur, rx = r, pos = -1;
    //    while (lx <= rx) {
    //        int md = lx + (rx-lx+1)/2;
    //        if (sum(md)-sum(cur-1) > 0) pos = md, rx = md-1;
    //        else lx = md+1;
    //    }
    //    assert(pos != -1);
    //    cur = pos+1;
    //}
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
