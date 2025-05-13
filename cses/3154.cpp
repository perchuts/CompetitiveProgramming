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

typedef mod_int<(int)1e9+7> mint;
void solve(){
    int n, m; cin >> n >> m;
    m++;
    vector<vector<mint>> M(n, vector<mint>(m));
    for (auto& x : M) for (auto& y : x) cin >> y;
    vector<vector<mint>> MM(n, vector<mint>(m-1));
    vector<mint> BB(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m-1; ++j) MM[i][j] = M[i][j];
        BB[i] = MM[i][m-1];
    }
    vector<int> who(n); iota(all(who), 0);
    auto get = [&] (int i) {
        for (int j = 0; j < m-1; ++j) if (M[i][j] != 0) return j;
        return -1LL;
    };
    int pivots = 0;
    vector<int> pivot(n, -1);
    auto printar = [&] (vector<vector<mint>> a) {
        for (auto& x : a) {
            for (auto& y : x) cout << y << ' ';
            cout << endl;
        }
        cout << endl;
    };
    for (int i = 0; i < n; ++i) {
        pivot[i] = get(i);
        if (pivot[i] == -1) continue;
        pivots++;
        mint X = M[i][pivot[i]];
        //cout << "Step #" << i << ":" << endl;
        //printar(M);
        for (int j = 0; j < m; ++j) M[i][j] /= X;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            if (M[j][pivot[i]] != 0) {
                mint Y = M[j][pivot[i]];
                for (int k = 0; k < m; ++k) M[j][k] -= M[i][k] * Y;
            }
        }
        //cout << "end of Step #" << i << ":" << endl;
        //printar(M);
    }
    for (int i = 0; i < n; ++i) {
        if (pivot[i] == -1 and M[i][m-1] != 0) {
            cout << -1 << endl;
            exit(0);
        }
    }
    vector<mint> sol(m-1);
    for (int i = 0; i < n; ++i) if (pivot[i] != -1) sol[pivot[i]] = M[i][m-1];
    auto multi = [&] (vector<vector<mint>> A, vector<mint> x) {
        vector<mint> B(sz(A));
        for (int i = 0; i < sz(A); ++i) {
            for (int j = 0; j < sz(A[0]); ++j) B[i] += A[i][j] * x[j];
        }
        return B;
    };
    //auto result = multi(MM, sol);
    //for (auto x : result) cout << x << ' ';
    //cout << endl;
    for (auto x : sol) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
