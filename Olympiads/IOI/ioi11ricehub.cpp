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
#include "ricehub.h"
using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<ll>v;
ll money;
int n;

int getmid(int i,int size){
    return i + size/2;
}

bool possible(int x){
    ll cost = 0, parity = 1ll*((x-1)&1);

    for(int i=1;i<=x;++i)
        cost += abs(v[1+x/2]-v[i]);

    if(cost<=money)return 1;
    for(int i=2;i<=n-x+1;++i){
        cost += v[i-1] - v[getmid(i-1,x)] + parity*(v[getmid(i,x)] - v[getmid(i-1,x)]) + v[i+x-1] - v[getmid(i,x)]; 
        if(cost<=money)return 1;
    }
    return 0;
}


int besthub(int cnt, int mx, int x[], ll b)
{
    v.pb(0);
    for(int i=0;i<cnt;++i)v.pb(1LL*x[i]);
    money = b, n = cnt;
    int l = 1, r = n, ans = 1;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md))ans = md, l = md + 1;
        else r = md - 1;
    }
    return ans;
}


// int c[maxn];
// int main(){_
//     int n,l;ll b;cin>>n>>l>>b;
//     for(int i=0;i<n;++i)cin>>c[i];
//     cout<<besthub(n,l,c,b)<<endl;
// }