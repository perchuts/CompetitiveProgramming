#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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
    vector<int> color(n), penis(300);
    penis['R'] = 0, penis['G'] = 1, penis['B'] = 2;
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        color[i] = penis[c];
    }
    // core idea: it is always possible.
    // we want a construction that consists of a disjoint union of 3 paths, one for each color
    // by induction, we want to add a new cell in the line. how to keep the tip of each path connected
    // to the unbounded region?
    // 111111
    // 12313123
    //   333333
    //
    // 3333333333
    // 3222222223
    // 3211111123
    // 3212313123
    // 3222333
    // 333333
    //
    // 33333333333333
    // 31111111111113
    // 313333333333133333333333
    // 313222222223111111111113
    // 313211111123111333333313 1111111
    // 313212313123131323232313213131312
    // 3132223331233333222223332133333
    // 313333331122222222222222213
    // 311111111111111111111111113
    // 333333333333333333333333333
    // depois de experimentos complexos e iluminadores (veja acima)
    // tenho 3 personagens:
    // dominante, 2o, 3o.
    // quando me aparece alguem diferente do ultimo:
    // se eh o dominante, facilmente estendemos ele pra alcancar por cima
    // se eh o 2o, estendemos por baixo
    // se eh o 3o, fazemos ele virar o novo dominante.
    // eh isto!
    // o caso base eh a segunda vez que me aparece 3 caras distintos. isso me define quem sera o dominante, 2o, 3o.
    // vou dormir e codar isso outro dia.
    // ta resolvido!
    // na verdade eh mais complicado que isso. eu preciso considerar por qual sentido eu adicionei os bichos (cima ou baixo).
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
