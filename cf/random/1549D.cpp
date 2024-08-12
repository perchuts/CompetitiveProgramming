#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define int ll
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
 
int v[2*maxn], table[2*maxn][20], ultima[2*maxn];
 
ll gcd(int x,int y){return (x==0?y:gcd(y%x,x));}
 
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    //gcd delta consecutive numbers
    //achar o maior subsegmento onde o gcd da diferenca de numeros consecutivos é maior que 1.
    // = candidatas sem query
    //sparse table! pra cada i, faco uma query no maior intervalo possivel
    //O(Nlog^2N)
    for(int j=0;j<20;++j){
        for(int i=1;i+(1<<j)<=n;++i){
            if(j==0)table[i][j] = abs(v[i+1] - v[i]);
            else table[i][j] = gcd(table[i][j-1],table[i+(1<<(j-1))][j-1]);
            ultima[i] = j;
        }
    }
 
    int resp = 1;
 
    auto query = [&](int i){
        int current, now=i, st = ultima[i];
        while(true){
            bool ok = 0;
            for(int j=st;j>=0;--j){
                if(now+(1<<j)>n)continue;
                if((now==i&&table[now][j]!=1)||(now!=i&&gcd(current,table[now][j])!=1)){
                    ok=1, current = now==i?table[now][j]:gcd(current,table[now][j]), now += (1<<j), st = j;
                    break; 
                }
            }
            if(!ok){
                return now - i + 1;
            }
        }
    };
 
    for(int i=1;i<n;++i){
        ckmax(resp, query(i));
        // cout<<query(i)<<" \n"[i==n-1];
    }
 
    cout<<resp<<endl;
}
 
 
int32_t main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}