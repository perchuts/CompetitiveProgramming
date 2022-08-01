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
 
pair<int,int>proximo[maxn];
void solve(){
    //a resposta ira demorar no maximo 2*n passos
    //posso andar somente com um cara que nao faz diferenca
    int n;cin>>n;
    string s[2];
    cin>>s[0]>>s[1];
    proximo[n+1] = {-1,-1};
    for(int i=n-1;i>=0;--i){
        if(s[0][i]=='*'&&s[1][i]=='*')proximo[i+1] = {i,2};
        else if(s[0][i]=='*')proximo[i+1] = {i,0};
        else if(s[1][i]=='*')proximo[i+1] = {i,1};
        else proximo[i+1] = proximo[i+2];
    }
    int current = 0;
    int ans = 0;
    for(int i=0;i<n;++i){
        if(s[0][i]=='*'&&s[1][i]=='*'){
            if(proximo[i+2].first==-1){
                ans++;break;
            }
            ans += proximo[i+2].first - i + 1;
        }
        else if(s[0][i]=='*'){
            if(proximo[i+2].first==-1)break;
            ans += proximo[i+2].first - i;
            s[0][proximo[i+2].first] = '*'; 
        }
        else if(s[1][i]=='*'){
            if(proximo[i+2].first==-1)break;
            ans += proximo[i+2].first - i;
            s[1][proximo[i+2].first] = '*';
        }
    }
    cout<<ans<<endl;    
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}