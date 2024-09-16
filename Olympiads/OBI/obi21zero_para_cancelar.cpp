#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
  int n;
  int soma=0;
  cin>>n;
  stack<int>pilha;
  for(int i=0;i<n;i++){
    int a;
    cin>>a;
    if(!a&&i>0){
      pilha.pop();
    }else{
      pilha.push(a);
    }

  }
  while(!pilha.empty()){
    soma+=pilha.top();
    pilha.pop();
  }
  cout<<soma;
  return 0;
}
