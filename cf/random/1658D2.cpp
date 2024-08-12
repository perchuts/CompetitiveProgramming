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
const int maxn = 1<<18;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
struct node{
    node *neighbor[2];
    node(){
        neighbor[0] = neighbor[1] = nullptr;
    }
};
node *Trie;
int v[maxn];
void solve(){
    int l,r;cin>>l>>r;
    Trie = new node();
    int qnt = 0, tmp = r;
    while(tmp)++qnt, tmp>>=1;
    for(int i=1;i<=r-l+1;++i){
        cin>>v[i];
        node *cur = Trie;
        for(int j=qnt-1;~j;--j){
            bool parity = (v[i]&(1<<j)); 
            if(cur->neighbor[parity]==nullptr)cur->neighbor[parity] = new node();
            cur = cur->neighbor[parity];
        }
    }
    int resp = 0;
    auto can = [&](int x){
        node *cur = Trie;
        int result = 0, result2 = 0;
        for(int i=qnt-1;~i;--i){
            //x&1^eu = 1 => eu = 1^x&1 
            bool parity = (x&(1<<i)), best = 1^parity;
            if(cur->neighbor[best]!=nullptr)cur = cur->neighbor[best], result+=(1<<i);
            else cur = cur->neighbor[best^1];
        }
        cur = Trie;
        for(int i=qnt-1;~i;--i){
            bool parity = (x&(1<<i)), best = parity;
            if(cur->neighbor[best]!=nullptr)cur = cur->neighbor[best];
            else cur = cur->neighbor[best^1], result2 += (1<<i);
        }
        return result==r&&result2==l;
    };
    
    for(int i=1;i<=r-l+1;++i){
        int candidato = v[i]^l;
        if(can(candidato)){
            resp = candidato;
            break;
        }
    }
    cout<<resp<<endl;
}
 
 
int main(){_
    int t;cin>>t;
    while(t--)solve();
}