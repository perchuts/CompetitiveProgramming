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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }


void solve(){
    int n;cin>>n;
    vector<int>v(n);
    bool one = 0, zero = 0;
    for(auto& x:v){
        cin>>x;
        if(x==0)zero=1;
        if(x==1)one=1;
    }
    if(one&&zero)cout<<"NO"<<endl;
    else{
        if(one){
            bool ok = 1;
            sort(all(v));
            for(int i=0;i<n-1;++i)if(v[i]+1==v[i+1])ok = 0;
            cout<<(ok?"YES":"NO")<<endl;
        }else if(zero){
            cout<<"YES"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}