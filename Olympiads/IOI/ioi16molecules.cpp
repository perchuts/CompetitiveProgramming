#include <bits/stdc++.h>
#include "molecules.h"
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

/*
find a contigous subarray such that its sum is in [l,u]
why does this work?
suppose that a solution exists with a gap of 1 
[x,y] + [a,a] are selected but z not
x........y z a.......  
sum + z-x > r
sum + z-a < l
-sum -z+a > -l
=> a-x > r-l
impossible!!!
*/
// sum - sum' <= r
// -sum' <= r - sum
// sum' >= sum - r
//
vector<int> find_subset(int l,int u, vector<int> w) {
    int n=sz(w);
    ll sum = 0;
    vector<int>ans,aux(n);
    vector<pair<ll,int>>pr;
    iota(all(aux),0);
    sort(all(aux),[&](int x,int y){
        return w[x]<w[y];
    });
    pr.pb({0,-1});
    for(int i=0;i<n;++i){
        sum += 1LL*w[aux[i]];
        int x = lower_bound(all(pr),make_pair(sum-1LL*u,-10)) - begin(pr);
        if(sum-pr[x].first>=l){
            for(int j=pr[x].second+1;j<=i;++j)ans.pb(aux[j]);
            break;
        }
        pr.pb({sum,i});
    }
    return ans;
}

// int main(){
//     int l,u,n;cin>>l>>u>>n;
//     vector<int>w(n);
//     for(int i=0;i<n;++i)cin>>w[i];
//     vector<int>resp = find_subset(l,u,w);
//     if(!sz(resp))cout<<-1;
//     else for(auto x:resp)cout<<x<<" ";
// }