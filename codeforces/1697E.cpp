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
const int mod = 998244353;
const int maxn = 101;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ii v[maxn];
ll f[maxn], ncr[maxn][maxn];
 
set<int>s[maxn];
 
int dist(int i,int j){
    auto [x1,y1] = v[i];
    auto [x2,y2] = v[j];
    return abs(x1-x2) + abs(y1-y2);
}
 
int n;
 
int main(){_
    cin>>n;
    
    int duplas = 0, triplas = 0, quatro = 0;
 
    for(int i=1;i<=n;++i)cin>>v[i].first>>v[i].second;
 
    for(int i=1;i<=n;++i){
        int mn = inf;
        for(int j=1;j<=n;++j){
            if(i==j)continue;
            if(ckmin(mn,dist(i,j)))s[i] = {j};
            else if(mn==dist(i,j))s[i].insert(j);
        }
        s[i].insert(i);
        bool nice = 1;
        for(auto j:s[i]){
            if(s[j]!=s[i])nice = 0;
        }
        if(nice){
            if(sz(s[i])==2)duplas++;
            if(sz(s[i])==3)triplas++;
            if(sz(s[i])==4)quatro++;
        }
    }
 
    ncr[0][0] = 1;
 
    ll res = 0;
 
    for(int i=1;i<=n;++i){
        f[i] = 1;
        for(ll j=n;j>n-i;--j)f[i] = (f[i]*j)%mod;
    }
 
    for(int i=1;i<=n;++i){
        for(int j=0;j<=i;++j){
            if(!j)ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1])%mod;
        }
    }
    
    for(int i=0;i<=duplas;++i){
        for(int j=0;j<=triplas;++j){
            for(int k=0;k<=quatro;++k){
                int grupos = n - i - 2*j - 3*k;
                ll tmp = (ncr[duplas][i]*ncr[triplas][j]*ncr[quatro][k])%mod;
                tmp = (tmp*f[grupos])%mod;
                res = (res+tmp)%mod;
            }
        }
    }
 
    cout<<res<<endl;
}