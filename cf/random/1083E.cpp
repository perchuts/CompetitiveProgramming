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
 
ll a[maxn];
int main(){_
    int n;cin>>n;
    vector<pair<ll,ll>>v(n);    
    for(int i=0;i<n;++i)cin>>v[i].first>>v[i].second>>a[i];
 
    vector<int>sorted(n);
    iota(all(sorted),0);
    sort(all(sorted), [&](int i,int j){
        return v[i].first<v[j].first;
    });
    
    ll resp = 0;
    deque<pair<ll,ll>>dq;// (coeficiente angular, constante)
    dq.push_front({0, 0});
    for(int i=0;i<n;++i){
        //dp[i] = x*y - a[i] + max(dp[j] - xj*yi)
        ll cur = v[sorted[i]].first*v[sorted[i]].second - a[sorted[i]], yi = v[sorted[i]].second, 
        xi = v[sorted[i]].first;
 
        while(sz(dq)>1){
            auto [xj, dpj] = dq.back();dq.pop_back();
            auto [xk, dpk] = dq.back();
            if(yi*xj + dpj > yi*xk + dpk){
                dq.push_back({xj,dpj});
                break;
            }
        }
 
        ll dpi;
        auto [xbest, dpbest] = dq.back();
        dpi = cur + yi*xbest + dpbest;
 
        ckmax(resp, dpi);
 
        while(sz(dq)>1){
            auto [xj, dpj] = dq.front();dq.pop_front();
            auto [xk, dpk] = dq.front();
            if((long double)(dpj-dpi)/(long double)(-xi-xj)<(long double)(dpk-dpj)/(long double)(xj-xk)){
                dq.push_front({xj, dpj});
                break;
            }
        }
 
        dq.push_front({-xi, dpi});
    }
 
    cout<<resp<<endl;
}