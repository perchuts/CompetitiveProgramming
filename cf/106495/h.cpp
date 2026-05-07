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
template<typename T> vector<int> manacher(const T& s) {
	int l = 0, r = -1, n = s.size();
	vector<int> d1(n), d2(n);
	for (int i = 0; i < n; i++) {
		int k = i > r ? 1 : min(d1[l+r-i], r-i);
		while (i+k < n && i-k >= 0 && s[i+k] == s[i-k]) k++;
		d1[i] = k--;
		if (i+k > r) l = i-k, r = i+k;
	}
	l = 0, r = -1;
	for (int i = 0; i < n; i++) {
		int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1); k++;
		while (i+k <= n && i-k >= 0 && s[i+k-1] == s[i-k]) k++;
		d2[i] = --k;
		if (i+k-1 > r) l = i-k, r = i+k-1;
	}
	vector<int> ret(2*n-1);
	for (int i = 0; i < n; i++) ret[2*i] = 2*d1[i]-1;
	for (int i = 0; i < n-1; i++) ret[2*i+1] = 2*d2[i+1];
	return ret;
}

void solve() {
    string s, t; cin >> s >> t;
    int ans = 0;
    int n = sz(s);
    vector<int> S(n);
    for (int i = 0; i < n; ++i) S[i] = 26 * (t[i]-'a') + s[i];
    auto man = manacher(S);
    vector<int> qtd_c(n+1), qtd_t(n+1);
    // qtd[i] = quantos palindromos terminam na posicao i
    // contabilizar impares
    for (int i = 0; i < n; ++i) {
        qtd_c[i-man[2*i]/2]++;
        qtd_c[i+1]--;

        qtd_t[i]++;
        qtd_t[i+man[2*i]/2+1]--;
    }
    // contabilizar pares
    for (int i = 0; i < n-1; ++i) {
        if (man[2*i+1] == 0) continue;
        qtd_c[i-man[2*i+1]/2+1]++;
        qtd_c[i+1]--;

        qtd_t[i+1]++;
        qtd_t[i+man[2*i+1]/2+1]--;
    }
    for (int i = 1; i < n; ++i) qtd_c[i] += qtd_c[i-1], qtd_t[i] += qtd_t[i-1];
    for (int i = 0; i < n and s[i] == t[n-1-i] and t[i] == s[n-1-i]; ++i) {
        ans++;
        if (i != n-1) ans += qtd_c[i+1] + qtd_t[n-2-i];
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
