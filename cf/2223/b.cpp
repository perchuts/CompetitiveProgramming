#include <bits/stdc++.h>
using namespace std;
// Order Statistic Set
//
// Funciona do C++11 pra cima

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
// para declarar:
// ord_set<int> s;
// coisas do set normal funcionam:
// for (auto i : s) cout << i << endl;
// cout << s.size() << endl;
// k-esimo maior elemento O(log|s|):
// k=0: menor elemento
// cout << *s.find_by_order(k) << endl;
// quantos sao menores do que k O(log|s|):
// cout << s.order_of_key(k) << endl;

// Para fazer um multiset, tem que
// usar ord_set<pair<int, int>> com o
// segundo parametro sendo algo para diferenciar
// os ementos iguais.
// s.order_of_key({k, -INF}) vai retornar o
// numero de elementos < k
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
// Aritmetica Modular
//
// O mod tem q ser primo

template<int p> struct mod_int {
	ll expo(ll b, ll e) {
		ll ret = 1;
		while (e) {
			if (e % 2) ret = ret * b % p;
			e /= 2, b = b * b % p;
		}
		return ret;
	}
	ll inv(ll b) { return expo(b, p-2); }

	using m = mod_int;
	int v;
	mod_int() : v(0) {}
	mod_int(ll v_) {
		if (v_ >= p or v_ <= -p) v_ %= p;
		if (v_ < 0) v_ += p;
		v = v_;
	}
	m& operator +=(const m& a) {
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator -=(const m& a) {
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator *=(const m& a) {
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator /=(const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -(){ return m(-v); }
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		// possivel otimizacao:
		// cuidado com 0^0
		// v = expo(v, e%(p-1)); 
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend istream& operator >>(istream& in, m& a) {
		ll val; in >> val;
		a = m(val);
		return in;
	}
	friend ostream& operator <<(ostream& out, m a) {
		return out << a.v;
	}
	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }
};

typedef mod_int<(int)mod> mint;
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto& x : b) cin >> x;
    for (auto& x : a) cin >> x;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    vector<iii> z;

    mint ans = 0;
    mint inv_b = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            inv_b += (b[i] > b[j]);
            z.pb({b[i], b[j], 0});
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) z.pb({a[i], a[j], 1});
        }
    }
    sort(all(z), [&] (iii x1, iii x2) {
        auto [n1, d1, c1] = x1;
        auto [n2, d2, c2] = x2;
        // n1/d1 < n2/d2
        return n1*d2 > n2*d1;
    });
    int cnt = 0;
    for (int l = 0, r = 0; l != sz(z); l = r) {
        int aq = 0;
        while (r != sz(z) and get<0>(z[l]) * get<1>(z[r]) == get<1>(z[l]) * get<0>(z[r])) aq += get<2>(z[r++]);
        ans += aq * cnt;
        cnt += (r-l-aq);
    }
    //ans -= inv_b * n;
    ans = ans * (mint(1)/n) * (mint(1)/(n-1));
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
