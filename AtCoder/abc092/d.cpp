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
    vector<int> a(n), b(n);
    int o1 = 0, o2 = 0;
    for (auto& x : a) cin >> x, o1 += (x&1);
    for (auto& x : b) cin >> x, o2 += (x&1);
    vector<int> qnt(31);
    qnt[0] = o1 * (n-o2) + o2 * (n-o1);
    for (int bit = 1; bit < 30; ++bit) {
        int m = (1LL << (bit+1)) - 1, p = (1 << bit);
        sort(all(b), [&] (int x, int y) {
            return (x & m) < (y & m);
        });
        for (auto x : a) {
            x &= m;
            int l = p-x, r = m-x;
            if (l < 0) {
                l += m+1;
                int lx = 0, rx = n-1, p1 = -1;
                while (lx <= rx) {
                    int md = lx + (rx-lx+1)/2;
                    if ((b[md]&m) <= r) p1 = md, lx = md+1;
                    else rx = md-1;
                }
                lx = 0, rx = n-1; int p2 = n;
                while (lx <= rx) {
                    int md = lx + (rx-lx+1)/2;
                    if (l <= (b[md]&m)) p2 = md, rx = md-1;
                    else lx = md+1;
                }
                qnt[bit] += n-p2 + p1+1;
            } else {
                int lx = 0, rx = n-1, p1 = n;
                while (lx <= rx) {
                    int md = lx + (rx-lx+1)/2;
                    if (l <= (b[md]&m)) p1 = md, rx = md-1;
                    else lx = md+1;
                }
                lx = 0, rx = n-1; int p2 = -1;
                while (lx <= rx) {
                    int md = lx + (rx-lx+1)/2;
                    if (r >= (b[md]&m)) p2 = md, lx = md+1;
                    else rx = md-1;
                }
                qnt[bit] += max(0LL, p2-p1+1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 30; ++i) if (qnt[i] & 1) ans += (1 << i);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
