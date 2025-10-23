#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;

	vector<int> heap(2*n+2);
	vector<int> dir(2*n+2);
	//vector<int> dedo(n+1);
	int ult = 1;

	for(int i=0;i<2*n;i++){

		string s; cin >> s;
		int x; cin >> x;
		if(s[0] == 'a'){
			heap[ult] = x;
			ult++;

			vector<int> qr;
			for(int j = ult-1; j>=1; j/=2){
				qr.push_back(heap[j]);
			}

			for(int j = ult-1; j>=2; j/=2){
				int irmao = j;
				if(j % 2 == 0) irmao++;
				else irmao--;
				if(irmao >= ult) continue;
				qr.push_back(heap[irmao]);
			}

			cout << qr.size() << " ";
			for(auto x : qr) cout << x << " ";
			cout << endl;

			vector<int> sorted(qr.size());
			for(auto& x : sorted) cin >> x;

			vector<int> rev(n+1);
			for(int j=0;j<qr.size();j++){
				rev[sorted[j]] = j;
			}

			//cout << "rev " ;
			//for(int i=1;i<=n;i++) cout << rev[i] << " ";
			//cout << endl;

			for(int j = ult-1; j>=2; j/=2){
				if(rev[heap[j]] < rev[heap[j/2]]) swap(heap[j], heap[j/2]);
				if(rev[heap[j/2*2]] < rev[heap[j/2*2+1]]) dir[j/2] = 0;
				else dir[j/2] = 1;
			}
		}

		else{
			int pos = -1;
			for(int i=1;i<ult;i++) if(heap[i] == x) pos = i;

			heap[pos] = heap[ult-1];
			ult--;


			int folha = pos;
			while(2*folha < ult){
				if(2*folha+1 == ult){
					folha = 2*folha;
					break;
				}
				folha = 2*folha + dir[folha];
			}

			if(folha == ult){
				cout << "0" << endl;
			}


			else{
			vector<int> qr;
			for(int j=folha; j>=1; j/=2){
				qr.push_back(heap[j]);
			}

			for(int j = folha; j>=2; j/=2){
				int irmao = j;
				if(j % 2 == 0) irmao++;
				else irmao--;
				if(irmao >= ult) continue;
				qr.push_back(heap[irmao]);
			}

			cout << qr.size() << " ";
			for(auto x : qr) cout << x << " ";
			cout << endl;

			vector<int> sorted(qr.size());
			for(auto& x : sorted) cin >> x;

			vector<int> rev(n+1);
			for(int j=0;j<qr.size();j++){
				rev[sorted[j]] = j;
			}
			//cout << "rev " ;
			//for(int i=1;i<=n;i++) cout << rev[i] << " ";
			//cout << endl;
			//

			int bicho = pos;
			while(2*bicho < ult){
				if(2*bicho+1 == ult){
					int filho = 2*bicho;
					if(rev[heap[bicho]] > rev[heap[filho]]) swap(heap[bicho], heap[filho]);
					break;
				}
				int filho = 2*bicho + dir[bicho];
				if(rev[heap[bicho]] > rev[heap[filho]]) swap(heap[bicho], heap[filho]);
				bicho = filho;
			}


			for(int j = folha; j>=2; j/=2){
				if(rev[heap[j]] < rev[heap[j/2]]) swap(heap[j], heap[j/2]);
				if(rev[heap[j/2*2]] < rev[heap[j/2*2+1]]) dir[j/2] = 0;
				else dir[j/2] = 1;
			}
			}
		}

		//cout << "heap: " ;
		//for(int i=1;i<ult;i++) cout << heap[i] << " ";
		//cout << endl;

		if(ult > 1) cout << heap[1] << endl;
		else cout << -1 << endl;
	}
}
