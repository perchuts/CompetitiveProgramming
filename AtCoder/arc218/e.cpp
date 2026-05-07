#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int __int128

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
struct BIT {
    vector<int> bit;
    int n;
    BIT() {};
    BIT(int n_) {
        n = n_;
        bit.resize(n+1);
    }
    int tot_sum = 0;
    void upd(int pos, int k) {
        tot_sum = (tot_sum + k * (n+1-pos)) % mod;
        while (pos <= n) bit[pos] += k, pos += pos & (-pos);
    }
    int query(int pos) {
        int ans = 0;
        while (pos) ans += bit[pos], pos -= pos & (-pos);
        return ans;
    }
};
struct solver {
    BIT inv_bit, ans_bit, local_bit;
    vector<int> lb, ab, p;
    int tot_inv;
    int C = 0;
    solver(int64_t n, vector<int64_t> p_) {

        inv_bit = BIT(n);
        ans_bit = BIT(n);
        local_bit = BIT(n);
        lb.resize(n+1), ab.resize(n+1);

        p.pb(0); for (auto x : p_) p.pb(x); 
        tot_inv = 0;

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

        for (int k = 0; k < n; ++k) C = (C + k*(n-k)) % mod;
    }

    void upd(int i) {
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
    }

    int query(int k) {
        int ik = ans_bit.query(k);
        //cout << "ans_bit: ";
        //for (int i = 1; i <= n; ++i) cout << ans_bit.query(i) << " ";
        //cout << endl;
        //cout << "local_bit: ";
        //for (int i = 1; i <= n; ++i) cout << local_bit.query(i) << " ";
        //cout << endl;
        int ik2 = local_bit.query(k);
        int n = sz(p)-1;
        int w = k*(n-k) - (ik-ik2) + (tot_inv - ik) + ik2;
        return w;
    }

    int get_all() {
        int res = (C + tot_inv * (sz(p)-1)) % mod;
        res = (res + 2 * (mod + local_bit.tot_sum - ans_bit.tot_sum)) % mod;
        return res;
    }
};
void solve() {
    int64_t n, q; cin >> n >> q;
    vector<int64_t> p(n); 
    for (auto& x : p) cin >> x;
    auto rev = p; reverse(all(rev));
    
    solver s(n, p), sr(n, rev);
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int inv_n = fexp(n, mod-2);
    while (q--) {
        int64_t x, k; cin >> x >> k;
        s.upd(x);
        sr.upd(n-x);
        int ans = 0;
        if (k % 2) {
            int L = (fexp(n-1, k)+1)*inv_n % mod;
            // let L = ((n-1)^m+1)/n
            // Q[i] = {P[i], ..., P[1], P[N], ..., P[i+1]}
            // Q[i] happens L times for 1 <= i < n, Q[n-1] happens L-1 times
            // if we treat P' as rev(P), we only deal with the case below!
            //for (int i = 0; i < n; ++i) ans = (ans + sr.query(i)) % mod;
            ans = sr.get_all();
            ans = ans * L % mod;
            ans = (ans+mod-sr.query(0)) % mod;
        } else {
            int L = (fexp(n-1, k)-1)*inv_n % mod;
            ans = s.get_all();
            ans = ans * L % mod;
            ans = (ans+s.query(0)) % mod;
            // let L = ((n-1)^m-1)/n
            // Q[i] = {P[i+1], ..., P[N], P[1], ..., P[i]}
            // Q[i] happens L times for 2 <= i <= n, Q[1] happens L+1 times
        }
        int64_t rans = ans;
        rans %= mod;
        rans = (rans + mod) % mod;
        cout << rans << endl;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
