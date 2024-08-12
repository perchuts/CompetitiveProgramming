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

int c[maxn];
map<int,int>qnt;
void solve(){
    int n;cin>>n;
    qnt.clear();
    for(int i=1;i<=n;++i)cin>>c[i];
    for(int i=1;i<=n;++i){
        qnt[c[i]]++;
    }
    bool ok = 1;
    for(int i=1;i<n;++i){
        if(c[i+1]>c[i]+1)ok = 0;
    }
    if(c[1]>c[n]+1)ok = 0;
    if(qnt[1]!=1)ok = 0;
    for(int i=2;i<=n;++i){
        if(qnt[i]>n-i+1)ok = 0;
    }
    cout<<(ok?"YES":"NO")<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}