#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// SegTree
//
// Recursiva com Lazy Propagation
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
// Pode usar a seguinte funcao para indexar os nohs:
// f(l, r) = (l+r)|(l!=r), usando 2N de memoria
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))
const int MAX = 2e5 + 10;

namespace seg {
ll seg[4*MAX], lazy[4*MAX];
int n;

void build(int p=1, int l=0, int r=n-1) {
    lazy[p] = -1;
    if (l == r) {
        seg[p] = n;
        return;
    }
    int m = (l+r)/2;
    build(2*p, l, m), build(2*p+1, m+1, r);
    seg[p] = n;
    return;
}
void builD(int n2) {
    n = n2;
    build();
}
void prop(int p, int l, int r) {
    if (lazy[p] == -1) return;
    seg[p] = lazy[p];
    if (l != r) lazy[2*p] = lazy[2*p+1] = lazy[p];
    lazy[p] = -1;
}
ll query(int a, int b, int p=1, int l=0, int r=n-1) {
    prop(p, l, r);
    if (a <= l and r <= b) return seg[p];
    if (b < l or r < a) return 0;
    int m = (l+r)/2;
    return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
}
ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
    prop(p, l, r);
    if (a <= l and r <= b) {
        lazy[p] = x;
        prop(p, l, r);
        return seg[p];
    }
    if (b < l or r < a) return seg[p];
    int m = (l+r)/2;
    update(a, b, x, 2*p, l, m), update(a, b, x, 2*p+1, m+1, r);
    return seg[p];
}
};

vector<int> solve(int n, vector<int> a, vector<int> p) {
    // coloca o cara, recomputa a resposta
    vector<int> ptr_morte(n+1), bit(n+1);
    ptr_morte[n] = -1;
    auto insert = [&] (int i, int k) {
        ++i;
        while (i <= n) bit[i] += k, i += i & (-i);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    auto Query = [&] (int l, int r) {
        ++l, ++r;
        return query(r) - query(l-1);
    };
    reverse(all(p));
    seg::builD(n);
    int cur_ans = 0;
    vector<int> ans, contribui(n+1);
    for (auto novo : p) {
        insert(novo, a[novo]);
        int i = novo, x = seg::query(i, i);
		//for (int j = 0; j < n; ++j) cout << seg::query(j, j) << " ";
		//cout << endl;
		//for (int j = 0; j < n; ++j) cout << contribui[j] << " ";
		//cout << endl;
		//cout << "cur_ans = " << cur_ans << endl;
		//cout << "add " << novo << endl;
        while (x != -1) {
            int other = 0, forca = a[i];
            if (x < i) other = Query(x, i-1);
            else if (x != n) other = a[x], forca = Query(i, x-1);
			//cout << "x = " << x << " forca = " << forca << " other = " << other << endl;
            if ((i < x and forca >= other) or (i > x and forca > other)) {
                cur_ans -= contribui[x];
				//cout << "ganhei" << ' ' << cur_ans << endl;
                if (x < i) cur_ans++, contribui[x] = 1;
                else contribui[x] = 0;
                int prox = ptr_morte[x];
                ptr_morte[x] = i;
                x = prox;
            } else {
				//cout << "perdi" << " " << cur_ans << endl;
				ptr_morte[i] = x;
                if (x > i) {
					cur_ans++, contribui[i] = 1;
					break;
				}
				else i = x, x = ptr_morte[i], cur_ans -= contribui[i], contribui[i] = 0;
            }
        }
        if (x == -1) ptr_morte[i] = -1, seg::update(i, n-1, i);
        else seg::update(i, x-1, i);
        ans.pb(cur_ans);
    }
    reverse(all(ans));
    return ans;
}

vector<int> brute(int n, vector<int> a, vector<int> p) {
    vector<int> ans, mark(n);
    for (auto c : p) {
        int cur = 0, z = 0;
        for (int j = 0; j < sz(a); ++j) {
            if (mark[j]) continue;
            if (a[j] > cur) z++, cur = a[j];
            else cur += a[j];
        }
        ans.pb(z-1);
        mark[c] = 1;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n), p(n);
        for (auto& x : a) cin >> x;
        for (auto& x : p) cin >> x, --x;
        auto ans = solve(n, a, p);
        for (auto x : ans) cout << x << " ";
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 10);
        vector<int> a(n), p(n);
        iota(all(p), 0);
        shuffle(all(p), rng);
        for (auto& x : a) x = rnd(1, 10000);
        auto my = solve(n, a, p);
        auto ans = brute(n, a, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            for (auto x : p) cout << x+1 << " ";
            cout << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
