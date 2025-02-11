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
    // so nao posso vacilar e pegar o xor de todo mundo (se ele so existir uma vez)
    vector<int> basis(60), b, cnt(60);
    int tudo = 0;
    for (int i = 0; i < n; ++i) {
        int cur = v[i];
        tudo ^= v[i];
        for (int j = 0; j < 60; ++j) {
            if (cur >> j & 1) {
                if (basis[j] == 0) { basis[j] = cur, b.pb(cur); break; }
                cur ^= basis[j];
            }
        }
        for (int j = 0; j < 60; ++j) {
            if (v[i] >> j & 1) cnt[j]++;
        }
    }
    if (sz(b) == n) {
    }
    deque<int> setado;
    auto ok = [&] () {
        basis = vector<int>(60);
        for (int i = 0; i < n; ++i) {
            int cur = v[i];
            for (auto x : setado) {
                if (cur >> x & 1) {
                    if (basis[x] == 0) { basis[x] = cur; break; }
                    cur ^= basis[x];
                }
            }
        }
        vector<int> flip(60);
        for (auto x : setado) {
            if (flip[x]) continue;
            if (basis[x] == 0) return false;
            for (int j = x; j < 60; ++j) {
                if (basis[x] >> j & 1) flip[j] ^= 1;
            }
        }
        return true;
    };
    int ans = 0;
    for (int j = 59; ~j; --j) {
        if (cnt[j] & 1) ans += (1LL << j); 
        else if (cnt[j]) {
            // vou tentar setar esse bit!
            setado.push_front(j);
            if (!ok()) setado.pop_front();
            else ans += (1LL << (j+1));
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
