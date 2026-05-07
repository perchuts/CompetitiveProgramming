#include <bits/stdc++.h>
using namespace std;
// Order Statistic Set
//
// Funciona do C++11 pra cima

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
// para declarar:
// ord_set<int> s;
// coisas do set normal funcionam:
// for (auto i : s) cout << i << endl;
// cout << s.size() << endl;
// k-esimo maior elemento O(log|s|):
// k=0: menor elemento
// cout << *s.find_by_order(k) << endl;
// quantos sao menores do que k O(log|s|):
// cout << s.order_of_key(k) << endl;

// Para fazer um multiset, tem que
// usar ord_set<pair<int, int>> com o
// segundo parametro sendo algo para diferenciar
// os ementos iguais.
// s.order_of_key({k, -INF}) vai retornar o
// numero de elementos < k
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
    vector<int> a(n), id(n);
    map<int, int> freq;
    ord_set<ii> todos;
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; ++i) {
        freq[a[i]]++;
        id[i] = freq[a[i]];
        todos.insert({a[i], id[i]});
    }
    // is binary searchable
    // if i can do with 2*p+1, can do with 2*p-1
    int M = todos.find_by_order(n/2)->first;
    vector<int> dp(n+1, -inf);
    dp[0] = 0;
    vector<vector<int>> v(n+1, vector<int>(3));
    for (int i = 1; i <= n; ++i) {
        v[i] = v[i-1];
        if (a[i-1] == M) v[i][1]++;
        else if (a[i-1] < M) v[i][0]++;
        else v[i][2]++;
    }

    for (int i = 1; i <= n; ++i) {
        ord_set<ii> bichos;
        for (int j = i; j >= 1; --j) {
            int tam = i-j+1;
            if (tam&1) {
                int cnt1 = v[i][0] - v[j-1][0];
                int cnt2 = v[i][1] - v[j-1][1];
                int cnt3 = v[i][2] - v[j-1][2];
                if (cnt1 <= tam/2 and cnt1+cnt2 > tam/2) ckmax(dp[i], dp[j-1]+1);
            }
        }
    }
    cout << dp[n] << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
