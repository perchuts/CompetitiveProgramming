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

pair<int, int> solve(int x, int y) {
    int p, q, opt = 1e18;
    iii rec;
    // ateh onde eu sigo o bicho
    vector<int> bx(32), by(32);
    for (int i = 0; i <= 31; ++i) bx[i] = (x >> i & 1), by[i] = (y >> i & 1);
    int lst_ok = -1;
    for (int i = 31; ~i; --i) {
        if (bx[i] == by[i] and bx[i]) { lst_ok = i; break; }
    }
    int cur_p = 0;
    int pp, qq;
    for (int i = 31; ~i; --i) {
        cur_p += (bx[i] << i);
        int cur_q = 0;
        for (int j = 31; ~j; --j) {
            if (max(i, j) <= lst_ok) break;
            cur_q += (by[j] << j);
            // p <= x, q <= y
            if ((i == 0 or bx[i-1] == 1) and (j == 0 or by[j-1] == 1)) {
                // x + y - p - q
                int k = max(i, j) - 1, subt = 0;
                if (k >= 0) {
                    subt = (1LL << k) - 1; 
                    int no = (cur_p | cur_q) & subt;
                    subt -= no;
                }
                if (ckmin(opt, x+y-cur_p-cur_q-subt)) rec = {i, j, 0};
            }
            if ((i == 0 or bx[i-1] == 0) and (j == 0 or by[j-1] == 0)) {
                int op = cur_p, oq = cur_q;
                if (i != 0) cur_p += (1LL << (i-1));
                if (j != 0) cur_q += (1LL << (j-1));
                if (cur_p & cur_q) {}
                else if (ckmin(opt, cur_p+cur_q-x-y)) rec = {i, j, 1}, pp = cur_p, qq = cur_q;
                cur_p = op, cur_q = oq;
            }
            if ((i == 0 or bx[i-1] == 0) and (j == 0 or by[j-1] == 1)) {
                if (i != 0 and by[i-1] == 1 and j <= i-1) {}
                else {
                    int oq = cur_q, op = cur_p;
                    if (i != 0) cur_p += (1LL << (i-1));
                    if (j != 0) {
                        int k = (1LL << (j-1)) - 1;
                        int tira = cur_p & k;
                        k ^= tira;
                        cur_q += k;
                    }
                    if (ckmin(opt, cur_p-x+y-cur_q)) rec = {i, j, 2}, pp = cur_p, qq = cur_q;
                    // da posicao j-2 ate a posicao zero, eu quero ser um!!
                    // o que pode me impedir isso
                    cur_q = oq, cur_p = op;
                }
            }
            if ((i == 0 or bx[i-1] == 1) and (j == 0 or by[j-1] == 0)) {
                if (j != 0 and bx[j-1] == 1 and i <= j-1) {}
                else {
                    int oq = cur_q, op = cur_p;
                    if (j != 0) cur_q += (1LL << (j-1));
                    if (i != 0) {
                        int k = (1LL << (i-1)) - 1;
                        int tira = cur_q & k;
                        k ^= tira;
                        cur_p += k;
                    }
                    if (ckmin(opt, x-cur_p+cur_q-y)) rec = {i, j, 3}, pp = cur_p, qq = cur_q;
                    cur_q = oq, cur_p = op;
                }
            }
        }
    }
    auto [i, j, type] = rec;
    p = q = 0;
    if (type == 0) {
        for (int k = 31; ~k; --k) {
            if (k >= i) p += (bx[k] << k);
            if (k >= j) q += (by[k] << k);

            if ((k < i-1 and ((q >> k & 1) == 0))) p += (1LL << k);
            if (k < j-1 and ((p >> k & 1) == 0)) q += (1LL << k);
        }
        assert(abs(x-p)+abs(y-q) == opt);
        return {p, q};
    } else {
        assert(abs(pp-x)+abs(qq-y) == opt);
        return {pp, qq};
    }
}

pair<int, int> brute(int x, int y) {
    int opt = 1e18;
    int p, q;
    for (int i = 0; i <= 1000; ++i) {
        for (int j = 0; j <= 1000; ++j) {
            if ((i & j)) continue;
            if (ckmin(opt, abs(x-i)+abs(y-j))) p = i, q = j;
        }
    }
    return {p, q};
}
int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        int x, y; cin >> x >> y;
        auto [p, q] = solve(x, y);
        cout << p << " " << q << endl;
    }
#else
    int t = 1;
    while (true) {
        int x = rnd(0, 100), y = rnd(0, 100);
        auto [p, q] = solve(x, y);
        auto [ap, aq] = brute(x, y);
        if (abs(p-x)+abs(q-y) != abs(ap-x)+abs(aq-y)) {
            cout << "Wrong answer on test " << t << endl;
            cout << x << " " << y << endl;
            cout << "Solve: " << p << ' ' << q << endl;
            cout << "Brute: " << ap << ' ' << aq << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
