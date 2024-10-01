#include<bits/stdc++.h>
using namespace std;

int a[100005], seg[4 * 100005];

void build(int ind, int low, int high){
    if(low == high){
        seg[ind] = a[low];
        return;
    }

    int mid = (low + high) /2;
    build(2*ind+1, low, mid);
    build(2*ind+2, mid+ 1, high);

    seg[ind] = max(seg[2*ind+1], seg[2*ind+2]);


}


querying to find the maximum value between the range 
int query(ind ind, int low, int high, int l, int r){
    if(low >= l && high <= r){
        return seg[ind];
    }
    if(high < l || low > r) return INT_MIN;
    int mid = (high + low) /2;
    int left = query(2*ind+1, low, mid, l, r);
    int right = query(2*ind+2, mid +1, high, l, r);
    return max(left, right);
    
}