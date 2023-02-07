#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n,flag;
    cin >> n;
    vector<int> h(n);
    for(int i=0;i<n;i++){
        cin >> h[i];
    }
    for(int i=0;i<n;i++){
        flag = i;
        while(flag >= 0 && h[i] <= h[flag]){
            --flag;
        }
        if(flag>=0){
            cout << flag+1 << " ";
        }else{
            cout << "0 ";
            continue;
        }
    }
    return 0;
}