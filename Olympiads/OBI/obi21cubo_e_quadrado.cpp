#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;
long long a,b;
bool ok[100000010];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin>>a>>b;
    int ans=0;
    for(int i=1;i<=10000;i++){
        long long sq=i*i;
        if(sq<=b&&sq>=a){
            if(ok[sq])ans++;
            ok[sq]=1;
        }

        long long cube=i*i*i;
        if(cube<=b&&cube>=a){
            if(ok[cube])ans++;
            ok[cube]=1;
        }
    }
    cout<<ans<<endl;
}