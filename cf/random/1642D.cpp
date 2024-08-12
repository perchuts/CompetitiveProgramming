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

map<int,int>cnt;
// 3 2 1 4 4 3 1 
// 3 2 1 4 4 3 2 2 1
// 3 2 1 4 4 3 2 1 1 2 1
// 3 2 1 4 4 3 2 1 4 4 1 2 1

void solve(){
    int n;cin>>n;
    vector<int>v(n+1);
    for(int i=1;i<=n;++i){
        cin>>v[i];
        cnt[v[i]]++;
    }
    for(int i=1;i<=n;++i){
        if(cnt[v[i]]&1){
            cout<<-1<<endl;
            cnt.clear();
            return;
        }
    }
    // 1 3 1 2 2 3
    // 1 3 1 3 3 2 2 3
    //1 3 1 3 3 2 2 3 2 2
    //1 3 1 3 3 2 2 3 2 2
    vector<ii>operations;
    vector<ii>intervals;
    int st = 1, i = 1;
    while(i<sz(v)){
        if(v[i]==v[st]&&i!=st){
            for(int j=1;j<i-st;++j){
                if(i+j>=sz(v)||v[st+j]!=v[i+j]){
                    v.insert(begin(v)+i+j,2,v[st+j]);
                    operations.pb({i+j-1,v[st+j]});
                }
            }
            intervals.pb({st,i+i-st-1});
            i = i+i-st;
            st = i;
        }else ++i;
    }
    cout<<sz(operations)<<endl;
    for(auto [p,c]:operations)cout<<p<<" "<<c<<endl;
    cout<<sz(intervals)<<endl;
    
    for(auto [a,b]:intervals){
        cout<<b-a+1<<" ";
    }
    cout<<endl;
    cnt.clear();
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}