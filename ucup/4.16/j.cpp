#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define gato
#define pb push_back
#define PI pair<int,int>
#define f first
#define s second

using namespace std;

using ll = long long;

int solve(int n, int k, int m, vector<vector<pair<int, int>>> intr) {
    //int n, k, m; cin >> n >> k >> m;

    vector<PI> evs;
    for (int i = 0; i < k; ++i){
        int c = intr[i].size();
        //int c; cin >> c;
        for (auto [a, b] : intr[i]) {
            //a++, b++;
            evs.pb({a,i});
            evs.pb({b+1,i});

        }
        //while (c--){
        //	int a, b; cin >> a >> b;
        //}
    }
    cout << flush;

    sort(evs.begin(), evs.end());

    vector<int> dp(1<<k);

    int cur = 1, act = 0;
    auto add = [&](int l, int r){
        if (l > r) return;
        int le = r-l+1;
        if (__builtin_popcountll(act) >= 2) dp[act] += le;
    };

    auto upd = [&](int ev){
        act ^= (1<<ev);
    };

    for (int i = 0, j; i < evs.size(); i = j+1){
        add(cur, evs[i].f-1);

        j = i;
        while (j+1 < evs.size() and evs[i].f == evs[j+1].f) j++;

        for (int a = i; a <= j; ++a) upd(evs[a].s);
        cur = evs[i].f;
    }


    int tot = 0;
    for (auto v : dp) tot += v;

    vector<vector<int>> vecs(k, vector<int>(1<<k));

    for (int v = 0; v < k; ++v)
        for (int i = 0; i < (1<<k); ++i) if (i>>v&1) vecs[v][i] = dp[i];

    for (int v = 0; v < k; ++v)
        for (int u = 0; u < k; ++u)
            for (int i = 0; i < (1<<k); ++i)if(i>>u&1){
                int j = i^(1<<u);
                vecs[v][i] += vecs[v][j];
            }



    for (int u = 0; u < k; ++u)
        for (int i = 0; i < (1<<k); ++i)if(i>>u&1){
            int j = i^(1<<u);
            dp[i] += dp[j];
        }

    vector<int> resp(1<<k);
    for (int i = 0; i < (1<<k); ++i){
        if (__builtin_popcountll(i) < 2) continue;
        int rev = (1<<k)-1;
        rev ^= i;
        resp[i] = tot - dp[rev];
        for (int u = 0; u < k; ++u) if (i>>u&1){
            resp[i] -= vecs[u][rev|(1<<u)];
        }
    }

    int ans = 0;
    for (auto v : resp) if (v >= m) ans++;
    return ans;
}

int brute(int n, int k, int m, vector<vector<pair<int, int>>> intr) {
    int ans = 0;
    for (int i = 1; i < (1 << k); ++i) {
        vector<int> p(n+1);
        for (int j = 0; j < k; ++j) {
            if (i >> j & 1) {
                for (auto [x, y] : intr[j]) p[x]++, p[y+1]--;
            }
        }
        int z = 0, x = 0;
        for (int j = 0; j < n; ++j) {
            x += p[j];
            if (x >= 2) z++;
        }
        ans += (z >= m);
    }
    return ans;
}
mt19937 rng(time(0));
int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int32_t main() {_
#ifndef gato
    int n, k, m; cin >> n >> k >> m;
    vector<vector<pair<int, int>>> intr(k);
    for (int i = 0; i < k; ++i) {
        int c; cin >> c;
        intr[i].resize(c);
        for (auto& [x, y] : intr[i]) cin >> x >> y;
    }
    cout << solve(n, k, m, intr) << endl;
#else
#endif
    int t = 1;
    while (true) {
        int n = rnd(1, 10), k = rnd(1, 3), m = rnd(1, k);
        vector<vector<pair<int, int>>> intr(k);
        for (auto& v : intr) {
            int z = rnd(1, (1<<n)-1);
            int st = -1;
            for (int w = 0; w <= n; ++w) {
                int b = z >> w & 1;
                if (st == -1 and b) st = w;
                if (st != -1 and b == 0) v.push_back({st, w-1}), st = -1;
            }
        }
        int my = solve(n, k, m, intr);
        int ans = brute(n, k, m, intr);
        if (my != ans) {
            cout << "WA " << t << endl;
            cout << n << " " << k << " " << m << endl;
            for (int i = 0; i < k; ++i) {
                cout << intr[i].size() << endl;
                for (int j = 0; j < intr[i].size(); ++j) cout << intr[i][j].first+1 << " " << intr[i][j].second+1 << endl;
            }
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "AC " << t++ << endl;
    }
}
