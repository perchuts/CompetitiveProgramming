/*
    Seletiva IOI 2018
    Comida
    https://codeforces.com/group/2k70zKp2Ci/contest/356247/problem/A
    por Gabriel Lucas

    Solução: inevitavelmente vou ter que passar pelo subsegmento de soma minima. Levando isso em consideração,
    é garantido que se existe alguma escolha possível, ela seguirá as seguintes restrições:
      1. seja [l,r] o intervalo de soma mínima
      2. seja V = (r,n] + [1,l), e opt = max(sufixo de V).
      3. temos que opt+soma[l,r] >= 0  e total >= 0.
    dá pra calcular tudo isso usando uma seg pra array circular (de tamanho 2n, onde i+n = i)
    provavelmente existem soluções muito mais simples, mas isso funciona
*/
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
 
struct Node{
    ll sufmn, prefmn, tot, best, sufmx;
    int sc, pc, answer;//suffix coord, prefix coord
    ii opt;
}seg[4*maxn], null;
 
Node merge(Node l,Node r){
    Node resp;
    resp.tot = l.tot + r.tot;
    resp.prefmn = min(l.prefmn,l.tot+r.prefmn), resp.sufmn = min(r.sufmn,r.tot+l.sufmn);
 
    if(resp.prefmn==l.prefmn)resp.pc = l.pc;
    else resp.pc = r.pc;
 
    if(resp.sufmn==r.sufmn)resp.sc = r.sc;
    else resp.sc = l.sc;
 
    resp.sufmx = max(r.sufmx,r.tot+l.sufmx);
 
    if(resp.sufmx==r.sufmx)resp.answer = r.answer;
    else resp.answer = l.answer;
 
    resp.best = min({l.best,r.best,l.sufmn+r.prefmn});
 
    if(resp.best==l.best)resp.opt = l.opt;
    else if(resp.best==r.best)resp.opt = r.opt;
    else resp.opt = {l.sc,r.pc};
 
    return resp;
}
 
void update(int i,int l,int r,int x,ll d){
    if(l>x||r<x)return;
    if(l==r){
        seg[i].tot += d, seg[i].prefmn = seg[i].sufmn = seg[i].sufmx = seg[i].best = seg[i].tot;
        seg[i].sc = seg[i].pc = seg[i].answer = l, seg[i].opt = {l,l};
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d), update(2*i+1,md+1,r,x,d);
    seg[i] = merge(seg[2*i],seg[2*i+1]);
}
 
int n,q;
 
Node query(int i,int l,int r,int x=1,int y=n){
    if(l>y||r<x||x>y)return null;
    if(x<=l&&r<=y)return seg[i];
    int md = (l+r)/2;
    return merge(query(2*i,l,md,x,y),query(2*i+1,md+1,r,x,y));
}
 
int getAnswer(){
    Node resp = query(1,1,2*n);
    if(resp.best>=0)return 1;
    auto [l,r] = resp.opt;
    Node resp2 = query(1,1,2*n,r+1,l-1+n);
    ll tot = seg[1].tot/2;
    if(tot>=0&&resp2.sufmx+resp.best>=0)return resp2.answer<=n?resp2.answer:resp2.answer-n;
    return 0;
}
 
int main(){_
    cin>>n>>q;
 
    null.sufmn = null.prefmn = null.best = 1e12, null.sufmx = -1e12, null.tot = 0;
 
    for(int i=1;i<=n;++i){
        int t;
        ll g;cin>>t>>g;
        update(1,1,2*n,i,(t==1?-g:g)), update(1,1,2*n,n+i,(t==1?-g:g));
    }
 
    cout<<getAnswer()<<endl;
 
    for(int i=1;i<=q;++i){
        int t, x;
        ll g;
        cin>>t>>x>>g;
        update(1,1,2*n,x,(t==1?-g:g)), update(1,1,2*n,n+x,(t==1?-g:g));
        cout<<getAnswer()<<endl;
    }
 
}