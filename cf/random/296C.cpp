#include <bits/stdc++.h>

using namespace std;
long long v[100010],freq[100010],vfreq[100010];
pair<pair<long long,long long>,long long>op[100010];
int main(){

	long long n,m,k;cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=1;i<=m;i++){
		long long l,r,d;cin>>l>>r>>d;
		op[i]={{l,r},d};
	}
	for(int i=0;i<k;i++){
		int l,r;cin>>l>>r;
		freq[l]++;freq[r+1]--;
	}
	long long cur=0;
	for(int i=1;i<=m;i++){
		cur+=freq[i];
		auto [x,d] = op[i];
		auto [l,r] = x;
		vfreq[l]+=d*cur;
		vfreq[r+1]-=d*cur;
	}
	long long add=0;
	for(int i=1;i<=n;i++){
		add+=vfreq[i];
		cout<<v[i]+add<<" ";
	}
	cout<<endl;

}
