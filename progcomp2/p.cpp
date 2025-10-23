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
const int INF = inf;
int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

struct eertree {
    // tentando codar isso de cabeca, parece divertido
    // um estado q parece canonico eh o estado de 1 letra...
    vector<int> link, tam, height;
    vector<tuple<int, int, int, char, bool>> tab;
    map<pair<int, char>, int> tr;
    string s;
    int cur, head, tot;
    eertree() {
        link.pb(0), tam.pb(-1);
        link.pb(0), tam.pb(0);
        height = {0, 0};
        s += "$";
        head = 0;
        cur = 1;
        tot = 0;
    }
    
    void add(char c) {
        s += c, head++;
		int old = cur;
        while (s[head-tam[cur]-1] != c) cur = link[cur];
        if (tr[make_pair(cur, c)] == 0) {
            int cur2 = link[cur];
            while (s[head-tam[cur2]-1] != c) cur2 = link[cur2];
            int z = tr[make_pair(cur2, c)];
            ckmax(z, 1);
            link.pb(z);
            tam.pb(tam[cur]+2);
            height.pb(height[link.back()]+1);
            tab.pb({old, sz(link)-1, cur, c, true});
            cur = tr[make_pair(cur, c)] = sz(link) - 1;
        } else {
            tab.pb({old, tr[make_pair(cur, c)], cur, c, false});
            cur = tr[make_pair(cur, c)];
        }
        tot += height[cur];
    }
    
    void rem() {
        s.pop_back(); head--;
        auto [c1, c2, c3, cc, tt] = tab.back(); tab.pop_back();
        tot -= height[c2];
        if (tt) {
            tr[make_pair(c3, cc)] = 0;
            link.pop_back();
            tam.pop_back();
            height.pop_back();
        }
        cur = c1;
        // eh basicamente desfazer oq foi feito. 
    }
};

vector<int> solve(string s) {
    eertree aut;
    vector<int> ans;
    for (auto c : s) {
        if (c == '-') {
            aut.rem();
        } else {
            aut.add(c);
        }
        ans.pb(aut.tot);
    }
    return ans;
}
vector<int> brute(string s) {
    vector<int> ans;
    string sexo;
    for (auto c : s) {
        if (c == '-') {
            sexo.pop_back();
        } else {
            sexo += c;
        }
        int tot = 0;
        for (int i = 0; i < sz(sexo); ++i) {
            for (int j = i; j < sz(sexo); ++j) {
                bool ok = true;
                for (int k = i; k <= j; ++k) {
                    ok &= (sexo[k] == sexo[j-(k-i)]);
                }
                tot += ok;
            }
        }
        ans.pb(tot);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int lixo; cin >> lixo;
    string s; cin >> s;
    auto ans = solve(s);
    for (auto x : ans) cout << x << ' ';
    cout << endl;
#else
    int t = 1;
    while (true) {
        int tam = rnd(1, 30);
        string s(tam, 'a');
        int bal = 0;
        for (auto& x : s) {
            x = rnd('a', 'b');
            if (bal and rnd(0, 2) == 2) x = '-', bal--;
            else bal++;
        }
        auto my = solve(s);
        auto ans = brute(s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << tam << endl;
            cout << s << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
