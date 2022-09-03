#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n,l;
    cin >> n >> l;
    vector<int> tre(n);
    vector<int> treHigh(n);
    for(int i=0;i<n;i++){
        cin >> tre[i];
    }
    for(int i=0;i<n;i++){
        cin >> treHigh[i];
    }


    return 0;
}