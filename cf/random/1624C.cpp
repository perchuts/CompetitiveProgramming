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

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

int v[51];
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        while(v[i]>n)v[i]/=2;
    }
    multiset<int>s;
    for(int i=1;i<=n;i++){
        s.insert(v[i]);
    }    
    bool ok;
    while(true){
        ok=1;
        for(int i=1;i<=n;i++){
            while(s.count(i)>1){
                ok=0;
                s.erase(s.find(i));
                s.insert(i/2);
            }
        }
        if(ok)break;
    }
    ok = 1;
    for(int i=1;i<=n;i++){
        if(s.count(i)==0)ok=0;
    }
    cout<<(ok ? "YES" : "NO")<<endl;
    
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}