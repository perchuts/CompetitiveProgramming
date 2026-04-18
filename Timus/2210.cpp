#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

struct CHT {
    int it;
    vector<ll> a, b;
    CHT():it(0){}
    ll eval(int i, ll x){
        return a[i]*x + b[i];
    }
    bool useless(){
        int sz = a.size();
        int r = sz-1, m = sz-2, l = sz-3;
        return (b[l] - b[r])*(a[m] - a[l]) <
        (b[l] - b[m])*(a[r] - a[l]);
    }
    void add(ll A, ll B){
        a.push_back(A); b.push_back(B);
        while (!a.empty()){
            if ((a.size() < 3) || !useless()) break;
            a.erase(a.end() - 2);
            b.erase(b.end() - 2);
        }
        it = min(it, int(a.size()) - 1);
    }
    ll get(ll x){
        while (it+1 < a.size()){
            if (eval(it+1, x) > eval(it, x)) it++;
            else break;
        }
        return eval(it, x);
    }
};
vector<int> brute(int n, int q, vector<int> a, vector<int> b, vector<int> qu) {
    const int lim_i = 2000;
    const int lim_m = 2000;
    vector<vector<int>> dp(lim_m, vector<int>(lim_i, 1e9));
    vector<vector<ii>> pai(lim_m, vector<ii>(lim_i, {-1, -1}));
    queue<ii> que;
    dp[0][0] = 0;
    que.push({0, 0});
    int A = a[0], B = b[0];
    for (int i = 1; i < n; ++i) {
        if (B < b[i] or (B == b[i] and A > a[i])) A = a[i], B = b[i];
    }
    while (!que.empty()) {
        auto [money, income] = que.front(); que.pop();
        int d = dp[money][income];
        for (int i = 0; i < n; ++i) {
            if (money >= a[i]) {
                int m2 = money - a[i] + income, i2 = income + b[i];
                if (m2 < lim_m and i2 < lim_i and dp[m2][i2] == 1e9) {
					pai[m2][i2] = {money, income};
                    dp[m2][i2] = 1 + d;
                    que.push({m2, i2});
                }
            }
        }
        int m2 = money + 1 + income, i2 = income;
        if (m2 < lim_m and i2 < lim_i and dp[m2][i2] == 1e9) {
			pai[m2][i2] = {money, income};
			dp[m2][i2] = 1 + d;
            que.push({m2, i2});
        }
    }
    vector<int> opt_c(lim_i, -1e15);
    const int lim_d = 206;
    vector<int> fim(lim_d);
    for (int i = 1; i < lim_d; ++i) {
        fim[i] = 1 + fim[i-1];
        for (int j = 0; j < n; ++j) ckmax(fim[i], fim[i-1] + i * b[j] - a[j]);
    }
    CHT cht;
    // slopes tem que ir aumentando
    vector<ii> retas;
    for (int i = A; i < 310; ++i) {
        for (int j = A; j < 410; ++j) {
            int d = dp[i][j];
            if (d == 1e9) continue;
            assert(d <= 780);
            // f(x) = i + fim[lim_d-1] + 1  + j * (x-d) + B * (x+lim_d+1-d) * (x-lim_d-d) / 2
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + B * [x * (x-lim_d-d)/2 + (lim_d+1-d)*x/2 + (lim_d+1-d)*(-lim_d-d)/2]
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + (B/2) * [x * (x-2d+1) - (lim_d+1-d)*(lim_d+d)]
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + (B/2) * (x^2-2xd+x) - (B/2) * (lim_d+1-d)*(lim_d+d)
            // f(x) = (B/2) x^2 + (j-dB+B/2) x + (i + fim[lim_d-1] + 1 - j*d - (B/2) * (lim_d+1-d)*(lim_d+d)
            // fixado o j, podemos unicamente determinar a funcao otima!
            retas.pb({j-B*d, i + fim[lim_d-1] + 1 - j*d - (lim_d+1-d)*(lim_d+d)*B/2});
        }
    }
    sort(all(retas));
    for (int l = 0, r = 0; l < sz(retas); l = r) {
        while (r != sz(retas) and retas[r].first == retas[l].first) r++;
        cht.add(retas[r-1].first, retas[r-1].second);
    }
    // ate um certo momento, vou precisar acumular minhas riquezas pra comprar o proximo item
    // depois desse momento, vou ter certa quantidade de dinheiro e de income.
    // a partir desse ponto, nao me importo mais com quanto dinheiro tenho no bolso, mas apenas com quais maquinas vou obter.
    // [income][money]
    // eh super complexudo
    vector<int> ans(q);
    const int lim_q = 1000;
    vector<vector<int>> fim2(lim_q, vector<int>(101));
    // 1e5*100 = 1e7
    for (int i = 1; i < lim_q; ++i) {
        for (int j = 1; j <= 100; ++j) {
            fim2[i][j] = 1 + fim2[i-1][j];
            for (int k = 0; k < n; ++k) {
                if (a[k] <= j) ckmax(fim2[i][j], fim2[i-1][j] + i*b[k] - a[k]);
            }
        }
    }
    vector<int> ord(q); iota(all(ord), 0), sort(all(ord), [&] (int x, int y) { return qu[x] < qu[y]; });
    vector<int> pre_ans(lim_q);
    for (int k = 1; k < lim_q; ++k) {
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < min(lim_i, i+1); ++j) {
                int d = dp[i][j];
                if (d > k) continue;
                if (d == k) ckmax(pre_ans[k], i);
                else {
                    ckmax(pre_ans[k], i + 1 + j * (k-d) + fim2[k-d-1][min(100LL, j)]);
                }
            }
        }
        for (int i = 100; i < lim_m; ++i) {
            for (int j = 100; j < lim_i; ++j) {
                int d = dp[i][j];
                if (d > k) continue;
                if (d == k) ckmax(pre_ans[k], i);
                else {
                    ckmax(pre_ans[k], i + 1 + j * (k-d) + fim2[k-d-1][min(100LL, j)]);
                }
            }
        }
    }
    for (auto i : ord) {
        if (qu[i] < lim_q) {
            ans[i] = pre_ans[qu[i]];
        } else {
            ans[i] = cht.get(qu[i]) + qu[i] * (qu[i]+1) * B / 2;
        }
    }
    return ans;

}

