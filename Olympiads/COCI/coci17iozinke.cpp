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

string v[maxn];
int main(){_
    int n;cin>>n;
    unordered_map<string,int>pwords;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        pwords[v[i]]++;
    }    
    ll ans = 0;
    for(int i=1;i<=n;i++){
        set<string>vis;
        for(int j=0;j<sz(v[i]);j++){
            string tmp = "";
            for(int k=j;k<sz(v[i]);k++){
                tmp+=v[i][k];
                if(vis.count(tmp)==0)ans+=1LL*pwords[tmp];
                vis.insert(tmp);
            }
        }
    }
    cout<<ans-n<<endl;
}