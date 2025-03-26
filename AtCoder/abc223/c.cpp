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
    double tot = 0;
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], tot += a[i];
    double l = 0, r = 1e9, K;
    while (abs(r-l) > 1e-7) {
        double md = (l+r)/2, esq = 0, dir = 0, fl = md, fr = md;
        for (int i = 0; i < n; ++i) {
            double k = min(fl, a[i]/(double)b[i]);
            esq += k * b[i];
            fl -= k;
        }
        for (int i = n-1; ~i; --i) {
            double k = min(fr, a[i]/(double)b[i]);
            dir += k * b[i];
            fr -= k;
        }
        K = esq;
        if (esq + dir > tot) r = md;
        else l = md;
    }
    cout << fixed << setprecision(10) << K << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
