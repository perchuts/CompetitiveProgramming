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

int v[2*maxn],n,k,freq[2*maxn];

bool possible(int d){
    for(int i = d+1;i<=n;i++){
        if(2*(freq[i] - freq[i-d-1]) - n >= k)return true;
    }
    return false;
}

void solve(){
    cin>>n>>k;
    // cout<<"testcase"<<endl;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        freq[v[i]]++;
    }
    for(int i=1;i<=n;i++){
        freq[i]+=freq[i-1];
        // cout<<freq[i]<<" ";
    }
    // cout<<endl;
    int l = 0, r = n-1, ans = n-1;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md)){
            ans = md;
            r = md-1;
        }else{
            l = md + 1;
        }
    }
    int x,y;
    for(int i = ans+1;i<=n;i++){
        if(2*(freq[i] - freq[i-ans-1]) - n >= k){
            x = i - ans, y = i;
            break;
        }
    }
    cout<<x<<" "<<y<<endl;
    int sum  = 0,start = 1,cnt=0;
    for(int i = 1;i<=n;i++){
        if(cnt==k-1){
            cout<<i<<" "<<n<<endl;
            break;
        }
        sum += (x<=v[i]&&v[i]<=y ? 1 : -1);
        if(sum>0){
            cout<<start<<" "<<i<<endl;
            start = i+1;
            cnt++;
            sum = 0;
        }
    }
    for(int i=1;i<=n;i++)freq[i] = 0;
}


int main(){_
    int t;cin>>t;
    while(t--)solve();
}