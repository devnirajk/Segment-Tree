#include<bits/stdc++.h>
using namespace std;

void createSegmentTree(int* tree, int* arr, int si, int ei, int index){
    if(si == ei){
        tree[index] = arr[si];
        return;
    }

    int mid = (si+ei)/2;

    createSegmentTree(tree, arr, si, mid, 2*index);
    createSegmentTree(tree, arr, mid+1, ei, 2*index+1);

    tree[index] = tree[2*index] + tree[2*index+1];
}

void update(int* tree, int* arr, int si, int ei, int index, int updateIndex, int updateValue){

    if(updateIndex == si){
        arr[si] = updateValue;
        tree[index] = updateValue;
        return;
    }

    int mid = (si+ei)/2;

    if(mid < updateIndex){
        update(tree, arr, mid+1, ei, 2*index+1, updateIndex, updateValue);
    }else{
        update(tree, arr, si, mid, 2*index, updateIndex, updateValue);
    }

    tree[index] = tree[2*index] + tree[2*index+1]; 
}

int query(int* tree, int si, int ei, int index, int left, int right){
    if(ei < left || right < si){
        return 0;
    }

    if(left <= si && right >= ei){
        return tree[index];
    }

    int mid = (si+ei)/2;
    return query(tree, si, mid, 2*index, left, right) + query(tree, mid+1, ei, 2*index+1, left, right); 
}

int main(){
    int n;
    cin>>n;

    int* arr = new int[n];

    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    int* tree = new int[2*n];

    createSegmentTree(tree, arr, 0, n-1, 1);

    int updateIndex = 2;
    int updateValue = 10;
    update(tree, arr, 0, n-1, 1, updateIndex, updateValue);

    for(int i=1; i<2*n; i++){
        cout<<tree[i]<<endl;
    }
    
    int right = 4, left = 2;
    cout<<query(tree, 0, n-1, 1, left, right);
}