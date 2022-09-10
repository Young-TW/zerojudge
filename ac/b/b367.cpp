#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int n,x,y,reg;
    vector<int> ar,revar;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x >> y;
        for(int j=0;j<x*y;j++){
            cin >> reg;
            ar.push_back(reg);
        }
        revar = ar;
        reverse(revar.begin(),revar.end());
        if(revar==ar){
            cout << "go forward" << endl;
        }else{
            cout << "keep defending" << endl;
        }
        ar.clear();
    }
    return 0;
}