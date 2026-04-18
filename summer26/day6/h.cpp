#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;
vector<int> pr;

int pot(int b, int e, int p){
	int r = 1;
	while(e){
		if(e&1) r = r * b % p;
		e /= 2; b = b * b % p;
	}
	return r;
}

void solve(int fodase){
	cout << "Case #" << fodase << ": ";


	int ans = -1;

	int d, k; cin >> d >> k;
	vector<int> s(k);
	for(auto& x : s) cin >> x;
	if(k == 1){
		cout << "I don't know." << endl;
		return;
	}
	if(k == 2){
		if(s[0] == s[1]){
			cout << s[0] << endl;
		}
		else cout << "I don't know." << endl;
		return;
	}


	if(s[0] == s[1]){
		cout << s[0] << endl;
		return;
	}

	int dk = 1;
	for(int i=0;i<d;i++) dk *= 10;

	int mx = 0;
	for(auto x : s) mx = max(mx, x);

	for(int ii=0;ii<pr.size();ii++){
		int p = pr[ii];
		if(p > dk) break;
		if(p <= mx) continue;

		int den = pot(p+s[0]-s[1], p-2, p);
		int a = (p+s[1]-s[2]) * den % p;
		int ok = 1;
		for(int i=3;i<k;i++){
			if((a * (p+s[i-2]-s[i-1]) + p + s[i]-s[i-1])% p){
				ok = 0;
				break;
			}
		}
		if(ok){
			//cout << p << ": OK ";
			int nans = (s[k-1] + (p+s[k-1] - s[k-2]) * a) % p;
			//cout << nans << endl;
			if(ans == -1) ans = nans;
			else if(ans != nans){
				ans = -1;
				break;
			}
		}
	}
	if(ans == -1) cout << "I don't know." << endl;
	else cout << ans << endl;
}

int32_t main() {_
	const int N = 1000000;
	vector<int> p(N);
	for(int i=2;i<N;i++){
		if(p[i]) continue;
		pr.push_back(i);
		for(int j=2*i;j<N;j+=i) p[j] = i;
	}
	int t; cin >> t;
	for(int i=1;i<=t;i++) solve(i);
}
