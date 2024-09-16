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

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ll a[3*maxn];

int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    priority_queue<array<ll,2>>pq;
    ll s = 0,bi;
    for(int i=1;i<=n;i++){
        s+=a[i];
        cin>>bi;    
        if(s<bi&&!pq.empty()&&pq.top()[0]>bi){
            s += pq.top()[0];
            pq.pop();
        }
        if(s>=bi){
            s-=bi;
            pq.push({bi,i});
        }
    }
    vector<int>ans;
    while(!pq.empty()){
        ans.pb(pq.top()[1]);
        pq.pop();
    }
    sort(all(ans));
    cout<<sz(ans)<<endl;
    for(auto x:ans)cout<<x<<" ";
}