vector<int> solve(int n, int q, vector<int> a, vector<int> b, vector<int> qu) {
    // dp[available money][income] -> minimum number of days to reach this
    // after we reach a large income 200), it does not matter anymore
    // it does not make sense to have more than 100 of money before turning to 
    const int lim_i = 310;
    const int lim_m = 410;
    vector<vector<int>> dp(lim_m, vector<int>(lim_i, 1e9));
    queue<ii> que;
    dp[0][0] = 0;
    que.push({0, 0});
    int A = a[0], B = b[0];
    for (int i = 1; i < n; ++i) {
        if (B < b[i] or (B == b[i] and A > a[i])) A = a[i], B = b[i];
    }
    while (!que.empty()) {
        auto [money, income] = que.front(); que.pop();
        int d = dp[money][income];
        for (int i = 0; i < n; ++i) {
            if (money >= a[i]) {
                int m2 = money - a[i] + income, i2 = income + b[i];
                if (m2 < lim_m and i2 < lim_i and dp[m2][i2] == 1e9) {
                    dp[m2][i2] = 1 + d;
                    que.push({m2, i2});
                }
            }
        }
        int m2 = money + 1 + income, i2 = income;
        if (m2 < lim_m and i2 < lim_i and dp[m2][i2] == 1e9) {
            dp[m2][i2] = 1 + d;
            que.push({m2, i2});
        }
    }
    vector<int> opt_c(lim_i, -1e15);
    const int lim_d = 206;
    vector<int> fim(lim_d);
    for (int i = 1; i < lim_d; ++i) {
        fim[i] = 1 + fim[i-1];
        for (int j = 0; j < n; ++j) ckmax(fim[i], fim[i-1] + i * b[j] - a[j]);
    }
    CHT cht;
    // slopes tem que ir aumentando
    vector<ii> retas;
    for (int i = A; i < 410; ++i) {
        for (int j = A; j < 310; ++j) {
            int d = dp[i][j];
            if (d == 1e9) continue;
            assert(d <= 780);
            // f(x) = i + fim[lim_d-1] + 1  + j * (x-d) + B * (x+lim_d+1-d) * (x-lim_d-d) / 2
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + B * [x * (x-lim_d-d)/2 + (lim_d+1-d)*x/2 + (lim_d+1-d)*(-lim_d-d)/2]
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + (B/2) * [x * (x-2d+1) - (lim_d+1-d)*(lim_d+d)]
            // f(x) = i + fim[lim_d-1] + 1 - j*d + j*x + (B/2) * (x^2-2xd+x) - (B/2) * (lim_d+1-d)*(lim_d+d)
            // f(x) = (B/2) x^2 + (j-dB+B/2) x + (i + fim[lim_d-1] + 1 - j*d - (B/2) * (lim_d+1-d)*(lim_d+d)
            // fixado o j, podemos unicamente determinar a funcao otima!
            retas.pb({j-B*d, i + fim[lim_d-1] + 1 - j*d - (lim_d+1-d)*(lim_d+d)*B/2});
        }
    }
    sort(all(retas));
    for (int l = 0, r = 0; l < sz(retas); l = r) {
        while (r != sz(retas) and retas[r].first == retas[l].first) r++;
        cht.add(retas[r-1].first, retas[r-1].second);
    }
    // ate um certo momento, vou precisar acumular minhas riquezas pra comprar o proximo item
    // depois desse momento, vou ter certa quantidade de dinheiro e de income.
    // a partir desse ponto, nao me importo mais com quanto dinheiro tenho no bolso, mas apenas com quais maquinas vou obter.
    // [income][money]
    // eh super complexudo
    vector<int> ans(q);
    const int lim_q = 1000;
    vector<vector<int>> fim2(lim_q, vector<int>(101));
    // 1e5*100 = 1e7
    for (int i = 1; i < lim_q; ++i) {
        for (int j = 1; j <= 100; ++j) {
            fim2[i][j] = 1 + fim2[i-1][j];
            for (int k = 0; k < n; ++k) {
                if (a[k] <= j) ckmax(fim2[i][j], fim2[i-1][j] + i*b[k] - a[k]);
            }
        }
    }
    vector<int> ord(q); iota(all(ord), 0), sort(all(ord), [&] (int x, int y) { return qu[x] < qu[y]; });
    vector<int> pre_ans(lim_q);
    for (int k = 1; k < lim_q; ++k) {
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < min(lim_i, i+1); ++j) {
                int d = dp[i][j];
                if (d > k) continue;
                if (d == k) ckmax(pre_ans[k], i);
                else {
                    ckmax(pre_ans[k], i + 1 + j * (k-d) + fim2[k-d-1][min(100LL, j)]);
                }
            }
        }
        for (int i = 100; i < lim_m; ++i) {
            for (int j = 100; j < lim_i; ++j) {
                int d = dp[i][j];
                if (d > k) continue;
                if (d == k) ckmax(pre_ans[k], i);
                else {
                    ckmax(pre_ans[k], i + 1 + j * (k-d) + fim2[k-d-1][min(100LL, j)]);
                }
            }
        }
    }
    for (auto i : ord) {
        if (qu[i] < lim_q) {
            ans[i] = pre_ans[qu[i]];
        } else {
            ans[i] = cht.get(qu[i]) + qu[i] * (qu[i]+1) * B / 2;
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    cin >> q;
    vector<int> qu(q);
    for (auto& x : qu) cin >> x;
    auto ans = solve(n, q, a, b, qu);
    for (auto x : ans) cout << x << ' ';
	cout << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 200), q = 3000;
        vector<int> a(n), b(n);
        for (auto& x : a) x = rnd(1, 100);
        for (auto& x : b) x = rnd(1, 100);
        vector<int> qu(q);
        for (auto& x : qu) x = rnd(1, 1000);
        auto my = solve(n, q, a, b, qu);
        auto ans = brute(n, q, a, b, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) cout << a[i] << " " << b[i] << endl;
            cout << q << endl;
            for (auto x : qu) cout << x << " ";
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
