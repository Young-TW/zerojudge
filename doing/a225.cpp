#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int n,m;
    vector<int> ar;

    while(cin >> n){
        for(int i=0;i<n;i++){
            cin >> m;
            ar.push_back(m);
        }
        sort(ar.begin(),ar.end());
        
        for(int i=0;i<n;i++){
            cout << ar[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

// 明明愛排列