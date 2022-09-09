#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n,m;
    int ar[1000];

    while(cin >> n){
        for(int i=0;i<n;i++){
            cin >> ar[i];
        }
        sort(ar[0],ar[n]);

        for(int i=0;i<n;i++){
            cout << ar[i] << " ";
        }
        cout << endl;
    }
    
    return 0;
}