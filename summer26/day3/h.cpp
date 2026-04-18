#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define gato

using namespace std;

using ll = long long;

int helper[10005];

const int inf = 1e18 + 50;

vector<int> solve(int n, vector<vector<int>> v) {
    struct stack_do_sexo {
        vector<vector<int>> dp;
        vector<int> id_seqs;
        int tamanho = 0;
        void pop() {
            assert(!dp.empty()); 
            dp.pop_back();
            id_seqs.pop_back();
            tamanho--;
        }
        stack_do_sexo() {}
        bool empty() {
            return tamanho == 0;
        }
        void push(int id, vector<vector<int>>& v, vector<vector<int>>& li, vector<vector<int>>& ri, vector<vector<int>>& ord, bool L_sup = 0, vector<int> dp_L = {}, int id_bicho = -1) {
            int m = v[id].size();
            vector<int> ndp(m, -1);
            int last_id;
            vector<int> dp_last;
            if (dp.empty() and L_sup == 0) {
                for (int i = 0; i < m; ++i) ndp[i] = 0;
                dp.pb(ndp);
                id_seqs.pb(id);
                tamanho++;
                return;
            } else if (L_sup == 1) {
                dp_last = dp_L;
                last_id = id_bicho;
            } else {
                last_id = id_seqs.back();
                dp_last = dp[tamanho-1];
            }
            id_seqs.pb(id);
            for (int i = 0; i < m; ++i) helper[i] = inf;
            for (int i = 0; i < v[last_id].size(); ++i) {
                if (dp_last[i] == -1) continue;
                int need = (dp_last[i] / ri[last_id][i]) + 1;
                int l = 0, r = m-1, opt = m;
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    if (li[id][ord[id][md]] >= need) opt = md, r = md-1;
                    else l = md+1;
                }
                helper[opt] = min(helper[opt], ri[last_id][i]);
            }
            for (int i = 0; i < m; ++i) {
                if (i) helper[i] = min(helper[i], helper[i-1]);
                if (helper[i] < inf) ndp[ord[id][i]] = helper[i] * li[id][ord[id][i]];
            }
            dp.pb(ndp);
            tamanho++;
        };
    };
    vector<vector<int>> li(n), ri(n), ord(n);
    for (int i = 0; i < n; ++i) {
        int l = v[i].size();
        li[i].resize(l), ri[i].resize(l);
        for (int j = 0; j < l; ++j) {
            li[i][j] = v[i][j];
            ri[i][j] = v[i][(j+1)%l];
        }
        ord[i].resize(l);
        iota(begin(ord[i]), end(ord[i]), 0);
        sort(begin(ord[i]), end(ord[i]), [&] (int x, int y) { return li[i][x] < li[i][y]; });
    }
    stack_do_sexo sexo_1, sexo_2;
    vector<int> dp_fim;
    int id_fim_2 = -1;
    auto q_push = [&] (int idx) { 
        if (sexo_1.empty() and id_fim_2 != -1) {
            sexo_1.push(idx, v, li, ri, ord, 1, dp_fim, id_fim_2); 
        } else {
            sexo_1.push(idx, v, li, ri, ord); 
        }
    };
    auto q_pop = [&] () {
        if (sexo_2.empty()) {
            id_fim_2 = sexo_1.id_seqs.back();
            dp_fim = sexo_1.dp.back();
            while (!sexo_1.empty()) {
                int idx = sexo_1.id_seqs.back();
                sexo_1.pop();
                sexo_2.push(idx, v, li, ri, ord);
            }
            return;
        }
        sexo_2.pop();
    };
    vector<int> ans;
    for (int i = 0; i < n; ++i) q_push(i);
    for (int i = 0; i < n; ++i) {
        bool ok = false;
        for (auto x : sexo_1.dp.back()) {
            if (x != -1) ok = 1;
        }
        if (ok) ans.push_back(i);
        q_pop();
        q_push(i);
    }
    return ans;
}

mt19937 rng(69);

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
vector<int> brute(int n, vector<vector<int>> v) {
    vector<int> ans;
    for (int start = 0; start < n; ++start) {
        vector<int> dp(v[start].size(), 0);
        for (int i = 1; i < n; ++i) {
            int id = (start + i) % n;
            int id_lst = (start + n - 1 + i) % n;
            vector<int> ndp(v[id].size(), -1);
            for (int j = 0; j < dp.size(); ++j) {
                if (dp[j] == -1) continue;
                for (int k = 0; k < ndp.size(); ++k) {
                    int prox = v[id_lst][(j-1+dp.size())%dp.size()] * v[id][k];
                    if (dp[j] < prox) {
                        if (ndp[k] == -1) ndp[k] = prox;
                        else ndp[k] = min(ndp[k], prox);
                    }
                }
            }
            swap(dp, ndp);
        }
        bool ok = 0;
        for (auto x : dp) if (x != -1) ok = 1;
        if (ok) ans.pb(start);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> v(n);
        for (int i = 0; i < n; ++i) {
            int l; cin >> l;
            v[i].resize(l);
            for (auto& x : v[i]) cin >> x;
        }
		auto ans = solve(n, v);
		cout << ans.size() << endl;
		for (auto x : ans) cout << x + 1 << " ";
		cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 3);
        vector<vector<int>> v(n);
        for (int i = 0; i < n; ++i) {
            int l = rnd(3, 3);
            v[i].resize(l);
            for (auto& x : v[i]) x = rnd(1, 5);
        }
        auto my = solve(n, v);
        auto ans = brute(n, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) {
                cout << v[i].size() << " ";
                for (auto x : v[i]) cout << x << " ";
                cout << endl;
            }
            cout << "solve: ";
            cout << endl << my.size() << endl;
            for (auto x : my) cout << x + 1 << " ";
            cout << endl;
            cout << "brute: ";
            cout << endl << ans.size() << endl;
            for (auto x : ans) cout << x + 1 << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif

}
