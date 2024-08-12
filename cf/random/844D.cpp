#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
using namespace std;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
int main(){
    int n, start, x;cin>>n>>start>>x;
    vector<int>v(n);iota(all(v),1);
    shuffle(all(v), rng);
    int best, indnxt;
    cout<<"? "<<start<<endl;
    cin>>best>>indnxt;
    if(best>=x){
        cout<<"! "<<best<<endl;
        return 0;
    }
    for(int i=0;i<min(n,1000);++i){
        int a,b;
        cout<<"? "<<v[i]<<endl;
        cin>>a>>b;
        if(a<=x&&a>best)best = a, indnxt = b;
    }
    while(best<x&&indnxt!=-1){
        cout<<"? "<<indnxt<<endl;
        cin>>best>>indnxt;
    }
    if(best>=x)cout<<"! "<<best<<endl;
    else cout<<"! "<<-1<<endl;
}