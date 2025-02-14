#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

void prox(int n, vector<int> p){
	if(n == 1){
		cout << 0 << endl;
		return;
	}
	int pri = -1; // ultima pos. que eh estritamente maior que a proxima
	for(int i=0;i<=n-3;i++){
		if(p[i] > p[i+1]) pri = i;
	}


	int sm = 0;
	for(int i = pri+1; i<n; i++){
		sm += p[i]; // varios iguais e o ultimo cai
	}

	int a = p[pri+1];
	for(int i=0;i<=pri;i++){
		cout << p[i] << " ";
	}
	cout << a+1 << " ";
	sm -= a+1;
	for(int i=0;i<sm;i++){
		cout << 1 << " ";
	}
	cout << endl;


}

void prev(int n, vector<int> p){

	int pri = -1; // ultimo nao-1
	for(int i=0;i<n;i++){
		if(p[i] > 1) pri = i;
	}
	if(pri == -1){
		cout << 0 << endl;
		return;
	}

	for(int i=0;i<pri;i++){
		cout << p[i] << " ";
	}

	int sm = 0;
	for(int i=pri;i<n;i++) sm += p[i];
	int a = p[pri];
	cout << a-1 << " ";
	sm -= a-1;
	// agora eh a lexicograficamente maxima usando bichos <= a-1
	while(sm >= a-1){
		cout << a-1 << " ";
		sm -= a-1;
	}
	if(sm > 0) cout << sm;
	cout << endl;
}

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> p(n);
	for(auto& x : p) cin >> x;
	prox(n, p);
	prev(n, p);
}
