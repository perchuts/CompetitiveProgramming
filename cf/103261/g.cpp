#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	
	for (auto &i : a) cin >> i;

	ord_set<int> st;
	for (int i : a) st.insert(i);

	int mx = 0;
	for (int i : a) {
		mx = max<int>(mx, st.order_of_key(i) + 1);
		st.erase(i);
	}


	cout << mx << endl;
}
