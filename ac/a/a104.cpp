#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int n,reg;
    vector<int> v;
    while(cin >> n){
        for(int i=0;i<n;i++){
            cin >> reg;
            v.push_back(reg);
        }
        sort(v.begin(),v.end());
        for(int i=0;i<n;i++){
            cout << v[i] << " ";
        }
        cout << endl;
        v.clear();
    }
    return 0;
}