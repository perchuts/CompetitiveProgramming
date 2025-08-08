#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

//6
//103530 57855 1885 4199 121771 1482
//0010010001 0000011100 0000011101 1100010100 0111000101 1111001001
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

bool brute(vector<int> A) { 
    sort(all(A));
    map<vector<int>, bool> state;
    auto go = [&state] (auto&& self, vector<int> a, int g = 0) -> bool {
        for (int i = 0; i < sz(a); ++i) {
            int gg = gcd(a[i], g);
            if (gg == 1) continue;
            auto b = a; b.erase(begin(b)+i);
            if (!self(self, b, gg)) return state[a] = true;
        }
        return state[a] = false;
    };
    return go(go, A);
}

vector<int> solve(vector<int> a){
	int mx = *max_element(all(a));
    vector<int> qnt(mx+1), f(mx+1), sqless(mx+1, 1), prime(mx+1);
    for (int i = 2; i <= mx; ++i) {
        if (sqless[i] == 1) {
            prime[i] = 1;
            for (int j = i; j <= mx; j += i) sqless[j] *= i;
        }
    }
    for (auto& x : a) x = sqless[x], qnt[x]++;
    for (int i = 1; i <= mx; ++i) {
        for (int j = i; j <= mx; j += i) f[i] += qnt[j]; 
    }
    vector<int> answer(mx+1, -1);
    for (int i = 1; i <= mx; ++i) {
        if (qnt[i] == 0 or sqless[i] != i) continue;
        vector<int> divs, primes;
        for (int k = 1; k * k <= i; ++k) {
            if (i % k == 0) {
                divs.pb(k);
                if (k * k != i) divs.pb(i/k);
            }
        }
        sort(all(divs));
        vector<int> ps;
        for (auto x : divs) if (prime[x]) ps.pb(x);
        int t = sz(divs), m = sz(ps);
        vector<int> sexo(t), gg(m);
        assert(__builtin_popcount(t) <= 1);
        for (int j = t-1; ~j; --j) {
            sexo[j] = f[divs[j]];
            for (int k = j + 1; k < t; ++k) if (divs[k] % divs[j] == 0) sexo[j] -= sexo[k];
        }
        sexo.back()--;
        for (auto& x : sexo) {
            if (x > 2) x = 2 - (x & 1);
        }
        // agr jogar o jogo
        //cout << "pra i = " << i << endl;
        //for (int j = 0; j < t; ++j) cout << "sexo[" << divs[j] << "] = " << sexo[j] << endl;
        vector<int> jogo, occ(m), atv(m, 1);
        int tudo = (1 << m) - 1;
        for (int j = 0; j < t; ++j) {
            if (sexo[j] == 0) continue;
            int mask = 0;
            for (int k = 0; k < m; ++k) {
                if (divs[j] % ps[k] == 0) mask += (1 << k), gg[k] += (1LL << (j-1));
            }
            tudo &= mask;
            if (!mask) continue;
            jogo.pb(mask); 
            if (sexo[j] == 2) jogo.pb(mask);
        }
        if (tudo != 0) {
            answer[i] = (t-1)&1;
            continue;
        }
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                if (k == j) continue;
                if (gg[k] == gg[j]) {
                    if (j < k) atv[j] = 0;
                } else if ((gg[j]&gg[k]) == gg[j]) atv[j] = 0;
            }
        }
        for (int j = 0; j < m; ++j) if (atv[j]) tudo += (1 << j);
        for (auto& x : jogo) {
            x &= tudo;
            for (int k = 0; k < m; ++k) if (x>>k&1) occ[k]++;
        }
        int even = 0, odd = 0, me = 0, mo = 0;
        for (int j = 0; j < m; ++j) {
            if (occ[j]&1) odd++, mo += (1 << j);
            else even++, me += (1 << j);
        }
        for (auto x : jogo) {
            if ((x & mo) == x) answer[i] = 0;
        }
        if (answer[i] != -1) continue;
        bool win = 1;
        for (int j = 0; j < sz(jogo); ++j) {
            bool found = 0;
            for (int k = 0; k < sz(jogo); ++k) {
                if (k == j) continue;
                found |= ((jogo[k]&jogo[j]&me) == (jogo[k]&jogo[j]));
            }
            win &= found;
        }
        if (win) {
            answer[i] = 1;
            continue;
        }
        if (min(even, odd) <= 1) {
            answer[i] = (even ? 1 : 0);
            continue;
        }
        if (even == 2) {
            answer[i] = 1;
            for (int j = 0; j < sz(jogo); ++j) {
                int x = jogo[j];
                bool achou = false;
                for (int k = 0; k < sz(jogo); ++k) {
                    if (j == k) continue;
                    int y = jogo[k];
                    if ((x&y&me) == 0) continue;
                    bool w = true;
                    for (int w = 0; w < sz(jogo); ++w) {
                        if (j == w or k == w) continue;
                        int z = jogo[w];
                        if ((x&y&z) != 0 and (x&y&z&me) == 0) { w = false; break; }
                    }
                    if (w) { achou = true; break; }
                }
                if (!achou) { answer[i] = 0; break; }
            }
            continue;
        } 
        //assert(even == odd and odd == 3);
        //cout << "jogo pra i = " << i << ": ";
        //for (auto x : jogo) cout << bitset<6>(x) << ' ';
        //cout << endl;

    }
    vector<int> ans;
    for (auto x : a) ans.pb(answer[x]);
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto ans = solve(a);
	for (auto x : ans) cout << x << endl;
    for (auto x : ans) cout << (x ? "Takahashi" : "Aoki") << endl;
#else
    int t = 1;
	vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    while (true) {
        int n = rnd(2, 10), g = 0;
        vector<int> a(n);
		vector<string> aa;
        for (auto& x : a) {
			string s;
			x = 1;
			for (int j = 0; j < sz(pr); ++j) {
				int k = rnd(0, 1);
                if (k == 1 and x * pr[j] > 2e5) k = 0;
				s += char('0' + k);
				if (k) x *= pr[j];
			}
			aa.pb(s);
			g = gcd(x, g);
		}
        if (g != 1) continue;
        cout << n << endl;
        sort(all(aa), [](string a1, string a2) {
            int c1 = 0, c2 = 0;
            for (int i = 0; i < sz(a1); ++i) c1 += a1[i] - '0', c2 += a2[i] - '0';
            return c1 < c2;
        });
        for (auto x : a) cout << x << ' ';
        cout << endl;
		for (auto x : aa) cout << x << ' ';
		cout << endl;
        auto my = solve(a);
		if (*min_element(all(my)) == -1) exit(0);
        //cout << (brute(a) ? "Alice" : "Bob") << endl;
		//if (brute(a) != brute(a2)) {
		//	cout << "morreu" << endl;
		//	exit(0); 
		//}
        t++;
    }
#endif
}
