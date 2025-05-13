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
// Li-Chao Tree - Lazy
//
// Sendo N = MA-MI:
// insert({a, b}) minimiza tudo com ax+b - O(log N)
// insert({a, b}, l, r) minimiza com ax+b no range [l, r] - O(log^2 N)
// shift({a, b}) soma ax+b em tudo - O(1)
// shift({a, b}, l, r) soma ax+b no range [l, r] - O(log^2 N)
// query(x) retorna o valor da posicao x - O(log N)
//
// No inicio eh tudo LINF, se inserir {0, 0} fica tudo 0
//
// O(n log N) de memoria ; O(n) de memoria se nao usar as operacoes de range
const int LINF = 1e18;
template<int MI = int(-1e9), int MA = int(1e9)> struct lichao {
	struct line {
		ll a, b;
		ll la, lb; // lazy
		array<int, 2> ch;
		line(ll a_ = 0, ll b_ = LINF) :
			a(a_), b(b_), la(0), lb(0), ch({-1, -1}) {}
		ll operator ()(ll x) { return a*x + b; }
	};
	vector<line> ln;

	int ch(int p, int d) {
		if (ln[p].ch[d] == -1) {
			ln[p].ch[d] = ln.size();
			ln.emplace_back();
		}
		return ln[p].ch[d];
	}
	lichao() { ln.emplace_back(); }

	void prop(int p, int l, int r) {
		if (ln[p].la == 0 and ln[p].lb == 0) return;
		ln[p].a += ln[p].la, ln[p].b += ln[p].lb;
		if (l != r) {
			int pl = ch(p, 0), pr = ch(p, 1);
			ln[pl].la += ln[p].la, ln[pl].lb += ln[p].lb;
			ln[pr].la += ln[p].la, ln[pr].lb += ln[p].lb;
		}
		ln[p].la = ln[p].lb = 0;
	}

	ll query(int x, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		ll ret = ln[p](x);
		if (ln[p].ch[0] == -1 and ln[p].ch[1] == -1) return ret;
		int m = l + (r-l)/2;
		if (x <= m) return min(ret, query(x, ch(p, 0), l, m));
		return min(ret, query(x, ch(p, 1), m+1, r));
	}

	void push(line s, int p, int l, int r) {
		prop(p, l, r);
		int m = l + (r-l)/2;
		bool L = s(l) < ln[p](l);
		bool M = s(m) < ln[p](m);
		bool R = s(r) < ln[p](r);
		if (M) swap(ln[p].a, s.a), swap(ln[p].b, s.b);
		if (s.b == LINF) return;
		if (L != M) push(s, ch(p, 0), l, m);
		else if (R != M) push(s, ch(p, 1), m+1, r);
	}
	void insert(line s, int a=MI, int b=MA, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		if (a <= l and r <= b) return push(s, p, l, r);
		if (b < l or r < a) return;
		int m = l + (r-l)/2;
		insert(s, a, b, ch(p, 0), l, m);
		insert(s, a, b, ch(p, 1), m+1, r);
	}

	void shift(line s, int a=MI, int b=MA, int p=0, int l=MI, int r=MA) {
		prop(p, l, r);
		int m = l + (r-l)/2;
		if (a <= l and r <= b) {
			ln[p].la += s.a, ln[p].lb += s.b;
			return;
		}
		if (b < l or r < a) return;
		if (ln[p].b != LINF) {
			push(ln[p], ch(p, 0), l, m);
			push(ln[p], ch(p, 1), m+1, r);
			ln[p].a = 0, ln[p].b = LINF;
		}
		shift(s, a, b, ch(p, 0), l, m);
		shift(s, a, b, ch(p, 1), m+1, r);
	}
};
void solve(){
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    stack<ii> st;
    st.push({-1, 0});
    vector<int> li(n), ri(n);
    for (int i = 0; i < n; ++i) {
        while (st.top().second >= a[i]) st.pop();
        li[i] = st.top().first+1;
        st.push({i, a[i]});
    }
    while (sz(st) != 1) st.pop();
    st.top().first = n;
    for (int i = n-1; ~i; --i) { 
        while (st.top().second >= a[i]) st.pop();
        ri[i] = st.top().first-1;
        st.push({i, a[i]});
    }
    lichao lixao;
    // agora pra cada cara, quero calcular a funcaozinha que acontece
    for (int i = 0; i < n; ++i) {
        // quando o inicio comecar a ser maior do que li[i], entao vou perder a[i] a cada iteracao
        // enquanto o final nao for maior que ri[i], entao vou ganhar a[i] a cada iteracao
        int ini = max(0LL, i-k+1);
        int B = min(k, (i-li[i]+1)) * a[i]; 
        if (i < k) B += (min(k-1, ri[i])-i) * a[i];
        vector<ii> events;
        // vou comecar a ganhar isso, mas uma hora vou comecar a parar de ganhar
        events.pb({ini, a[i]}), events.pb({max(ini, ri[i]-k+1), -a[i]});
        events.pb({max(li[i], ini), -a[i]});
        events.pb({i+k, 0});
        sort(all(events));
        int A = 0;
        for (int l = 0, r = 0; events[l].first < i+k; l = r) {
            while (events[r].first == events[l].first) A += events[r++].second;
            int lx = events[l].first, rx = events[r].first;
            int tB = B - lx * A;
            lixao.insert({-A, -tB}, lx, rx-1);
            B = tB + A * events[r].first;
        }
    }
    for (int i = 0; i <= n-k; ++i) cout << -lixao.query(i) << ' ';
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
