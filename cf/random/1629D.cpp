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

map<string,bool>possible;
void solve(){
    int n;cin>>n;
    bool ok = 0;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        string rev = s;
        reverse(all(rev));
        possible[s] = 1;
        if(possible[rev])ok = 1;
        if(sz(rev)>1&&possible[rev.substr(0,sz(rev)-1)])ok=1;
        if(sz(rev)<3){
            for(int i='a';i<='z';i++){
                if(possible[rev+char(i)]){
                    ok=1;
                    break;
                }
            }
        }        

    }
    cout<<(ok ? "YES" : "NO")<<endl;
    possible.clear();

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    string a = "ab";
    int t;cin>>t;
    while(t--)solve();
}