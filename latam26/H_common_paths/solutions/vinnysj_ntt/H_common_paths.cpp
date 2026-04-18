#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>
#include <bit>
#define pb push_back
#define del pop_back
#define ll long long
#define mp make_pair
#define pii pair<int, int>
#define deriva_e_iguala_a return
#define fcin ios_base::sync_with_stdio(false)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define all(v) v.begin(), v.end()
#define print(vec, a, b) for(int i = a; i < b; i++){cout << vec[i] << ' ';} cout << endl
#define printr(vec) for(auto i: vec){cout  << i << ' ';} cout << endl
#define endl '\n'

using namespace std;
#define __lg(x) (std::bit_width((unsigned long long)(x)) - 1) // Clang lmao
 
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
 
const int LG = 19, N = 1 << LG, MOD = 998244353, root = 62;
const double PI = acos(-1);
 
 
vector<int> graph[N], szs[N];
vector<pair<vector<int>, int>> res_info;
vector<int> cur;
int sz[N], vis[N];
vector<ll> rt(2, 1);
vector<int> final[LG+1];
ll ans[N];
vector<ll> prod[N];
int hlfsz;


ll fast_exp(ll base, ll exp, ll mod = MOD){
    ll res = 1;
    while(exp){
        if(exp&1){
            res = (res * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return res;
}
 
ll inv_exp(ll base, ll mod = MOD){
    return fast_exp(base, mod-2);
}

 
void ntt(vector<int> &a){ // kactl
    int n = a.size(), L = 31 - __builtin_clz(n);
    vector<int> rev(n);
    for(static int k = 2, s = 2; k < N; k *= 2, s++){
        rt.resize(N);
        ll z[] = {1, fast_exp(root, MOD >> s, MOD)};
        for(int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
    }
    for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for(int k = 1; k < n; k *= 2){
        for(int i = 0; i < n; i += 2 * k){
            for(int j = 0; j < k; j++){
                int z = rt[j + k] * a[i + j + k] % MOD;
                int &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                ai += (ai + z >= MOD ? z - MOD : z);
            }
        }
    }
}

void ntt_inv(vector<int>& a){
    int invN = inv_exp((int)a.size());
    for(int& x: a) x = 1ll*x*invN % MOD;
    reverse(a.begin()+1, a.end());
    ntt(a);
}

void dfs(int u, int p){
    sz[u] = 1;
    for(int v: graph[u]){
        if(v == p || vis[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void dfs_reroot(int u, int p, int n, int sum_sz = 0){
    /*
    Calcular o coef de x^N da subárvore enraizada em U e V sendo o pai

    Aqui fica uma merda, mas pelo que deu fica:

    prod_u_v = (n - szs[v])^2 - soma(todo filho w exceto v)szs[w]^2
    */
    int sum_sq = 0;
    for(int v: graph[u]){
        if(v == p){
            szs[u].push_back(sum_sz);
        }
        else{
            szs[u].push_back(sz[v]);
        }
        sum_sq += 1ll*szs[u].back()*szs[u].back() % MOD;
        if(sum_sq >= MOD) sum_sq -= MOD;
    }
    int it = 0;
    for(int v: graph[u]){
        sum_sq -= 1ll*szs[u][it]*szs[u][it] % MOD;
        if(sum_sq < 0) sum_sq += MOD;
        ll cur_prod = (1ll*(n - szs[u][it])*(n - szs[u][it]) - sum_sq) % MOD;
        if(cur_prod < 0) cur_prod += MOD;
        prod[u].push_back(cur_prod);
        if(v != p) dfs_reroot(v, u, n, n-szs[u][it]);
        sum_sq += 1ll*szs[u][it]*szs[u][it] % MOD;
        if(sum_sq >= MOD) sum_sq -= MOD;
        ++it;
    }
}

int centr(int u, int p){
    for(int v: graph[u]){
        if(v == p || vis[v]) continue;
        if(sz[v] > hlfsz) return centr(v, u);
    }
    return u;
}

void dfs2(int u, int p, int d){
    sz[u] = 1;
    if(d >= (int)cur.size()){
        cur.resize(d+1);
    }
    int it = 0;
    for(int v: graph[u]){
        ll cur_prod = prod[u][it++];
        if(v == p || vis[v]){
            if(v == p){
                cur[d] += cur_prod;
                if(cur[d] >= MOD) cur[d] -= MOD;
            }
            continue;
        }
        dfs2(v, u, d+1);
        sz[u] += sz[v];
        if(!d){
            res_info.resize(res_info.size() + 1);
            swap(res_info.back().first, cur);
            res_info.back().second = it-1;
        }
    }
}

void conv_add(vector<int>& now, vector<int>& a){
    int n = (int)a.size();
    if(n > (int)now.size()){
        ntt_inv(now);
        now.resize(a.size());
        ntt(now);
    }
    
    int idx = __lg(n);
    for(int i = 0; i < n; ++i){
        final[idx][i] += 1ll*now[i]*a[i] % MOD;
        if(final[idx][i] >= MOD) final[idx][i] -= MOD;
        now[i] += a[i];
        if(now[i] >= MOD) now[i] -= MOD;
    }
}

void work(int centr){
    if(res_info.empty()) return;
    sort(all(res_info), [](pair<vector<int>, int>& a, pair<vector<int>, int>& b){
        return a.first.size() < b.first.size();
    });
    vector<int> now = {0};
    int lst = 1;
    int pqp = 0;
    for(int i = 0; i < (int)res_info.size(); ++i){
        auto& [res, idx] = res_info[i];
        for(int j = 0; j < (int)now.size(); ++j){ // DFT do impulso eh uma constante
            now[j] += prod[centr][idx] - pqp;
            if(now[j] < 0) now[j] += MOD;
            if(now[j] >= MOD) now[j] -= MOD;
        }
        int need = (int)res.size() + lst - 1;
        need = 1 << (__lg(need-1) + 1);
        lst = (int)res.size();
        res.resize(need);
        ntt(res);
        conv_add(now, res);
        pqp = prod[centr][idx];
    }
    res_info.clear();
}

void centr_decomp(int start, int n){
    res_info.reserve(n);
    for(int i = 0; i <= LG; ++i){
        final[i].resize(1 << i);
    }
    dfs(start, 0);
    dfs_reroot(start, 0, n);
    hlfsz = sz[start] >> 1;
    int u;
    vector<int> st;
    st.pb(centr(1, 0));
    while(!st.empty()){
        u = st.back();
        st.pop_back();
        vis[u] = 1;
        dfs2(u, 0, 0);
        work(u);
        for(int v: graph[u]){
            if(!vis[v]){
                hlfsz = sz[v] >> 1;
                st.pb(centr(v, 0));
            }
        }
    }
    for(int i = 0; i <= LG; ++i){
        ntt_inv(final[i]);
        for(int j = 1; j < (int)final[i].size(); ++j){
            ans[j] += final[i][j];
            if(ans[j] >= MOD) ans[j] -= MOD;
        }
    }
}


int main(){
    fcin;
    cin.tie(0);
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int n, u, v;
    cin >> n;
    for(int i = 0; i < n-1; i++){
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    centr_decomp(1, n);
    for(int i = 1; i < n; ++i){
        cout << ans[i] << ' ';
    }
    cout << endl;
    deriva_e_iguala_a 0;
}
