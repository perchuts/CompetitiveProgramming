#include <bits/stdc++.h>
#define sz(x) (int) x.size()
#define pb push_back
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
 fast_io;
 int q; cin >> q;
    struct node {
        int ans = 1<<30, qnt = 0, val = 0;
        int ptr[2];
        node() { ptr[0] = ptr[1] = 0; }
    };
    vector<node> trie;
    trie.pb(node());
    auto upd = [&] (auto&& self, int i, int x, int type, int layer = 29) -> void {
        if (layer == -1) {
            trie[i].val = x;
            trie[i].qnt += type;
            if (trie[i].qnt >= 2) trie[i].ans = 0;
            else trie[i].ans = 1<<30;
            return;
        };
        int prox = trie[i].ptr[x>>layer&1];
        if (prox == 0) {
            trie[i].ptr[x>>layer&1] = sz(trie);
            trie.pb(node());
        }
        prox = trie[i].ptr[x>>layer&1];
        self(self, prox, x, type, layer-1);
        int l = trie[i].ptr[0], r = trie[i].ptr[1];
        if (l == 0) trie[i].qnt = trie[r].qnt, trie[i].ans = trie[r].ans, trie[i].val = trie[r].val;
        else if (r == 0) trie[i].qnt = trie[l].qnt, trie[i].ans = trie[l].ans, trie[i].val = trie[l].val;
        else {
            trie[i].qnt = trie[l].qnt+trie[r].qnt;
            if (trie[l].qnt == 1 and trie[r].qnt == 1) {
                trie[i].ans = trie[l].val ^ trie[r].val;
            } else {
                trie[i].ans = min(trie[l].ans, trie[r].ans);
            }
            if (trie[l].qnt == 1 and trie[r].qnt == 0) trie[i].val = trie[l].val;
            else if (trie[l].qnt == 0 and trie[r].qnt == 1) trie[i].val = trie[r].val;
        }
    };
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            upd(upd, 0, x, 1);
        } else if (op == 2) {
            int x; cin >> x;
            upd(upd, 0, x, -1);
        } else {
            cout << trie[0].ans << endl;
        }
    }
}
