#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;
#define P 998244353


int pot(int b, int e){
	int r = 1;
	while(e){
		if(e&1) r = r * b % P;
		e /= 2; b = b * b % P;
	}
	return r;
}



vector<int> mul(int k, vector<int> a, vector<int> b){

	int ik = pot(k, P-2);
	//int ik = 1;
	vector<int> c(2*k-1);
	for(int i=0;i<k;i++) for(int j=0;j<k;j++) c[i+j] = (c[i+j] + a[i] * b[j]) % P;
	for(int i=2*k-2;i>=k;i--){
		for(int j =1;j<=k;j++){
			c[i-j] = (c[i-j] +  ik * c[i]) % P ;
		}
	}
	c.resize(k);
	return c;
}

vector<int> ppot(int n, int k){

	// x^n mod x^k - (1/k) * (x^(k-1) + ... + 1)
	
	if(k == 1){
		return {1};
	}
	vector<int> ans(k);
	ans[0] = 1;
	vector<int> b(k);
	b[1] = 1;
	while(n){
		if(n&1) ans = mul(k, ans, b);
		n /= 2; b = mul(k, b, b);
	}
	return ans;
}

int solve(int n, int m, int k, vector<int> v){
	


	if(k == 1){
		if(m == 0) return  (n+1) % P;
		else return -1;
	}

	vector<int> b(k);
	vector<int> d(k); // coeficiente de a0
	int atual = n+1;
	//b[0] = 1;
	for(int i=0;i<k;i++){
		b[i] = (2) * ((atual+i)%P) % P * pot(k+1, P-2) % P;
	}

	//for(int i=0;i<10;i++){
	//	auto c = ppot(i, k);
	//	cout << i << ": ";
	//	for(auto x : c) cout << x << " ";
	//	cout << endl;
	//}

	for(int ii=0;ii<=m;ii++){
		int buraco = v[ii];
		vector<int> nb(k), nd(k);
		if(buraco+1 < atual){
			for(int i=0;i<k;i++){
				// calcular b[buraco + 1 + i] a partir de b[atual], b[atual+1], ...
				int passos = atual+k-1 - (buraco + i + 1);
				vector<int> c = ppot(passos, k);
				for(int j=0;j<k;j++){
					nb[i] = (nb[i] + c[j] * b[k-1-j]) % P;
					nd[i] = (nd[i] + c[j] * d[k-1-j]) % P;
				}
			}
			atual = buraco + 1;
			swap(b, nb);
			swap(d, nd);
		}
		//for(int i=0;i<k;i++){
		//	cout << setw(3) << atual+i << ":" << setw(3) << b[i] << setw(3) << d[i] << endl;
		//}
		//cout << "____________" << endl;

		// agora eh fazer homem-das-cavernas com que atual = buraco.
		if(buraco != -1){
			for(int i=k-1;i>=1;i--) b[i] = b[i-1], d[i] = d[i-1];
			b[0] = (2) * (buraco%P) % P * pot(k+1, P-2) % P;
			//b[0] = 0;
			d[0] = 1;
			atual = buraco;
		}

		//for(int i=0;i<k;i++){
		//	cout << setw(3) << atual+i << ":" << setw(3) << b[i] << setw(3) << d[i] << endl;
		//}
		//cout << "____________" << endl;
	}

	// temos: ans = d[0] * ans + b[0]
	// ans = b[0] / (1 - d[0])
	
	if(d[0] == 1){
		return -1;
	}
	int ans = b[0] * pot((P+1-d[0])%P, P-2) % P;
	return ans;
}

int32_t main() {_

	int t; cin >> t;
	while(t--){

		int n, m, k; cin >> n >> m >> k;
		vector<int> v(m);
		for(auto& x : v) cin >> x;
		reverse(v.begin(), v.end());
		v.push_back(-1);
		
		int ans = solve(n, m, k, v);
		cout << ans << endl;

	}
	
}
