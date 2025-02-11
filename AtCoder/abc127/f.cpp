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
// SlopeTrick
//
// Armazena uma estrutura convexa piecewise linear
// Permite adicionar slopes sem peso e realizar query de minimo
// Comentarios acima das funcoes para explicar o que cada uma faz

template<typename T> struct SlopeTrick {
	T inf = numeric_limits<T>::max() / 3;
	T min_f;
	priority_queue<T, vector<T>, less<>> L;
	priority_queue<T, vector<T>, greater<>> R;
	T add_l, add_r;

	T top_R() {
		if (R.empty()) return inf;
		else return R.top() + add_r;
	}

	T pop_R() {
		T val = top_R();
		if (R.size()) R.pop();
		return val;
	}

	T top_L() {
		if (L.empty()) return -inf;
		else return L.top() + add_l;
	}

	T pop_L() {
		T val = top_L();
		if (L.size()) L.pop();
		return val;
	}

	size_t size() {
		return L.size() + R.size();
	}

	SlopeTrick() : min_f(0), add_l(0), add_r(0) {};

	// return {min f(x), lx, rx} 
	// Em que [lx, rx] eh o intervalo que atinge o minimo
	array<T, 3> query() {
		return {min_f, top_L(), top_R()};
	}

	// f(x) += a
	void add_all(T a) {
		min_f += a;
	}

	// add \_
	// f(x) += max(a - x, 0)
	void add_a_minus_x(T a) {
		min_f += max(T(0), a - top_R());
		R.push(a - add_r);
		L.push(pop_R() - add_l);
	}

	// add _/
	// f(x) += max(x - a, 0)
	void add_x_minus_a(T a) {
		min_f += max(T(0), top_L() - a);
		L.push(a - add_l);
		R.push(pop_L() - add_r);
	}

	// add \/
	// f(x) += abs(x - a)
	void add_abs(T a) {
		add_a_minus_x(a);
		add_x_minus_a(a);
	}

	// \/ -> \_
	// f_{new} (x) = min f(y) (y <= x)
	void clear_right() {
		while (R.size()) R.pop();
	}

	// \/ -> _/
	// f_{new} (x) = min f(y) (y >= x)
	void clear_left() {
		while (L.size()) L.pop();
	}

	// \/ -> \_/
	// f_{new} (x) = min f(y) (x-b <= y <= x-a)
	void shift(T a, T b) {
		assert(a <= b);
		add_l += a;
		add_r += b;
	}

	// \/. -> .\/
	// f_{new} (x) = f(x - a)
	void shift(T a) {
		shift(a, a);
	}

	// Retorna f(x) 
	// O(size)
	T get(T x) {
		auto L2 = L;
		auto R2 = R;
		T ret = min_f;
		while (L.size()) {
			ret += max(T(0), pop_L() - x);
		}
		while (R.size()) {
			ret += max(T(0), x - pop_R());
		}
		L = L2, R = R2;
		return ret;
	}

	// O(min(size, st.size))
	void merge(SlopeTrick &st) {
		if (st.size() > size()) {
			swap(*this, st);
		}
		while (st.R.size()) {
			add_x_minus_a(st.pop_R());
		}
		while (st.L.size()) {
			add_a_minus_x(st.pop_L());
		}
		min_f += st.min_f;
	}
};
void solve(){
    int q; cin >> q;
    SlopeTrick<int> st;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int a, b; cin >> a >> b;
            st.add_all(b);
            st.add_abs(a);
        } else {
            auto [a, b, c] = st.query();
            cout << b << ' ' << a << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
