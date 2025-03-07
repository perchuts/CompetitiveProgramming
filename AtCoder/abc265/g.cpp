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

vector<int> solve(int n, int q, vector<int> a, vector<array<int, 6>> queries){
    const int block = 330;
    vector<vector<int>> cnt(n/block+1, vector<int>(3)), sum_idx = cnt, block_ans(n/block+1, vector<int>(27)), state(27), tr(27, vector<int>(27));
    vector<int> cur_state(n/block+1, 21), is_simple(27);
    for (int i = 0; i < 27; ++i) {
        int cur = i;
        for (int j = 0; j < 3; ++j) state[i].pb(cur % 3), cur /= 3;
        is_simple[i] = ((state[i][0] ^ state[i][1] ^ state[i][2]) != 3);
    }
    for (int i = 0; i < 27; ++i) for (int j = 0; j < 27; ++j) {
        vector<int> nstate(3);
        for (int k = 0; k < 3; ++k) nstate[k] = state[j][state[i][k]];
        tr[i][j] = 9 * nstate[2] + 3 * nstate[1] + nstate[0];
    }
    for (int i = 0; i * block < n; ++i) {
        for (int j = i * block; j < min(n, i * block + block); ++j) cnt[i][a[j]]++, sum_idx[i][a[j]] += j;
        for (int st = 0; st < 27; ++st) {
            if (is_simple[st]) continue;
            vector<int> temp(3);
            for (int j = min(n, i * block + block) - 1; j >= i * block; --j) {
                for (int k = 0; k < state[st][a[j]]; ++k) block_ans[i][st] += temp[k];
                temp[state[st][a[j]]]++;
            }
        }
    }
    auto rebuild = [&] (int i, int l, int r, int upd) {
        int nstate = tr[cur_state[i]][upd];
        for (int j = i*block; j < min(n, i*block+block); ++j) {
            if (l <= j and j <= r) a[j] = state[nstate][a[j]];
            else a[j] = state[cur_state[i]][a[j]];
        }
        cur_state[i] = 21;
        for (int k = 0; k < 3; ++k) cnt[i][k] = sum_idx[i][k] = 0;
        for (int j = i * block; j < min(n, i * block + block); ++j) cnt[i][a[j]]++, sum_idx[i][a[j]] += j;
        for (int st = 0; st < 27; ++st) {
            if (is_simple[st]) continue;
            block_ans[i][st] = 0;
            vector<int> temp(3);
            for (int j = min(n, i * block + block) - 1; j >= i * block; --j) {
                for (int k = 0; k < state[st][a[j]]; ++k) block_ans[i][st] += temp[k];
                temp[state[st][a[j]]]++;
            }
        }
    };
    vector<int> resp;
    for (auto z : queries) {
        int op = z[0];
        if (op == 1) {
            int l = z[1]-1, r = z[2]-1;
            int ans = 0;
            vector<int> cur_cnt(3);
            int bl = l / block, br = r / block;
            if (br-bl <= 1) {
                for (int i = r; i >= l; --i) {
                    int act = state[cur_state[i/block]][a[i]];
                    for (int j = 0; j < act; ++j) ans += cur_cnt[j];
                    cur_cnt[act]++;
                }
            } else {
                for (int j = l; j < (l / block + 1) * block; ++j) {
                    int val = state[cur_state[l/block]][a[j]];
                    for (int k = val+1; k < 3; ++k) ans += cur_cnt[k];
                    cur_cnt[val]++;
                }
                for (int i = bl+1; i < br; ++i) {
                    int st = cur_state[i];
                    vector<int> cnt_here(3), sum_idx_here(3);
                    for (int j = 0; j < 3; ++j) cnt_here[state[st][j]] += cnt[i][j], sum_idx_here[state[st][j]] += sum_idx[i][j];
                    if (is_simple[st]) {
                        if (st % 13) {
                            int big_id = (cnt_here[2] ? sum_idx_here[2] : sum_idx_here[1]);
                            int big_cnt = (cnt_here[2] ? cnt_here[2] : cnt_here[1]);
                            int gauss = (2*((i+1)*block-1)-big_cnt+1)*big_cnt/2;
                            ans += gauss - big_id;
                        }
                    } else ans += block_ans[i][st];
                    ans += (cur_cnt[1]+cur_cnt[2]) * cnt_here[0] + cur_cnt[2] * cnt_here[1];
                    for (int j = 0; j < 3; ++j) cur_cnt[j] += cnt_here[j];
                }
                for (int j = r/block*block; j <= r; ++j) {
                    int val = state[cur_state[r/block]][a[j]];
                    for (int k = val+1; k < 3; ++k) ans += cur_cnt[k];
                    cur_cnt[val]++;
                }
            }
            resp.pb(ans);
        } else {
            int l = z[1]-1, r = z[2]-1, aa = z[3], b = z[4], c = z[5];
            int st = aa + 3 * b + 9 * c;
            for (int i = l/block+1; i < r/block; ++i) cur_state[i] = tr[cur_state[i]][st];
            rebuild(l/block, l, min(l/block*block+block-1, r), st);
            if (l/block != r/block) rebuild(r/block, r/block*block, r, st);
        }
    }
    return resp;
}

vector<int> brute(int n, int q, vector<int> a, vector<array<int, 6>> qu) {
    vector<int> resp;
    for (auto op : qu) {
        op[1]--, op[2]--;
        int l = op[1], r = op[2];
        vector<int> change = {op[3], op[4], op[5]};
        if (op[0] == 1) {
            vector<int> cnt(3);
            int ans = 0;
            for (int i = l; i <= r; ++i) {
                for (int j = a[i]+1; j < 3; ++j) ans += cnt[j];
                cnt[a[i]]++;
            }
            resp.pb(ans);
        } else {
            for (int i = l; i <= r; ++i) a[i] = change[a[i]];
        }
    }
    return resp;
}

int32_t main(){_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<array<int, 6>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0];
        if (queries[i][0] == 1) cin >> queries[i][1] >> queries[i][2];
        else cin >> queries[i][1] >> queries[i][2] >> queries[i][3] >> queries[i][4] >> queries[i][5];
    }
    auto ans = solve(n, q, a, queries);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = 1000, q = 1000;
        vector<int> a(n);
        vector<array<int, 6>> qu(q);
        for (auto& x : a) x = rnd(0, 2);
        for (int i = 0; i < q; ++i) {
            qu[i][0] = rnd(1, 2);
            qu[i][1] = rnd(1, n), qu[i][2] = rnd(qu[i][1], n);
            if (qu[i][0] == 2) qu[i][3] = rnd(0, 2), qu[i][4] = rnd(0, 2), qu[i][5] = rnd(0, 2);
        }
        auto my = solve(n, q, a, qu);
        auto resp = brute(n, q, a, qu);
        if (my != resp) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto op : qu) {
                if (op[0] == 1) cout << 1 << ' ' << op[1] << ' ' << op[2] << endl;
                else for (int i = 0; i <= 5; ++i) cout << op[i] << ' ';
                cout << endl;
            }
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : resp) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
