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

vector<int> solve(int n, int q, vector<int> a, vector<ii> qu) {
    vector<int> seta(n+1, n);
    vector<int> ord(n), pos(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
    for (int i = 0; i < n; ++i) pos[ord[i]] = i;
    struct node {
        array<int, 5> esq, dir;
        bool ok1, ok2;
        int mn, mx;
        int tam;
        node() {
            for (int i = 0; i < 5; ++i) esq[i] = dir[i] = -1;
            ok1 = ok2 = 0;
            mn = inf, mx = -1;
            tam = 0;
            ok1 = ok2 = 0;
        };
    } nulo;
    auto print = [&] (node x) {
        cout << "tam: " << x.tam << endl;
        cout << "esq: ";
        for (int i = 0; i < min(5LL, x.tam); ++i) cout << x.esq[i] << " ";
        cout << endl;
        cout << "dir: ";
        for (int i = 0; i < min(5LL, x.tam); ++i) cout << x.dir[i] << " ";
        cout << endl;
        cout << "mn: " << x.mn << " mx: " << x.mx << endl;
        cout << "ok1: " << x.ok1 << " ok2: " << x.ok2 << endl;
    };
    vector<node> seg(4*n); vector<int> val(20);
    auto merge = [&] (node a, node b) {
        node c;
        c.tam = a.tam + b.tam;
        for (int i = 0; i < min(5LL, a.tam); ++i) c.esq[i] = a.esq[i];
        for (int i = 0; i < max(0LL, 5 - a.tam); ++i) c.esq[a.tam+i] = b.esq[i];
        for (int i = 0; i < min(5LL, b.tam); ++i) c.dir[i] = b.dir[i];
        for (int i = 0; i < max(0LL, 5 - b.tam); ++i) c.dir[b.tam+i] = a.dir[i];
		//cout << "esq:" << endl << endl;
		//print(a);
		//cout << "dir: " << endl << endl;
		//print(b);
        c.mn = (a.ok1 ? a.mn : (b.ok1 ? b.mn + a.tam : a.mn));
        c.mx = (b.ok1 ? b.mx + a.tam : a.mx);
        c.ok1 |= a.ok1, c.ok1 |= b.ok1;
        c.ok2 |= (a.ok2), c.ok2 |= (b.ok2), c.ok2 |= (a.ok1 and b.ok1);
		//cout << "aqui: " << c.ok2 << endl;
        if (a.tam >= 1 and b.tam >= 2) {
            if (a.dir[0] + b.esq[0] > b.esq[1]) {
                c.ok1 = 1, ckmin(c.mn, a.tam-1), ckmax(c.mx, a.tam-1);
                if (b.mx > 1 or a.mn < a.tam-3) c.ok2 = 1;
            }
        }
		//cout << "aqui2: " << c.ok2 << endl;
        if (a.tam >= 2 and b.tam >= 1) {
            if (a.dir[0] + a.dir[1] > b.esq[0]) {
                c.ok1 = 1, ckmin(c.mn, a.tam-2), ckmax(c.mx, a.tam-2);
                if (b.mx > 0 or a.mn < a.tam-4) c.ok2 = 1;
            }
        }
		//cout << "aqui3: " << c.ok2 << endl;
        // agr tem os trem suspeito
        int h = 0;
        for (int i = 0; i < min(5LL, a.tam); ++i) val[h++] = a.dir[min(5LL, a.tam)-1-i];
        for (int i = 0; i < min(5LL, b.tam); ++i) val[h++] = b.esq[i];
        for (int i = 0; i < h - 5 and !c.ok2; ++i) {
            // choose two from 1,2,3,4,5
            // 1,2 -> checked
            // 1,3
            if (val[i+0]+val[i+1] > val[i+3] and val[i+2]+val[i+4] > val[i+5]) c.ok2 = 1;
            // 1,4
            if (val[i+0]+val[i+1] > val[i+4] and val[i+2]+val[i+3] > val[i+5]) c.ok2 = 1;
            // 1,5
            if (val[i+0]+val[i+1] > val[i+5] and val[i+2]+val[i+3] > val[i+4]) c.ok2 = 1;
            // 2,3
            if (val[i+0]+val[i+2] > val[i+3] and val[i+1]+val[i+4] > val[i+5]) c.ok2 = 1;
            // 2,4
            if (val[i+0]+val[i+2] > val[i+4] and val[i+1]+val[i+3] > val[i+5]) c.ok2 = 1;
            // 2,5
            if (val[i+0]+val[i+2] > val[i+5] and val[i+1]+val[i+3] > val[i+4]) c.ok2 = 1;
            // 3,4
            if (val[i+0]+val[i+3] > val[i+4] and val[i+1]+val[i+2] > val[i+5]) c.ok2 = 1;
            // 3,5
            if (val[i+0]+val[i+3] > val[i+5] and val[i+1]+val[i+2] > val[i+4]) c.ok2 = 1;
            // 4,5
            if (val[i+0]+val[i+4] > val[i+5] and val[i+1]+val[i+2] > val[i+3]) c.ok2 = 1;
        }
        c.ok1 |= c.ok2;
		//cout << "result: " << endl;
		//print(c);
        return c;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            assert(k != 0);
            if (k == -1) {
                seg[i].esq[0] = seg[i].dir[0] = -1;
                seg[i].tam = 0;
            } else {
                seg[i].esq[0] = seg[i].dir[0] = k;
                seg[i].tam = 1;
            }
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    for (int i = n-1; ~i; --i) {
        upd(upd, 1, 0, n-1, pos[i], a[i]);
        if (seg[1].ok2) {
            int ptr = min(n-1, seta[i+1]);
            while (seg[1].ok2) upd(upd, 1, 0, n-1, pos[ptr], -1), ptr--;
            ptr++;
            upd(upd, 1, 0, n-1, pos[ptr], a[ptr]);
            seta[i] = ptr;
        } else seta[i] = n;
    }
    //for (auto x : seta) cout << x << " ";
    //cout << endl;
    vector<int> ans;
    for (auto [l, r] : qu) ans.pb(seta[l] <= r);
    return ans;
}
vector<int> brute(int n, int q, vector<int> a, vector<ii> qu) {
    vector<int> ans;
    for (auto [l, r] : qu) {
        vector<int> b;
        for (int i = l; i <= r; ++i) b.pb(a[i]);
        sort(all(b));
        int t = r-l+1;
        vector <int> pr(t+1), sf(t+1);
        for (int i = 3; i <= t; ++i) {
            pr[i] = pr[i-1] + (b[i-3] + b[i-2] > b[i-1]);
        }
        for (int i = t-2; i >= 1; --i) {
            sf[i] = sf[i+1] + (b[i-1] + b[i] > b[i+1]);
        }
        bool ok = 0;
        for (int i = 1; i < t; ++i) ok |= (pr[i] > 0 and sf[i+1] > 0);
        if (ok) { ans.pb(1); continue; }
        auto val = b;
        for (int i = 0; i < t-5; ++i) {
            if (val[i+0]+val[i+1] > val[i+3] and val[i+2]+val[i+4] > val[i+5]) ok = 1;
            // 1,4
            if (val[i+0]+val[i+1] > val[i+4] and val[i+2]+val[i+3] > val[i+5]) ok = 1;
            // 1,5
            if (val[i+0]+val[i+1] > val[i+5] and val[i+2]+val[i+3] > val[i+4]) ok = 1;
            // 2,3
            if (val[i+0]+val[i+2] > val[i+3] and val[i+1]+val[i+4] > val[i+5]) ok = 1;
            // 2,4
            if (val[i+0]+val[i+2] > val[i+4] and val[i+1]+val[i+3] > val[i+5]) ok = 1;
            // 2,5
            if (val[i+0]+val[i+2] > val[i+5] and val[i+1]+val[i+3] > val[i+4]) ok = 1;
            // 3,4
            if (val[i+0]+val[i+3] > val[i+4] and val[i+1]+val[i+2] > val[i+5]) ok = 1;
            // 3,5
            if (val[i+0]+val[i+3] > val[i+5] and val[i+1]+val[i+2] > val[i+4]) ok = 1;
            // 4,5
            if (val[i+0]+val[i+4] > val[i+5] and val[i+1]+val[i+2] > val[i+3]) ok = 1;
        }
        ans.pb(ok);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
    auto ans = solve(n, q, a, qu);
    for (auto x : ans) cout << (x?"Yes":"No") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(6, 30), q = 30;
        vector<int> a(n);
        vector<ii> qu(q);
        for (auto& x : a) x = rnd(1, 1e9);
        for (auto& [l, r] : qu) l = rnd(0, n-6), r = rnd(l+5, n-1);
        auto my = solve(n, q, a, qu);
        auto ans = brute(n, q, a, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << q << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            for (auto [l, r] : qu) cout << l+1 << " " << r+1 << endl;
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
