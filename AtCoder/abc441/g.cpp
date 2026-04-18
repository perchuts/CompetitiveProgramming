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
vector<int> brute(int n, int q, vector<array<int, 4>> qq) {
    vector<int> v(n), f(n);
    vector<int> resp;
    for (auto arr : qq) {
        int op = arr[0];
        int l = arr[1];
        int r = arr[2];
        int x = arr[3];
        if (op == 1) {
            for (int i = l; i <= r; ++i) {
                if (f[i] == 0) v[i] += x;
            }
        } else if (op == 2) { 
            for (int i = l; i <= r; ++i) {
                v[i] = 0;
                f[i] ^= 1;
            }
        } else {
            int ans = 0;
            for (int i = l; i <= r; ++i) ckmax(ans, v[i]);
            resp.pb(ans);
        }
    }
    return resp;
}

vector<int> solve(int n, int q, vector<array<int, 4>> qq) {
    vector<int> v(n), state_block(n), state(n), morto(n);
    vector<array<int, 2>> mx_block(n), sv(n), qt(n);
    int block = 330;
	vector<int> resp;
	auto reset_block = [&] (int pos) {
		mx_block[pos][0] = mx_block[pos][1] = 0;
		qt[pos][0] = qt[pos][1] = 0;
		for (int i = pos * block; i < min(n, pos*block + block); ++i) {
			if (morto[pos]) v[i] = 0;
			v[i] += sv[pos][state[i]];
			ckmax(mx_block[pos][state[i]], v[i]);
			qt[pos][state[i]]++;
		}
		sv[pos][0] = sv[pos][1] = morto[pos] = 0;
	};
	for (int i = 0; i * block < n; ++i) {
		reset_block(i);
	}
    for (auto arr : qq) {
        int op = arr[0];
        int l = arr[1];
        int r = arr[2];
        int x = arr[3];
        if (op == 1) {
            int ini_block = l/block, fim_block = r/block;
            if (ini_block == fim_block) {
                reset_block(ini_block);
                for (int i = l; i <= r; ++i) {
                    if ((state[i] ^ state_block[ini_block]) == 0) v[i] += x;
                    ckmax(mx_block[ini_block][state[i]], v[i]);
                }
            } else {
                reset_block(ini_block);
                reset_block(fim_block);
                for (int i = l; i < (ini_block+1) * block; ++i) {
                    if ((state[i] ^ state_block[ini_block]) == 0) v[i] += x;
                    ckmax(mx_block[ini_block][state[i]], v[i]);
                }
                for (int i = fim_block*block; i <= r; ++i) {
                    if ((state[i] ^ state_block[fim_block]) == 0) v[i] += x;
                    ckmax(mx_block[fim_block][state[i]], v[i]);
                }
                for (int i = ini_block + 1; i < fim_block; ++i) sv[i][state_block[i]] += x;
            }

        } else if (op == 2) { 
            int ini_block = l/block, fim_block = r/block;
            if (ini_block == fim_block) {
                reset_block(ini_block);
                for (int i = l; i <= r; ++i) v[i] = 0, state[i] ^= 1;
                reset_block(ini_block);
            } else {
                reset_block(ini_block);
                for (int i = l; i < (ini_block+1)*block; ++i) v[i] = 0, state[i] ^= 1;
                reset_block(ini_block);
                reset_block(fim_block);
                for (int i = fim_block*block; i <= r; ++i) v[i] = 0, state[i] ^= 1;
                reset_block(fim_block);
                for (int i = ini_block + 1; i < fim_block; ++i) {
                    sv[i][0] = sv[i][1] = mx_block[i][0] = mx_block[i][1] = 0;
                    state_block[i] ^= 1;
                    morto[i] = 1;
                }
            }
        } else {
            int ini_block = l/block, fim_block = r/block, ans = 0;
            if (ini_block == fim_block) {
                reset_block(ini_block);
                for (int i = l; i <= r; ++i) ckmax(ans, v[i]);
            } else {
                reset_block(ini_block);
                reset_block(fim_block);
                for (int i = l; i < (ini_block+1)*block; ++i) ckmax(ans, v[i]);
                for (int i = fim_block*block; i <= r; ++i) ckmax(ans, v[i]);
                for (int i = ini_block + 1; i < fim_block; ++i) {
                    if (qt[i][1]) ckmax(ans, mx_block[i][1] + sv[i][1]);
                    if (qt[i][0]) ckmax(ans, mx_block[i][0] + sv[i][0]);
                }
            }
            resp.pb(ans);
        }
    }
    return resp;
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<array<int, 4>> qq(q);
    for (int i = 0; i < q; ++i) {
        int op, l, r; cin >> op >> l >> r;
        --l, --r;
        int x;
        if (op == 1) cin >> x;
        qq[i][0] = op;
        qq[i][1] = l;
        qq[i][2] = r;
        qq[i][3] = x;
    }
    auto ans = solve(n, q, qq);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5), q = rnd(1, 4);
        vector<array<int, 4>> qq(q);
        for (int i = 0; i < q; ++i) {
            int op = rnd(1, 3);
            int l = rnd(0, n-1), r = rnd(l, n-1), x;
            if (op == 1) x = rnd(1, 3);
            qq[i][0] = op;
            qq[i][1] = l;
            qq[i][2] = r;
            qq[i][3] = x;
        }
        auto my = solve(n, q, qq);
        auto ans = brute(n, q, qq);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << q << endl;
            for (int i = 0; i < q; ++i) {
                cout << qq[i][0] << " " << qq[i][1]+1 << " " << qq[i][2]+1 << " ";
                if (qq[i][0] == 1) cout << qq[i][3];
                cout << endl;
            }
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
