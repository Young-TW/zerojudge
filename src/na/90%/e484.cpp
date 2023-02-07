#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    bool judge = 0;
    for(int i=2;i<n/2;i++){
        if(n%i==0){
            judge=1;
            break;
        }
    }
    if(judge){
        cout << "no";
        return 0;
    }
    cout << "yes";
    return 0;
}