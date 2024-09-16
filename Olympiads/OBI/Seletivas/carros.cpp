/*
    Seletiva IOI 2019
    Carros
    https://codeforces.com/group/2k70zKp2Ci/contest/263327/problem/B
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
const int maxn = 1e6+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int a[maxn], b[maxn], n, m;

bool possible(int x){
    for(int i=0;i<=min(x,n);++i){
        if(a[1+i]+x>=b[max(0,m-(x-i))]-x)return true;
    }
    return false;
}
 
int main(){_
    cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=m;++i)cin>>b[i];
    a[n+1] = inf, b[0] = -1;
    int l = 0, r = min(n,m), resp = r;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md))resp = md, r = md - 1;
        else l = md + 1;
    }
    cout<<resp<<endl;
}