#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve(){
	string st; cin >> st;
	int n = st.size();
	int ans = 0;

	int c = 0;
	for (int i = 0; i < n; ++i){
		if (st[i] == '?') ans = max(ans, 1ll), c++;
		else c = 0;
		if (c >= 3) ans = 2;
	}

	int i = 0;
	while (i < n){
		if (st[i] != '0'){
			i++;
			continue;
		}

		vector<int> vec;
		int cur = 0;
		int rig = -1;
		bool wr = false;

		for (int k = i; k < n; ++k){
			if (st[k] == '0') cur++;
			else if (st[k] == '?'){
				if (!cur) {
					rig = k;
					break;
				}
				vec.pb(cur);
				cur = 0;
			} else{
				if (cur) vec.pb(cur), wr = true;
				rig = k;
				break;
			}	
		}

		if (rig == -1) {
			rig = n;
			if (cur) vec.pb(cur), wr = true;
		}

		bool wl = false;
		if (i == 0) wl = true;
		else if (st[i-1] == '1') wl = true;

		if (vec.size() == 1){
			int a = vec[0];
			if (!wl or !wr) ans = max(ans, a+1);
			ans = max(ans,a);

			if (!wl and !wr){
				if (i-2 >= 0 and st[i-2] == '?') ans = max(ans,a+2);
				if (rig+1 < n and st[rig+1] == '?') ans = max(ans,a+2);
			}

			i = rig;
			continue;
		}

		if (vec.size() == 2){
			int ab = vec[0]+vec[1]+1;
			if (!wl and !wr) ans = max(ans, ab+1);
			ans = max(ans, ab);
			i = rig;
			continue;
		}	

		int ab = vec[0] + vec[1] + 1;
		if (!wl) ans = max(ans, ab+1);
		ans = max(ans, ab);

		for (int aa = 1; aa+2 < vec.size(); ++aa){
			int w = vec[aa] + vec[aa+1] + min(vec[aa-1], vec[aa+2]) + 2;
			ans = max(ans, w);
		}

		ab = vec.back() + vec.end()[-2] + 1;
		if (!wr) ans = max(ans, ab+1);
		ans = max(ans, ab);
		i = rig;
	}
	
	
	for (int i = 1; i+2 < n; ++i){
		if (st[i-1] == '0' and st[i] == '?' and st[i+1] == '?' and st[i+2] == '0'){
			int a = 0, b = 0, x = 0, y = 0;

			int j = i+2;
			while (j < n and st[j] == '0') j++;
			a = j-(i+2);

			bool ok1 = true;
			if (j >= n or st[j] == '1') ok1 = false;

			if (j+1 < n and st[j] == '?' and st[j+1] == '0'){
				int k = j+1;
				j = k;
				while (j < n and st[j] == '0') j++;
				b = j-k;
			}

			j = i-1;
			while (j >= 0 and st[j] == '0') j--;
			y = i-1-j;

			bool ok2 = true;
			if (j < 0 or st[j] == '1') ok2 = false;

			if (j-1 >= 0 and st[j] == '?' and st[j-1] == '0'){
				int k = j-1;
				j = k;
				while (j >= 0 and st[j] == '0') j--;
				x = k-j;
			}

			if (ok1) ans = max(ans, min(a+b+2, a+y+2));
			if (ok2) ans = max(ans, min(x+y+2, a+y+2));
		}
	}


	for (int i = 1; i+3 < n; ++i){
		if (st[i-1] == '0' and st[i] == '?' and st[i+1] == '?' and st[i+2] == '?' and st[i+3] == '0'){
			int a = 0;

			int j = i+3;
			while (j < n and st[j] == '0') j++;
			a = j-(i+3);

			int y = 0;

			j = i-1;
			while (j >= 0 and st[j] == '0') j--;
			y = i-1-j;

			ans = max(ans, min(a,y)+2);

		}
	}

	cout << ans << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}
