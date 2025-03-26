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
// Manacher
//
// manacher recebe um vetor de T e retorna o vetor com tamanho dos palindromos
// ret[2*i] = tamanho do maior palindromo centrado em i
// ret[2*i+1] = tamanho maior palindromo centrado em i e i+1
//
// Complexidades:
// manacher - O(n)
// palindrome - <O(n), O(1)>
// pal_end - O(n)

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

// verifica se a string s[i..j] eh palindromo
template<typename T> struct palindrome {
	vector<int> man;

	palindrome(const T& s) : man(manacher(s)) {}
	bool query(int i, int j) {
		return man[i+j] >= j-i+1;
	}
};

// tamanho do maior palindromo que termina em cada posicao
template<typename T> vector<int> pal_end(const T& s) {
	vector<int> ret(s.size());
	palindrome<T> p(s);
	ret[0] = 1;
	for (int i = 1; i < s.size(); i++) {
		ret[i] = min(ret[i-1]+2, i+1);
		while (!p.query(i-ret[i]+1, i)) ret[i]--;
	}
	return ret;
}
void solve(){
    string s; cin >> s; 
    auto v = pal_end<string>(s);
    for (int i = sz(s) - v.back() - 1; ~i; --i) s += s[i];
    cout << s << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
