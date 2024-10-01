#include<bits/stdc++.h>

using namespace std;

int func(int n){
    if(n==0) return 0;
    if(n==1) return 1;

    int left = func(n-1);
    int right = func(n-2);
    return left + right;
}

int main(){
  
    int n;
    cin>>n;
    
    cout<<n;
}