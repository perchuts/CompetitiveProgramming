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
    vector<ll>v(n);
    map<ll,int>mark;
    for(auto& x:v)cin>>x;
    ll sum=0, cnt = 0;
    for(auto x:v){
        sum+=x;
        mark[x]++;
    }
    priority_queue<ll>pq;
    pq.push(sum);
    int cortes = 0;
    while(cortes<n){
        if(pq.empty()){
            break;
        }
        ll x = pq.top();pq.pop();
        if(mark[x]!=0){
            mark[x]--;
            cnt++;
        }
        else{
            ll a = x/2+(x&1ll), b = x/2;
            cortes++;
            pq.push(a);pq.push(b);
        }
    }
    while(!pq.empty()){
        if(mark[pq.top()]!=0){
            mark[pq.top()]--;
            cnt++;
        }
        pq.pop();
    }
    cout<<(cnt==n?"YES":"NO")<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}