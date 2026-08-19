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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
	int n; cin >> n;
    vector<int> color(n);
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        color[i] = (c == 'B');
    }
    vector<vector<int>> val(2, vector<int>(n));
    for (auto& x : val) for (auto& y : x) cin >> y;

    int block = sqrt(n);

    vector calc(n / block + 1, vector(2, vector(2, vector(4, 0LL))));
    vector sum_mod(n / block + 1, vector(4, 0LL));
    vector qt(n / block + 1, vector(2, 0LL));

    vector<int> temp(2), cur_calc(4), cur_sum_mod(4);

    auto recalc = [&] (int bl) {
        int l = block * bl, r = min(l + block, n) - 1;
        for (int q0 = 0; q0 < 2; ++q0) {
            for (int q1 = 0; q1 < 2; ++q1) {
                temp[0] = q0, temp[1] = q1;
                auto& v = calc[bl][q0][q1];
                v[0] = v[1] = v[2] = v[3] = 0;
                for (int i = l; i <= r; ++i) {
                    v[(i-l)&3] += val[temp[color[i]]][i];
                    temp[color[i]] ^= 1;
                }
            }
        }
    };

    for (int i = 0; i < n; ++i) {
        sum_mod[i/block][(i%block)&3] += val[0][i] + val[1][i];
        qt[i/block][color[i]] ^= 1;
    }

    for (int i = 0; i * block < n; ++i) recalc(i);

	int q; cin >> q;

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; cin >> i; --i;
            qt[i/block][color[i]] ^= 1, qt[i/block][color[i]^1] ^= 1;
            color[i] ^= 1;
            recalc(i/block);
        }
        if (op == 2 or op == 3) {
            int i, k; cin >> i >> k; --i;
            sum_mod[i/block][(i%block)&3] += k - val[op-2][i];
            val[op-2][i] = k;
            recalc(i/block);
        }
        if (op == 4) {
            int l, r, t; cin >> l >> r >> t; --l, --r, t = (t + 1) & 1;
            if (r-l < block) {
                temp[0] = temp[1] = 0;
                int ans = 0;
                for (int i = l; i <= r; ++i) {
                    int m = (i-l)&3;
                    if (m == 0 or m == 3 or t == 0) ans += val[temp[color[i]]][i];
                    else ans += val[temp[color[i]]^1][i];
                    temp[color[i]] ^= 1;
                }
                cout << ans << endl;
                continue;
            }
            temp[0] = temp[1] = 0;
            for (int i = 0; i < 4; ++i) cur_calc[i] = cur_sum_mod[i] = 0;
            int xwq = (l + block - 1) / block * block;
            for (int i = l; i < xwq; ++i) {
                int m = (i-l)&3;
                cur_sum_mod[m] += val[0][i] + val[1][i];
                cur_calc[m] += val[temp[color[i]]][i];
                temp[color[i]] ^= 1;
            }
            for (int bl = xwq/block; bl != r / block; ++bl) {
                int shift = (bl*block - l) & 3;
                for (int i = 0; i < 4; ++i) cur_calc[(i+shift)&3] += calc[bl][temp[0]][temp[1]][i], cur_sum_mod[(i+shift)&3] += sum_mod[bl][i];
                temp[0] ^= qt[bl][0], temp[1] ^= qt[bl][1];
            }
            for (int i = r - (r % block); i <= r; ++i) {
                int m = (i-l)&3;
                cur_sum_mod[m] += val[0][i] + val[1][i];
                cur_calc[m] += val[temp[color[i]]][i];
                temp[color[i]] ^= 1;
            }
            int ans = cur_calc[0] + cur_calc[1] + cur_calc[2] + cur_calc[3];
            if (t) ans += cur_sum_mod[1] + cur_sum_mod[2] - 2 * (cur_calc[1] + cur_calc[2]);
            cout << ans << endl;
        }
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int T = 1;
    while (true) {
        int n = rnd(1, 50);
        vector<int> v(n);
        for (auto& x : v) x = rnd(0, 1);
        vector<int> sexo;
        //for (int t = 0; t < 3; ++t) { 
        //    int qt0 = 0, qt1 = 0;
        //    for (auto& x : v) {
        //        if (x == 0) qt0++;
        //        else qt1++;
        //        if (x == 0) x = (qt0 % 2) ^ 1;
        //        else x = (qt1 % 2) ^ 1;
        //    }
        //    if (t == 0) sexo = v;
        //}
        //assert(sexo == v);
        for (int t = 0; t < 10; ++t) { 
            int qt0 = 0, qt1 = 0;
            for (auto& x : v) {
                if (x == 0) qt0++;
                else qt1++;
                if (x == 0) x = (qt0 % 2) ^ 1;
                else x = (qt1 % 2) ^ 1;
            }
            for (auto x : v) cout << x;
            cout << endl;
        }
        T++;
        cout << "OK " << T-1 << endl;
    }
#endif
}
