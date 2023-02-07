#include <iostream>
using namespace std;

int main(){
    int num;
    while(cin >> num){
        for(int i=1;i<num;i++){
            if(i%7==0)
                continue;
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}