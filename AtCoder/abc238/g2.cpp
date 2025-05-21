#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int sexo[maxn], freq[maxn], v1[maxn], v2[maxn];
const int MAX = 2e5+10;
vector<ii> bichos[MAX];
void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> pr(n+1);
    for (int i = 2; i < maxn; ++i) {
        if (sexo[i]) continue;
        sexo[i] = i;
        v1[i] = rnd(0, -1ULL);
        v2[i] = rnd(0, -1ULL);
        for (int j = i * i; j < maxn; j += i) if (sexo[j] == 0) sexo[j] = i; 
    }
    for (int i = 0; i < n; ++i) {
        int cur = a[i];
         pr[i+1] = pr[i];
        while (cur != 1) {
            int p = sexo[cur], t = 0;
            while (sexo[cur] == p) cur /= p, t++;
            t %= 3;
            while (t) {
                if (freq[p] == 0) pr[i+1] ^= v1[p];
                else if (freq[p] == 1) pr[i+1] ^= v2[p];
                else pr[i+1] ^= v1[p] ^ v2[p];
                freq[p]++, t--;
                freq[p] %= 3;
            }
        }
    }
    while (q--) {
        int l, r; cin >> l >> r;
        int x = pr[r] ^ pr[l-1];
        cout << (x ? "No" : "Yes") << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
