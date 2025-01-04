#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main() { _
    int n, k; cin >> n >> k;
    vector<vector<int>> g(n); 
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<int>> layer(n);
    auto dfs = [&] (auto&& self, int u, int p, int lvl) -> void {
        layer[lvl].pb(u);
        for (auto v : g[u]) {
            if (v == p) continue;    
            self(self, v, u, lvl+1);
        }
    };
    dfs(dfs, 0, 0, 0);
    int kk = 2*k-1;
    vector<int> dp(1<<kk), ndp(1<<kk), val(1<<kk), val2(1<<kk);
    vector<int> id(n, -1), id2(n);
    int cnt = 0, ans = 0;
    dp[1] = 1;
    for (auto v : g[0]) id[v] = 0;
    vector<int> popc(1<<kk);
    for (int i = 0; i < (1 << kk); ++i) popc[i] = __builtin_popcount(i);
    for (int i = 1; i < n; ++i) {
		//cout << "inicio" << endl;
        cnt++;
        // vou setar o id dos pais desses caras
        if ((int)layer[i].size() == (int)layer[i-1].size() && i != n-1 && layer[i+1].size() != 0) {
            for (auto x : layer[i]) {
                for (auto v : g[x]) {
                    if (id[v] != -1) continue;
                    id[v] = id[x];
                }
            }
            continue;
        }
        // agora quero fazer automaticamente as ultimas cnt-2 layers! caso cnt seja impar, vamos fazer as ultimas cnt-3 layers.
        // dai vou rodar a dp na mao nessas ultimas rodadinhas, e tambem na primeira rodada do proximo cara
        int tentar, cnt2 = 0;
        if (cnt == 1) tentar = 1;
        else if (cnt & 1) tentar = 3;
        else tentar = 2;
        for (int j = 0; j < (1 << (int)layer[i-tentar].size()); ++j) dp[j] += (int)layer[i-tentar].size() * (cnt-tentar) / 2;
        assert(cnt % 2 == tentar % 2);
        for (int w = i-tentar+1; w <= i; ++w) {
			cnt2 = 0;
			for (int j = 0; j < layer[w-1].size(); ++j) val2[1<<j] = 0;
			for (auto x : layer[w]) {
				if (cnt2 < kk) val[(1<<cnt2)] = (1<<id[x]);
				val2[(1<<id[x])] |= (1<<cnt2);
				cnt2++;
			}
			for (int j = 1; j < (1 << layer[w-1].size()); ++j) val2[j] = (val2[j&(-j)] | val2[j - (j&(-j))]);
            int z = (1 << layer[w-1].size()) - 1;
            if (layer[w].size() > kk) break;
            for (int j = 0; j < (1 << layer[w].size()); ++j) {
                // vou pegar j, o cara tem direito a pegar j complemento
                if (j) val[j] = (val[j&(-j)] | val[j - (j&(-j))]);
                ndp[j] = max(ndp[j - (j?(j&(-j)):0)], dp[z^val[j]] + min(k, popc[j]));
            }
            swap(dp, ndp);
			//cout << "dp na camada " << w << endl;
			//for (auto x : dp) cout << x << ' ';
			//cout << endl;
        }
        //cout << "layer: " << i << endl;
        //cout << "id: ";
        //for (int j = 0; j < layer[i].size(); ++j) cout << id[layer[i][j]] << ' ';
        //cout << endl;
        if ((int)layer[i].size() > kk) {
            for (int j = 0; j < (1 << (int)layer[i-1].size()); ++j) {
                //cout << j << ' ' << dp[j] << ' ' << val2[j] << ' ' << dp[j] + min(k, (int)layer[i].size() - __builtin_popcount(val2[j])) << endl;
                ans = max(ans, dp[j] + min(k, (int)layer[i].size() - __builtin_popcount(val2[j])));
            }
            for (int j = i+1; j < n; ++j) if (layer[j].size() != 0) {
                assert(layer[j] >= layer[j-1]);
                ans += k;
            }
            cout << ans << endl;
            exit(0);
        }
        //cout << "dp: ";
        //for (int j = 0; j < (1<<layer[i].size()); ++j) cout << dp[j] << ' ';
		//cout << endl;
        
        cnt2 = cnt = 0;
        for (auto x : layer[i]) {
            id[x] = cnt2++;
            for (auto v : g[x]) {
                if (id[v] != -1) continue;
                id[v] = id[x];
            }
        }
    }    
    ans = *max_element(begin(dp), end(dp));
    cout << ans << endl;
}
