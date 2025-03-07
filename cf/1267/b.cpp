#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	string s; cin >> s;
	int n = s.size();
	vector<char> t;
	vector<int> freq;
	t.push_back(s[0]);
	freq.push_back(1);
	for(int i=1;i<n;i++){
		if(s[i] != s[i-1]){
			t.push_back(s[i]);
			freq.push_back(1);
		}
		else freq.end()[-1]++;
	}

	if(t.size() % 2 == 0){
		cout << 0 << endl;
		return 0;
	}

	int L=0;
	int mid = t.size() / 2;
	if(freq[mid] < 2) L=1;
	for(int i=1;i<=mid;i++){
		if(freq[mid-i] + freq[mid+i] <= 2 || t[mid-i] != t[mid+i]) L=1;
	}
	if(L){
		cout << 0 << endl;
		return 0;
	}

	cout << freq[mid]+1 << endl;
	
}
