#include <iostream>
#include <vector>
using namespace std;

bool pressure(int left,int right,vector<int> trePlace){
    for(int i=left;i<right;i++){
        for(int j=0;j<trePlace.size();j++){
            if(trePlace[j]==i){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int n,l;
    int highestTree = 0;
    cin >> n >> l;
    vector<int> trePlace(n);
    vector<int> treHigh(n);
    for(int i=0;i<n;i++){
        cin >> trePlace[i];
    }
    for(int i=0;i<n;i++){
        cin >> treHigh[i];
    }
    for(int i=0;i<n;i++){
        if(pressure(trePlace[i]-treHigh[i],treHigh[i],trePlace) || pressure(trePlace[i]-treHigh[i],treHigh[i],trePlace))
        treHigh[i];
    }

    return 0;
}