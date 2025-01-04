#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define int ll
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

template <typename T> struct rmq {
  vector<T> v;
  int n;
  static const int b = 30;
  vector<int> mask, t;

  int op(int x, int y) { return v[x] <= v[y] ? x : y; }
  int msb(int x) { return __builtin_clz(1) - __builtin_clz(x); }
  int small(int r, int sz = b) { return r - msb(mask[r] & ((1 << sz) - 1)); }
  rmq() {}
  rmq(const vector<T> &v_) : v(v_), n(v.size()), mask(n), t(n) {
    for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
      at = (at << 1) & ((1 << b) - 1);
      while (at and op(i - msb(at & -at), i) == i)
        at ^= at & -at;
    }
    for (int i = 0; i < n / b; i++)
      t[i] = small(b * i + b - 1);
    for (int j = 1; (1 << j) <= n / b; j++)
      for (int i = 0; i + (1 << j) <= n / b; i++)
        t[n / b * j + i] =
            op(t[n / b * (j - 1) + i], t[n / b * (j - 1) + i + (1 << (j - 1))]);
  }
  int index_query(int l, int r) {
    if (r - l + 1 <= b)
      return small(r, r - l + 1);
    int x = l / b + 1, y = r / b - 1;
    if (x > y)
      return op(small(l + b - 1), small(r));
    int j = msb(y - x + 1);
    int ans = op(small(l + b - 1),
                 op(t[n / b * j + x], t[n / b * j + y - (1 << j) + 1]));
    return op(ans, small(r));
  }
  T query(int l, int r) { return v[index_query(l, r)]; }
};
int get(int a, int b) {
    if (a == 1) return 0;
    return get((a + b - 1) / b, b) + 1;
}

void test_case() {
    int n; cin >> n;
    vector<int> a(n); for (int &x : a) cin >> x;
    vector<int> b(n); for (int &x : b) cin >> x;

    rmq<int> R(b);

    int max_a = *max_element(a.begin(), a.end());
    int min_b = *min_element(b.begin(), b.end());
    int lim = get(max_a, min_b);

    auto solve = [&](auto &&self, int l, int r) -> vector<int> {
      if (l == r) {
        vector<int> ans(lim, max_a);
        int cur = a[l];
        for (int i = 0; i < lim; i++) {
            ans[i] = cur;
            cur = (cur + b[l] - 1) / b[l];
        }

        return ans;
      }
      int mn = R.query(l, r);
      int pos = R.index_query(l, r);
      vector<int> left, right;
      if (pos != r) left = self(self, l, pos), right = self(self, pos + 1, r);
      else left = self(self, l, r - 1), right = self(self, r, r);

      vector<int> ans(lim, max_a);
      int i = 0, j = 0;
      while (i + j < lim) {
          ans[i + j] = min(ans[i + j], max(left[i], right[j]));
          if (max(left[i], right[j]) == 1) break;

          if (max(left[i], right[j]) == left[i]) i++;
          else j++;
      }

      for (int i = 1; i < lim; i++)
          ans[i] = min(ans[i], (ans[i - 1] + mn - 1) / mn);

      return ans;
    };
    auto best = solve(solve, 0, n - 1);

    int ans = lim;
    for (int i = lim - 1; i >= 0; --i)
        if (best[i] == 1) ans = i;

    cout << ans << endl;
}

int32_t main() {
    fast_io;

    int t = 1;
    cin >> t;
    while (t--) test_case();
}

