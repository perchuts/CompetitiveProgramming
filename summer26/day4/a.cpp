#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;
typedef long double ld;

struct Seg{

	int n;
	vector<ld> seg;
	Seg(int n_) : n(n_), seg(4*n) {}

	ld query(int a, int p, int l, int r){ // soma do sufixo [a,n)
		if(r <= a) return 0;
		if(l >= a) return seg[p];
		int m = (l+r)/2;
		return query(a, 2*p, l, m) + query(a, 2*p+1, m, r);
	}

	void update(int a, ld x, int p, int l, int r){
		if(l+1 == r){
			seg[p] = x;
			return;
		}
		int m = (l+r)/2;
		if(a < m) update(a, x, 2*p, l, m);
		else update(a, x, 2*p+1, m, r);
		seg[p] = seg[2*p] + seg[2*p+1];
	}

};

#define C 50

int32_t main() {_

	vector<ld> cf(C);
	const ld pi = acos(-1);
	cout << fixed << setprecision(10);
	cf[0] = 1;
	for(int i=1;i<C;i++){
		cf[i] = cf[i-1] * (2*i-1) / (2*i);
	}
	//for(int i=0;i<10;i++){
	//	cout << i << " " << cf[i] << endl;
	//}
	//cout << flush;
	//return 0;

	const ld d4 = 10000;
	int n; cin >> n;
	vector<int> l(n);
	vector<int> r(n);
	for(auto &x : l) cin >> x;
	for(auto& x : r) cin >> x;

	vector<Seg> seg(C, n);

	for(int i=0;i<C;i++){
		for(int j=0;j<n;j++){
			seg[i].update(j, pow(r[j]/d4, ((ld)(-2*i-1))) * l[j], 1, 0, n);
		}
	}

	ld ts = 0;
	for(int i=0;i<C;i++){
		ts += cf[i] * pow(0.5, 2*i+1);
	}
	cout << ts << endl;

	vector<int> pref(n);
	pref[0] = l[0];
	for(int i=1;i<n;i++) pref[i] = pref[i-1] + l[i];

	int q; cin >> q;
	
	for(int ii=0;ii<q;ii++){

		int t; cin >> t;
		if(t == 1){

			int id, nl, nr;
			cin >> id >> nl >> nr;
			id--;
			r[id] = nr;
			l[id] = nl;

			for(int i=0;i<C;i++){
				seg[i].update(id, pow((r[id]/d4), ((ld)(-2*i-1))) * l[id], 1, 0, n);
			}
		}
		else{

			int x; int ang;
			cin >> x >> ang;
			
			ld s0 = sin(pi *ang / ((ld)(3600 * 180)) );

			cout << "s0 " << s0 << endl;
			// busca binaria pra achar o i0!
			int lb = -1, ub = n;
			while(ub - lb > 1){
				int m = (ub + lb) / 2;
				// maior  que o pr1: ta dentro do 2 (sobe)
				//
				if(x > pref[m]) lb = m;
				else if(x == pref[m]){
					if(m == n-1 || r[m] > r[m+1]) ub = m;
					else lb = m;
				}
				else ub = m;
			}
			// o bicho comeca dentro do ub.
			
			ld ans = 0;
			int l0 = pref[ub] - x;
			int r0 = r[ub];
		
			cout << "l0: " << l0 << endl;
			ans += l0 * (s0 / sqrt(1 - s0 * s0));
			cout << "ans: " << ans << endl;
			
			ld A = s0 * r0 / d4;
			assert(A<1);
			cout << "ss  " << seg[0].query(0, 1, 0, n) << endl;
			for(int i=0;i<C;i++){
				ans += cf[i] * pow(A, 2*i+1) * seg[i].query(ub+1, 1, 0, n);
			}

			cout << ans << endl;
		}

	}

}
