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
    int n, m, A, B; cin >> n >> m >> A >> B;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    // todo mundo em a[] eh igual, todo mundo em b[] eh igual
    // (vai ser contado la embaixo)
    A++, B++;
    int ans = A*B;
    // todo mundo em a[] eh igual, b[] tem dois e vice versa
    ans = (ans + (B * (B-1) / 2) % mod * A % mod * (mod+fexp(2, m)-2) % mod + (A * (A-1) / 2) % mod * B % mod * (mod+fexp(2, n)-2)) % mod;
    // dois diferentes em a[]
    // {a, b} - {c, d} a^c, b^c. a^b^c=d. contar numero de triplas (a,b,c) com a!=b e a^b^c<=B, a, b <= A
    // a^c, b^c, a^(a^b^c), b^(a^b^c)
    // a^c, b^c, b^c, a^c
    vector dp(2, vector(2, vector(2, vector(2, 0LL))));
    dp[1][1][1][1] = 1;
    for (int i = 30; ~i; --i) {
        vector ndp(2, vector(2, vector(2, vector(2, 0LL))));
        int bA = A >> i & 1, bB = B >> i & 1;
        for (int fa = 0; fa < 2; ++fa) {
            for (int fb = 0; fb < 2; ++fb) {
                for (int fc = 0; fc < 2; ++fc) {
                    for (int fd = 0; fd < 2; ++fd) {
                        for (int ba = 0; ba < 2; ++ba) {
                            for (int bb = 0; bb < 2; ++bb) {
                                for (int bc = 0; bc < 2; ++bc) {
                                    int bd = ba ^ bb ^ bc;
                                    int nfa = fa && (ba == bA);
                                    int nfb = fb && (bb == bA);
                                    int nfc = fc && (bc == bB);
                                    int nfd = fd && (bd == bB);
                                    if (fa and ba > bA) continue;
                                    if (fb and bb > bA) continue;
                                    if (fc and bc > bB) continue;
                                    if (fd and bd > bB) continue;
                                    ndp[nfa][nfb][nfc][nfd] += dp[fa][fb][fc][fd];
                                    if (ndp[nfa][nfb][nfc][nfd] >= mod) ndp[nfa][nfb][nfc][nfd] -= mod;
                                }
                            }
                        }
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    // e o caso em que A = B?
    // A = B = i
    // d = A^B^C -> D = C
    // esse caso eh basicamente o caso A*B
    dp[0][0][0][0] = (mod - (A*B)%mod + dp[0][0][0][0]) % mod;
    dp[0][0][0][0] = dp[0][0][0][0] * fexp(4, mod-2) % mod;
    int x1 = (fexp(2, n) + mod - 2) % mod, x2 = (fexp(2, m) + mod - 2) % mod;
    ans = (ans + dp[0][0][0][0] * x1 % mod * x2) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
