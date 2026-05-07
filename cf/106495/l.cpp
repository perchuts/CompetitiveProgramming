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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int q, vector<int> p, vector<ii> qq) {
    struct BIT {
        vector<int> bit;
        int n;
        BIT(int n_) {
            n = n_;
            bit.resize(n+1);
        }
        void upd(int pos, int k) {
            while (pos <= n) bit[pos] += k, pos += pos & (-pos);
        }
        int query(int pos) {
            int ans = 0;
            while (pos) ans += bit[pos], pos -= pos & (-pos);
            return ans;
        }
    };
    BIT inv_bit(n), ans_bit(n), local_bit(n);
    vector<int> lb(n+1), ab(n+1);
    vector<int> ans;
    int tot_inv = 0;
    for (int i = n; i; --i) {
        int eu = inv_bit.query(p[i]);
        ab[i] = eu;
        inv_bit.upd(p[i], 1);
        ans_bit.upd(i, eu);
        tot_inv += eu;
    }
    for (int i = 0; i <= n; ++i) inv_bit.bit[i] = 0;
    for (int i = 1; i <= n; ++i) {
        int eu = i-1-inv_bit.query(p[i]);
        inv_bit.upd(p[i], 1);
        lb[i] = eu;
        local_bit.upd(i, eu);
    }
    //cout << "ans_bit: ";
    //for (int i = 1; i <= n; ++i) cout << ans_bit.query(i) << " ";
    //cout << endl;
    //cout << "local_bit: ";
    //for (int i = 1; i <= n; ++i) cout << local_bit.query(i) << " ";
    //cout << endl;
    for (auto [t, xx] : qq) {
        if (t == 1) {
            int i = xx;
            if (p[i] < p[i+1]) {
                ans_bit.upd(i, ab[i+1]-ab[i]+1), ans_bit.upd(i+1, ab[i]-ab[i+1]);
                local_bit.upd(i, lb[i+1]-lb[i]), local_bit.upd(i+1, lb[i]-lb[i+1]+1);
                tot_inv++;
            } else { 
                ans_bit.upd(i, ab[i+1]-ab[i]), ans_bit.upd(i+1, ab[i]-ab[i+1]-1);
                local_bit.upd(i, lb[i+1]-lb[i]-1), local_bit.upd(i+1, lb[i]-lb[i+1]);
                tot_inv--;
            }
            swap(ab[i], ab[i+1]);
            swap(lb[i], lb[i+1]);
            if (p[i] < p[i+1]) {
                ab[i]++, lb[i+1]++;
                //ans_bit.upd(i, 1), local_bit.upd(i+1, 1), tot_inv++;
            }
            else {
                ab[i+1]--, lb[i]--;
                //ans_bit.upd(i+1, -1), local_bit.upd(i, -1), tot_inv--;
            }
            swap(p[i], p[i+1]);
        } else {
            int k = xx;
            int ik = ans_bit.query(k);
            //cout << "ans_bit: ";
            //for (int i = 1; i <= n; ++i) cout << ans_bit.query(i) << " ";
            //cout << endl;
            //cout << "local_bit: ";
            //for (int i = 1; i <= n; ++i) cout << local_bit.query(i) << " ";
            //cout << endl;
            int ik2 = local_bit.query(k);
            int w = k*(n-k) - (ik-ik2) + (tot_inv - ik) + ik2;
            ans.pb(w);

        }
    }
    return ans;
}

vector<int> brute(int n, int q, vector<int> p, vector<ii> qq) {
    vector<int> ans;
    for (auto [t, x] : qq) {
        if (t == 1) {
            swap(p[x], p[x+1]);
        } else {
            vector<int> t;
            for (int i = x+1; i <= n; ++i) t.pb(p[i]);
            for (int i = 1; i <= x; ++i) t.pb(p[i]);
            int ti = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j < n; ++j) {
                    ti += (t[i] > t[j]);
                }
            }
            ans.pb(ti);
        }
    }
    return ans;
}


int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n >> q;
    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i) cin >> p[i];
    vector<ii> qq(q);
    for (auto& [x, y] : qq) cin >> x >> y;
    auto ans = solve(n, q, p, qq);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 50);
        vector<int> p(n+1); iota(begin(p)+1, end(p), 1); shuffle(begin(p)+1, end(p), rng);
        int q = rnd(1, 20);
        vector<ii> qq(q);
        for (auto& [x, y] : qq) {
            x = rnd(1, 2);
            y = rnd(1, n-1);
        }
        auto my = solve(n, q, p, qq);
        auto ans = brute(n, q, p, qq);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << q << endl;
            for (int i = 1; i <= n; ++i) cout << p[i] << " ";
            cout << endl;
            for (auto [x, y] : qq) cout << x << " " << y << endl;
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
