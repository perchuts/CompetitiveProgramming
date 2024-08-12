#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int query(int r,int i){
    cout<<"? "<<(1<<i) - r<<" "<<(1<<i) - r + (1<<(i+1))<<endl;
    int x;cin>>x;
    if(x==(1<<(i+1)))return r + (1<<i);
    else return r;
}
 
void solve(){
    int r = 0;
    for(int i=1;i<=30;++i){
        r = query(r,i-1);
    }
    cout<<"! "<<r<<'\n';
}
 
int main(){_
    int t;cin>>t;
    while(t--)solve();
}