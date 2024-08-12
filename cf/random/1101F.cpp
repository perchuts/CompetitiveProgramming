#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
 
using namespace std;
 
using ll = long long;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int>cities;
vector<tuple<int,int,ll,int>>trucks;
 
bool possible(ll x,int i){
    //check for x fuel capacity in truck i
    auto [s,f,c,r] = trucks[i];
    --s, --f;
    int refuelings = 0;
    ll cur = x;
    for(int i=s;i<f;++i){
        ll cost = c*ll(cities[i+1]-cities[i]);
        if(cur<cost)refuelings++, cur = x;
        cur -= cost;
        if(cur<0||refuelings>r)return 0;
    }
    return 1;
}
 
int main(){
    int n,m;cin>>n>>m;
    vector<int>perm(m);
    cities.resize(n), trucks.resize(m);
    iota(all(perm),0), shuffle(all(perm),rng);
    for(auto &x:cities)cin>>x;
    for(auto &[s,f,c,r]:trucks)cin>>s>>f>>c>>r;
    ll mx = 0;
    for(auto cur:perm){
        //check if current maximum works. if it doesnt, binary search the answer
        if(!possible(mx,cur)){
            ll l = mx+1ll, r = 2e18, answer;
            while(l<=r){
                ll md = l + (r-l+1ll)/2;
                if(possible(md,cur))r = md - 1ll, answer = md;
                else l = md + 1ll;
            }
            mx = answer;
        }
    }
    cout<<mx<<endl;
}