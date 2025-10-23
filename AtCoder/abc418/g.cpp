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

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    // 0000
    vector<array<int, 2>> ans(16, {-1, 0});
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') ans[0][1]++, ans[0][0] = 1;
    }
    // 1000
    {
        // proibidos: 0, 01, 10, 11, 000, 111, 101
        ans[1][1] = (n+1)*n/2;
        if (n >= 4) ans[1][0] = n;
        else if (n == 3 and s != "000" and s != "111" and s != "101") ans[1][0] = 3;
        else if (s == "00" or (n == 3 and s == "000")) ans[1][0] = 2;
        else if (ans[0][1]) ans[1][0] = 1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[1][1]--;
            if (i != n-1 and (s[i] == '1' or s[i+1] == '1')) ans[1][1]--;
            if (i < n-2 and s[i] == '1' and s[i+1] == '1' and s[i+2] == '1') ans[1][1]--;
            if (i < n-2 and s[i] == '1' and s[i+1] == '0' and s[i+2] == '1') ans[1][1]--;
            if (i < n-2 and s[i] == '0' and s[i+1] == '0' and s[i+2] == '0') ans[1][1]--;
        }
    }
    // 0001
    {
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') t = 0;
            else t++, ans[8][1] += t, ckmax(ans[8][0], t);
        }
    }
    // 1001
    {
        vector<vector<ii>> sexo(2, vector<ii>(2, pair(0LL, inf)));
        sexo[1][0] = {1, -1};
        int x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= (s[i] == '1'); 
            ans[9][1] += sexo[i&1][x].first + sexo[(i&1)^1][x^1].first;
            ckmax(ans[9][0], i-sexo[i&1][x].second);
            ckmax(ans[9][0], i-sexo[(i&1)^1][x^1].second);
            sexo[i&1][x].first++;
            ckmin(sexo[i&1][x].second, i);
        }
    }
    // 1111
    {
        ans[15][1] = (n-1)*n/2 + ans[0][1];
        if (n >= 2) ans[15][0] = n;
        else if (s == "1") ans[15][0] = 1;
    }
    // 0111
    {
        ans[14][1] = (n+1)*n/2;
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') t = 0;
            else t++, ans[14][1] -= t;
        }
        ans[14][0] = (ans[0][1] ? n : -1);
    }
    // 0110
    {
        vector<ii> sexo(2, pair(0LL, inf));
        sexo[0] = {1LL, -1LL};
        int x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= (s[i] == '1'); 
            ans[6][1] += sexo[x^1].first;
            ckmax(ans[6][0], i-sexo[x^1].second);
            sexo[x].first++;
            ckmin(sexo[x].second, i);
        }
    }
    // 1110
    {
        // 0 -> L
        // 11 -> L
        // 101 -> L
        // acho que todo o resto faz o W -> true
        // prova:
        // 1xx1 se nao eh W
        // 11x -> W
        // 10f -> 11 -> 0 -> W
        ans[7][1] = (n+1)*n/2;

        if (n >= 4) ans[7][0] = n;
        else if (n == 3 and s != "101") ans[7][0] = 3;
        else if (n >= 2 and s != "11") ans[7][0] = 2;
        else if (ans[0][1]) ans[7][0] = 1;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[7][1]--;
            if (i != n-1 and s[i] == '1' and s[i+1] == '1') ans[7][1]--;
            if (i < n-2 and s[i] == '1' and s[i+1] == '0' and s[i+2] == '1') ans[7][1]--;
        }
    }
    // diversao
    // 1101
    {
        // 0, 10 -> L
        // 110 -> L
        // 111111110 -> L supremo
        bool bad = (s.back() == '0');
        for (int i = 0; i < n-1; ++i) bad &= (s[i] == '1');
        if (bad) {
            if (n > 1) ans[11][0] = n-1;
        } else ans[11][0] = n;
        ans[11][1] = n*(n+1)/2;
        int lst = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[11][1] -= i - lst, lst = i;
        }
    }
    // 0100
    {
        // precisa terminar com 1
        // claim: faz o W se:
        // terminar com 1 e nao ser da forma 00000000011
        int lst = -inf, lst2 = -inf;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ckmax(ans[2][0], 1);
                if (lst != i-1) ckmax(ans[2][0], i+1), ans[2][1] += i + 1;
                else {
                    ans[2][1] += 1 + max(0LL, lst2 + 1);
                    if (lst2 >= 0) ckmax(ans[2][0], i+1);
                }
                lst2 = lst, lst = i; 
            }
        }
    }
    // 0101
    {
        for (int i = 0; i < n; ++i) if (s[i] == '1') ans[10][1] += i+1, ckmax(ans[10][0], i+1);
    }
    // 1100
    {
        if (n >= 3) ans[3][0] = n;
        else if (n == 2 and s[0] == '0') ans[3][0] = 2;
        else if (ans[0][1]) ans[3][0] = 1;
        ans[3][1] = (n+1)*n/2;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[3][1]--;
            // 1x
            if (i != n-1 and s[i] == '1') ans[3][1]--;
        }
    }
    // diversao de novo (agr ao contrario!
    // 1011
    {
        // 0 na direita eh W
        // 011101111 -> L supremo
        bool bad = (s[0] == '0');
        for (int i = 1; i < n; ++i) bad &= (s[i] == '1');
        if (bad) {
            if (n > 1) ans[13][0] = n-1;
        } else ans[13][0] = n;
        ans[13][1] = n*(n+1)/2;
        int lst = n;
        for (int i = n-1; ~i; --i) {
            if (s[i] == '0') ans[13][1] -= lst - i, lst = i;
        }
    }
    // 0010
    {
        // tem q comecar com 1
        // 1 W
        // 10 W
        // 100 W
        // 111X -> w (n >= 4)
        // 1100000000
        int lst = inf, lst2 = inf;
        for (int i = n-1; ~i; --i) {
            if (s[i] == '1') {
                ckmax(ans[4][0], 1);
                if (lst != i+1) ckmax(ans[4][0], n-i), ans[4][1] += n-i;
                else {
                    ans[4][1] += 1 + max(0LL, n - lst2);
                    if (lst2 < n) ckmax(ans[4][0], n - i);
                }
                lst2 = lst, lst = i; 
            }
        }
    }
    // 0011
    {
        // <=> comeca com 1
        ans[12][1] = (n+1)*n/2;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[12][1] -= n - i;
            else ckmax(ans[12][0], n - i);
        }
    }
    // 1010
    // termina com 0: top
    // 0, 01, 11 eh proibido e so
    {
        ans[5][1] = (n+1)*n/2;
        if (n >= 3) ans[5][0] = n;
        else if (n == 2 and s[1] == '0') ans[5][0] = 2;
        else if (ans[0][1]) ans[5][0] = 1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') ans[5][1]--;
            if (i and s[i] == '1') ans[5][1]--;
        }
    }
    auto ans2 = ans;
    for (int i = 0; i < 16; ++i) {
        int ni = 0;
        for (int j = 0; j < 4; ++j) {
            if (i >> j & 1) ni += (1 << (3 - j));
        }
        ans2[ni] = ans[i];
    }
    swap(ans, ans2);
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
