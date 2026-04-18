#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

int solve(int n, int m, int k, int x, vector<int> a) {
    sort(all(a));
    vector ncr(k+1, vector(k+1, 0LL)), pot(m+1, vector(k+1, 1LL));
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= i; ++j) {
            if (j == 0 or j == i) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
        }
    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= k; ++j) {
            pot[i][j] = i * pot[i][j-1] % mod;
        }
    }
    int ans = 0, tira = 0;
    for (auto y : a) ans = (ans + y*pot[m][k]) % mod;
    for (int val = 1; val <= m; ++val) {
        int pos = 0;
        ans = (ans + val * k * pot[m][k-1]) % mod;
        int pl = 0, pr = n;
        while (pl < n and a[pl] < val) pl++;
        while (pr and val < a[pr-1]) pr--;
        if (pl <= x-1 and x-1 <= pr) pos = x-1;
        else if (pr < x-1) pos = pr;
        else pos = pl;
		int dist = abs(x-1-pos);
		// aqui eh pra EU me matar
		// eu preciso ter surgido ao menos uma vez no momento de minha morte
		if (pos < x-1) {
			for (int rounds = dist; rounds <= k; ++rounds) {
				// de quantas maneiras eu posso construir as operacoes de forma que o val caia no vacuo no round rounds
				int ways2 = (pot[val][dist] - pot[val-1][dist] + mod) * pot[m-val][rounds-dist] % mod;
				int ways = ncr[rounds-1][dist-1] * ways2 % mod;
				tira = (tira + ways) % mod;
			}
		} else if (pos >= x) {
			for (int rounds = dist+1; rounds <= k; ++rounds) {
				int ways = ncr[rounds-1][dist] * pot[m-val][dist+1] % mod * pot[val][rounds-dist-1] % mod;
				ways = ways * pot[m][k-rounds] % mod * val;
				tira = (tira + ways) % mod;
			}
		} else {
			for (int rounds = 1; rounds <= k; ++rounds) {
				tira = (tira + (m-val) * pot[val][rounds-1] % mod * pot[m][k-rounds] % mod * val) % mod;
			}
		}
    }
    // falta considerar as vezes em que os elementos originais do array morrem!
    cout << "tirada parcial = " << tira << endl;
    for (int i = 0; i < n; ++i) {
        int dist = abs(x-1-i), val = a[i];
        //cout << "a[i] = " << val << endl;
        if (i < x-1) {
            for (int rounds = dist; rounds <= k; ++rounds) {
                int ways = ncr[rounds-1][dist-1] * pot[val-1][dist] % mod * pot[m-val+1][rounds-dist] % mod;
                ways = ways * pot[m][k-rounds] % mod * val;
                tira = (tira + ways) % mod;
            }
        } else if (i >= x) {
            for (int rounds = dist+1; rounds <= k; ++rounds) {
                int ways = ncr[rounds-1][dist] * pot[m-val][dist+1] % mod * pot[val][rounds-dist-1] % mod;
                ways = ways * pot[m][k-rounds] % mod * val;
                tira = (tira + ways) % mod;
            }
        } else {
            for (int rounds = 1; rounds <= k; ++rounds) {
                tira = (tira + (m-val) * pot[val][rounds-1] % mod * pot[m][k-rounds] % mod * val) % mod;
            }
        }
    }
    cout << "resposta ta tirando: " << tira << endl;
    ans = (ans + mod - tira) % mod;
    cout << "minha resposta: ";
    cout << ans << endl;
	return ans;
}

int brute(int n, int m, int k, int x, vector<int> a) {
    int tira = 0,  s = 0;
    auto go = [&] (auto&& self, vector<int> aa, int it) -> void {
        if (it == k){
            for (auto y : aa) s = (s + y) % mod;
            return;
        }
        for (int i = 1; i <= m; ++i) {
            auto b = aa;
            b.pb(i);
            sort(all(b));
            tira += b[x-1];
            b.erase(begin(b)+x-1);
            self(self, b, it+1);
        }
    };
    go(go, a, 0);
    //cout << "brute tirou: " << tira << endl;
    //cout << "brute somou: " << s << endl;
	return s;
}

int32_t main() {_
#ifndef gato
    int n, m, k, x; cin >> n >> m >> k >> x;
    vector<int> a(n);
    for (auto& y : a) cin >> y;
    cout << solve(n, m, k, x, a) << endl;
#else
    int t = 1;
    while (true) {
		int n = rnd(1, 3), m = rnd(1, 4), k = rnd(1, 3), x = rnd(1, n+1);
		vector<int> a(n);
		for (auto& y : a) y = rnd(1, m);
        int my = solve(n, m, k, x, a), ans = brute(n, m, k, x, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
			cout << n << " " << m << " " << k << " " << x << endl;
			for (auto y : a) cout << y << " ";
			cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
