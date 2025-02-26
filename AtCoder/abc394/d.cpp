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

void solve(){
    string s; cin >> s;
    vector<stack<int>> st(3);
    map<char, int> id;
    map<char, int> fecha;
    id['('] = id[')'] = 0;
    id['<'] = id['>'] = 1;
    id['['] = id[']'] = 2;
    fecha[')'] = fecha['>'] = fecha[']'] = 1;
    for (int i = 0; i < sz(s); ++i) {
        int idx = id[s[i]];
        int fechar = fecha[s[i]];
        for (int j = 0; j < 3; ++j) {
            if (idx == j) st[j].push(fechar);
            else st[j].push(-1);
        }
        while (true) {
            int pos = -1;
            for (int j = 0; j < 3; ++j) {
                if (sz(st[j]) >= 2) {
                    int eu = st[j].top(); st[j].pop(); int eu2 = st[j].top();
                    if (eu == 1 and eu2 == 0) {
                        st[j].pop();
                        pos = j;
                        break;
                    } else {
                        st[j].push(eu);
                    }
                }
            }
            if (pos == -1) break;
            for (int j = 0; j < 3; ++j) {
                if (j != pos) {
                    assert(st[j].top() == -1);
                    st[j].pop();
                    assert(st[j].top() == -1);
                    st[j].pop();
                }
            }
        }
    }
    for (int j = 0; j < 3; ++j) {
        if (!st[j].empty()) {
            cout << "No" << endl;
            exit(0);
        }
    }
    cout << "Yes" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
