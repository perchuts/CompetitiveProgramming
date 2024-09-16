/*
    Seletiva IOI 2020
    Pirâmides
    https://codeforces.com/group/2k70zKp2Ci/contest/352987/problem/A
    por Gabriel Lucas
*/

#include <bits/stdc++.h>
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
 
ii box[maxn];
int dp[2*maxn],bit[2*maxn],n;
void insert(int x,int d){
    while(x<=2*n)ckmax(bit[x],d),x+=x&(-x);
}
 
int query(int x){
    int ans = 0;
    while(x){
        ckmax(ans,bit[x]);
        x-=x&(-x);
    }
    return ans;
}
 
 
int main(){_
    cin>>n;
    vector<int>v;
    for(int i=1;i<=n;++i){
        cin>>box[i].first>>box[i].second;
        v.pb(box[i].first);v.pb(box[i].second);
    }
    sort(all(v));
    sort(box+1,box+1+n,[](ii x,ii y){
        return max(x.first,x.second) < max(y.first,y.second);
    });
    //once picked, we cant pick any box above
    auto getindex = [&](int x){
        return lower_bound(all(v),x) - begin(v) + 1;
    };
    for(int i=1;i<=n;++i){
        // dp[i] = max(dp[j]) for all j such that i>j and min(box[i]) > box[j]
        // got it: lets use an BIT to store min coordinates and get maximum.
        int x = getindex(box[i].first), y = getindex(box[i].second);
        int best = query(min(x,y));
        insert(min(x,y),best+1);
    }
    cout<<query(2*n)<<endl;
 
}