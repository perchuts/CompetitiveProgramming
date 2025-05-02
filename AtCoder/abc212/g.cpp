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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int P; cin >> P;
    // eu sei que x^{P-1} === x mod P
    // (peq. teo. de fermat)
    // entao eu sei que o tamanho do ciclo de x eh um divisor de P
    // quero resolver mais lento pra x <= sqrt(P), e resolver rapido pra x > sqrt(P)
    vector<int> divs;
    for (int i = 1; i * i <= P-1; ++i) {
        if ((P-1) % i) continue;
        divs.pb(i);
        if (i * i != (P-1)) divs.pb((P-1)/i);
    }
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    vector<int> qnt(sz(divs));
    sort(all(divs));
    int ans = 0;
    for (int i = sz(divs)-1; ~i; --i) {
        qnt[i] = (P-1)/divs[i];
        for (int j = i+1; j < sz(divs); ++j) {
            if (divs[j] % divs[i]) continue;
            qnt[i] -= qnt[j];
        }
        int x = fexp(divs[i]%mod, mod-2);
        ans = (ans + qnt[i] % mod * x) % mod;
    }
    ans = (P-1)%mod * ans % mod;
    cout << (ans+1) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
