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
const int maxn = 2e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int v[maxn], resp[maxn];
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        cin>>v[i];
        resp[i] = -1;
    }
    int cur = 1;
    while(cur<=n&&v[cur]==0)resp[cur++] = 0;
    resp[cur] = 1;
    for(;cur<=n;++cur){
        if(resp[cur]!=0){
            if(v[cur]+1>n)break;
            else resp[v[cur]+1] = 0;
        }else{
            if(v[cur]+cur>n)break;
            else resp[v[cur]+cur] = 0;
        }
    }
    for(int i=1;i<=n;++i)cout<<(resp[i]==-1?1:resp[i])<<" ";
    cout<<endl;
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}