#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    int p; cin >> p;
    vector<int> a(p);
    for (auto& x : a) cin >> x;
    vector<int> poly(p);
    poly[0] = 1;
    for (int i = 0; i < p; ++i) {
        if (a[i] == 0) {
            int t = poly.back();
            for (int j = p-1; ~j; --j) poly[j] = (poly[j] * (p - i) + (j ? poly[j-1] : 0)) % p;
            poly[1] = (poly[1] + t) % p;
        }
    }
    auto fexp = [&] (vector<int> P, int e) {
        vector<int> ans(p);
        ans[0] = 1;
        while (e) {
            if (e&1) {
                vector<int> nans(p);
                for (int i = 0; i < p; ++i) for (int j = 0; j < p; ++j) {
                    int ind = i + j;
                    if (ind >= p) ind -= p-1;
                    nans[ind] = (nans[ind] + ans[i] * P[j]) % p;
                }
                swap(nans, ans);
            }
            vector<int> novo(p);
            for (int i = 0; i < p; ++i) for (int j = 0; j < p; ++j) {
                int ind = i + j;
                if (ind >= p) ind -= p-1;
                novo[ind] = (novo[ind] + P[i] * P[j]) % p;
            }
            swap(novo, P), e /= 2;
        }
        return ans;
    };
    poly = fexp(poly, p-1);
    for (auto x : poly) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
