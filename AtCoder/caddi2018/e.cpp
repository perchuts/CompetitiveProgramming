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

int solve(int n, vector<int> A){
    vector<vector<int>> a(2, vector<int>(n));
    reverse(all(A)); a[1] = A;
    for (int i = 0; i < n; ++i) a[0][i] = a[1][n-1-i]*2;
    vector<vector<int>> sexo(2, vector<int>(n));
    for (int j = 0; j < 2; ++j) {
        // non increasing
        vector<int> shift(n), dist(n);
        stack<ii> st;
        st.push({0, 0});
        for (int i = 1; i < n; ++i) {
            sexo[j][i] = sexo[j][i-1];
            int x = a[j][i-1], y = a[j][i];
            // dist[i] = quantas vezes preciso multiplicar o i pra ele ficar >= que o i+1
            // se for negativo quer dizer que ele ja eh maior
            // 9 2 -> dist = -2
            //
            while (x < a[j][i]) x *= 4, dist[i-1]++;
            while (4*y <= a[j][i-1]) y *= 4, dist[i-1]--;
            st.push({i, i});
            while (sz(st) > 1) {
                auto [l1, r1] = st.top(); st.pop();
                auto [l2, r2] = st.top(); st.pop();
                int diff = shift[r2] - shift[l1];
                int need = max(0LL, dist[r2] - diff);
                if (need == 0) {
                    st.push({l2, r2});
                    st.push({l1, r1});
                    break;
                }
                #ifndef gato
                //cout << "merda: r2 = " << r2 << " need = " << need << " diff = " << diff << endl;
                #endif
                sexo[j][i] += (r2-l2+1)*need;
                shift[l2] += need;
                if (l2 != r2) shift[r2] += need;
                st.push({l2, r1});
            }
        }
        #ifndef gato
        //cout << "dist: ";
        //for (int i = 0; i < n; ++i) cout << dist[i] << ' ';
        //cout << endl;
        //cout << "A: ";
        //for (int i = 0; i < n; ++i) cout << a[j][i] << ' ';
        //cout << endl;
        //cout << "sexo: ";
        //for (int i = 0; i < n; ++i) cout << sexo[j][i] << ' ';
        //cout << endl;
         #endif
    }
    reverse(all(sexo[1]));
    int ans = min(sexo[0][n-1]*2+n, sexo[1][0]*2);
    for (int i = 0; i < n-1; ++i) ckmin(ans, i+1 + 2*(sexo[0][i] + sexo[1][i+1]));
    return ans;
}

int brute(int n, vector<int> a) {
    int ans = inf;
    for (int i = 0; i <= n; ++i) {
        auto aa = a;
        int ops = 0;
        for (int j = 0; j < i; ++j) aa[j] *= -2, ops++;
        for (int j = i-2; j >= 0; --j) {
            while (aa[j] > aa[j+1]) aa[j] *= 4, ops += 2;
        }
        for (int j = i+1; j < n; ++j) {
            while (aa[j-1] > aa[j]) aa[j] *= 4, ops += 2;
        }
        ckmin(ans, ops);
    }
    return ans;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 15);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 15);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

