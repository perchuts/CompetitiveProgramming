/*
    Seletiva IOI 2019
    Anido Setter
    https://codeforces.com/group/2k70zKp2Ci/contest/352573/problem/B
    por Gabriel Lucas    
*/

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 5e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int qnt1, qnt2, n, k;
vector<ll>um, dois;
ll pref[maxn][2];
int main(){_
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        ll qnt, tempo;cin>>qnt>>tempo;
        if(qnt==1)um.pb(tempo);
        else dois.pb(tempo);
    }
    sort(all(um)), sort(all(dois));
    for(int i=1;i<=sz(um);++i)pref[i][0] = pref[i-1][0] + um[i-1]; 
    for(int i=1;i<=sz(dois);++i)pref[i][1] = pref[i-1][1] + dois[i-1]; 
    ll resp = 1e18;
    for(int i=0;i<=min(k,sz(um));++i){
        int left = (k - i + 1)/2;
        if(left>sz(dois))continue;
        ckmin(resp, pref[i][0] + pref[left][1]);
    }
    cout<<resp<<endl;
}