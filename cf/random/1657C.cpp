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

char s[5*maxn];
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>s[i];
    int resp = 0, i = 1;
    while(i<n){
        char me = s[i], prox = s[i+1];
        int start = i;
        if(me==prox||me=='('&&prox==')'){
            resp++,i+=2;
        }else{
            //)(
            bool ok = 0;
            i+=2;
            while(i<=n){
                if(s[i]==')'){
                    i++, ok = 1, resp++;
                    break;
                }
                i++;
            }
            if(!ok){
                i=start;break;
            }
        }
    }
    cout<<resp<<" "<<n-i+1<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}